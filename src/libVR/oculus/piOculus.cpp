#include "../../libSystem/piTimer.h"
#include "../../libSystem/piTypes.h"
#include "../../libMath/piVecTypes.h"
#include "../../libSystem/piStr.h"

#if defined(OVR_OS_WIN32) || defined(OVR_OS_WIN64)
#include <windows.h>
#endif


#include "OVR_Platform.h"
#include "OVR_CAPI_GL.h"
#include "OVR_CAPI_Audio.h"
#include <string.h>
#include "piOculus.h"

namespace piLibs {

static int imax(int a, int b) { return (a>b) ? a : b; }

bool piVROculus::Init(const char * appID)
{
    if (ovr_Initialize(nullptr) < 0)
        return false;

	if (appID != nullptr)
	{
		if (ovr_PlatformInitializeWindowsEx(appID, 1, 1) != ovrPlatformInitialize_Success)
			return false;

		ovr_Entitlement_GetIsViewerEntitled(); // send message
	}
    return true;
}

void piVROculus::DeInit(void)
{
    ovr_Shutdown();
}

//====================================================================

class piVRHMDOculus : public piVRHMD
{
private:
	#ifdef PROVIDE_DEPTH
	ovrLayerEyeFovDepth mLayer;
	#else
	ovrLayerEyeFov      mLayer;
	#endif
	bool                mIsVisible;
	ovrHmdDesc          mHmdDesc;
	ovrSession          mSession;
	uint64_t            mFrame;
	ovrTextureSwapChain mTextureChainColor[2];
	#ifdef PROVIDE_DEPTH
	ovrTextureSwapChain mTextureChainDepth[2];
	#endif
	ovrSizei            mRecommendedTexSize[2];
	ovrMirrorTexture    mMirrorTexture;
	bool                mEnableMipmapping;
	GUID			    mSoundGUID;

	struct HapticState
	{
		int    mState;
		float  mDuration;
		double mTime;
	}mHapticState[2];

	piTimer mTimer;

public:
	piVRHMDOculus();

	bool AttachToWindow(bool createMirrorTexture, int mirrorTextureSizeX, int mirrorTextureSizeY);
	void BeginFrame(int *texIndexLeft, int *texIndexRight, bool *outNeedsMipMapping);
	void EndFrame(void);
	void GetHmdState(HmdState * state);
	void *GetSoundOutputGUID(void);
    void SetTrackingOrigin(void);
	void SetTrackingOriginType(TrackingOrigin type);

private:
	void iHaptic(int id, float frequency, float amplitude, float duration);

	friend class piVROculus;

private:
	bool Init(int deviceID, float pixelDensity);
	void DeInit(void);

};


piVRHMD *piVROculus::CreateHmd(int deviceID, float pixelDensity)
{
    piVRHMDOculus *me = new piVRHMDOculus();
    if( !me ) 
        return nullptr;

    if( !me->Init(deviceID, pixelDensity ) )
        return nullptr;

    return me;
}

void piVROculus::DestroyHmd(piVRHMD * vme)
{
	if ( !vme ) return;
    piVRHMDOculus *me = (piVRHMDOculus*)vme;
    me->DeInit();
    delete me;
}

void piVROculus::GetLastError(char* errorStr)
{
	ovrErrorInfo errorInfo;
	ovr_GetLastErrorInfo(&errorInfo);
	pistrcpy(errorStr,511,errorInfo.ErrorString);
}


//------------------------------------------------------------

void piVRHMDOculus::iHaptic(int id, float frequency, float amplitude, float duration)
{
    HapticState *hs = mHapticState + id;

    if( hs->mState==1 ) return;

    hs->mState = 1;
    hs->mDuration = duration;
    hs->mTime = mTimer.GetTime();

    const ovrControllerType ct = (id == 0) ? ovrControllerType_LTouch : ovrControllerType_RTouch;
    ovr_SetControllerVibration(mSession, ct, frequency, amplitude);
}

static void iJoystickInit(piVRHMD::Joystick *j)
{
	j->mEventSwipeDown = false;
	j->mEventSwipeLeft = false;
	j->mEventSwipeRight = false;
	j->mEventSwipeUp = false;
}

static void iJoystickLogic(piVRHMD::Joystick *j, float x, float y)
{
	// X -------------------------------
	j->mX = x;
	j->mEventSwipeLeft = false;
	j->mEventSwipeRight = false;
	if (x > 0.8f)
	{
		if (j->mInternalX != 1)
		{
			j->mEventSwipeRight = true;
			j->mInternalX = 1;
		}
	}
	else if (x < -0.8f)
	{
		if ((j->mInternalX != -1))
		{
			j->mEventSwipeLeft = true;
			j->mInternalX = -1;
		}
	}
	else {
		j->mInternalX = 0;
	}


	// Y -------------------------------
	j->mY = y;
	j->mEventSwipeUp = false;
	j->mEventSwipeDown = false;

	if (y > 0.8f)
	{
		if (j->mInternalY != 1)
		{
			j->mEventSwipeUp = true;
			j->mInternalY = 1;
		}
	}
	else if (y < -0.8f)
	{
		if (j->mInternalY != -1)
		{
			j->mEventSwipeDown = true;
			j->mInternalY = -1;
		}
	}
	else
	{
		j->mInternalY = 0;
	}	
}

static void iTouchInit(piVRHMD::Touch *b)
{
	b->mStateTouched = false;
	b->mEventTouchBegin = false;
	b->mEventTouchEnd = false;
}

static void iTouchLogic(piVRHMD::Touch *b, bool state)
{
	bool oldState = b->mStateTouched;
	b->mStateTouched = state;
	b->mEventTouchBegin = (!oldState &&  b->mStateTouched);
	b->mEventTouchEnd = (oldState && !b->mStateTouched);
}


static void iButtonInit(piVRHMD::Button *b )
{
    b->mInternal1 = 0;
    b->mInternal2 = 0.0;
    b->mStatePressed = false;
    b->mEventDown = false;
    b->mEventUp = false;
    b->mEventDoubleClick = false;
    b->mEventSingleClick = false;
}

static void iButtonLogic(piVRHMD::Button *b, bool state, double time)
{
    bool oldUpButton = b->mStatePressed;
    b->mStatePressed = state;
    b->mEventDown = (!oldUpButton &&  b->mStatePressed);
    b->mEventUp = (oldUpButton && !b->mStatePressed);

    // pick double click
    b->mEventDoubleClick = false;
    b->mEventSingleClick = false;
    if (b->mInternal1 == 0)
    {
        if (b->mEventDown) // single CLICK
        {
            b->mInternal2 = time;
            b->mInternal1 = 1;
        }
    }
    else if (b->mInternal1 == 1)
    {
        if ((time - b->mInternal2) > 250.0)
        {
            b->mInternal1 = 0;
            b->mEventSingleClick = true;
        }
        else if (b->mEventDown) // double Y click
        {
            b->mInternal1 = 0;
            b->mEventDoubleClick = true;
        }
    }

}

piVRHMDOculus::piVRHMDOculus()
{
	memset( &mInfo, 0, sizeof( mInfo ) );
	memset( &mState, 0, sizeof( mState ) );
	memset( &mLayer, 0, sizeof( mLayer ) );
	mIsVisible = false;
	memset( &mHmdDesc, 0, sizeof( mHmdDesc ) );
	memset( &mSession, 0, sizeof( mSession ) );
	mFrame = 0;
	memset( &mTextureChainColor, 0, sizeof(mTextureChainColor) );
	#ifdef PROVIDE_DEPTH
	memset( &mTextureChainDepth, 0, sizeof(mTextureChainDepth));
	#endif
	memset( &mRecommendedTexSize, 0, sizeof( mRecommendedTexSize ) );
	memset( &mMirrorTexture, 0, sizeof( mMirrorTexture ) );
	mEnableMipmapping = false;
	memset( &mSoundGUID, 0, sizeof( mSoundGUID ) );
}

bool piVRHMDOculus::Init(int deviceID, float pixelDensity)
{
    if( !mTimer.Init() )
        return false;
    
	ovrGraphicsLuid luid;
    ovrResult res = ovr_Create(&mSession, &luid);
    if (!OVR_SUCCESS(res))
        return false;

	res = ovr_GetAudioDeviceOutGuid(&mSoundGUID);
	if (!OVR_SUCCESS(res))
		return false;

    mFrame = 0;
    mHmdDesc = ovr_GetHmdDesc(mSession);
    mInfo.mXres = mHmdDesc.Resolution.w;
    mInfo.mYres = mHmdDesc.Resolution.h;
    mEnableMipmapping = (pixelDensity>1.0f);

    for (int i = 0; i<2; i++)
    {
        mRecommendedTexSize[i] = ovr_GetFovTextureSize(mSession, ovrEyeType(i), mHmdDesc.DefaultEyeFov[i], pixelDensity);
    }

    mInfo.mVRXres = mRecommendedTexSize[0].w;
    mInfo.mVRYres = mRecommendedTexSize[0].h;

    for (int i = 0; i<2; i++)
    {
        iButtonInit( &mInfo.mHead.mController[i].mUpButton );
        iButtonInit(&mInfo.mHead.mController[i].mDownButton);

		iTouchInit(&mInfo.mHead.mController[i].mUpTouch);
		iTouchInit(&mInfo.mHead.mController[i].mDownTouch);
		iTouchInit(&mInfo.mHead.mController[i].mIndexTriggerTouch);
		iTouchInit(&mInfo.mHead.mController[i].mThumbstickTouch);

		iJoystickInit(&mInfo.mHead.mController[i].mThumbstick);

        mInfo.mHead.mController[i].Vibrate = [&]( int id, float frequency, float amplitude, float duration) 
        {
            iHaptic(id, frequency, amplitude, duration );
        };
        mHapticState[i].mState = 0;
    }

    iButtonInit(&mInfo.mHead.mRemote.mDownButton);
    iButtonInit(&mInfo.mHead.mRemote.mUpButton);
    iButtonInit(&mInfo.mHead.mRemote.mLeftButton);
    iButtonInit(&mInfo.mHead.mRemote.mRightButton);
    iButtonInit(&mInfo.mHead.mRemote.mVolumeUpButton);
    iButtonInit(&mInfo.mHead.mRemote.mVolumeDownButton);
    iButtonInit(&mInfo.mHead.mRemote.mHomeButton);


	mState.mHMDLost = false;
	mState.mIsVisible = false;
	mState.mShouldQuit = false;
	mState.mNotEntitled = false;
	mState.mHMDWorn = false;
	mState.mPositionTracked = false;
	mState.mTrackerConnected = false;

    return true;
}


void piVRHMDOculus::DeInit( void )
{
	ovr_Destroy(mSession);
}


bool piVRHMDOculus::AttachToWindow( bool createMirrorTexture, int mirrorTextureSizeX, int mirrorTextureSizeY)
{
    if( createMirrorTexture )
    {
    ovrMirrorTextureDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.Width = mirrorTextureSizeX;
    desc.Height = mirrorTextureSizeY;
    desc.Format = OVR_FORMAT_R8G8B8A8_UNORM_SRGB;
    ovrResult result = ovr_CreateMirrorTextureGL(mSession, &desc, &mMirrorTexture);
    if (!OVR_SUCCESS(result))
        return false;
    ovr_GetMirrorTextureBufferGL(mSession, mMirrorTexture, &mInfo.mMirrorTexID);
    }

    for( int i=0; i<2; i++ )
    {
		//------------
		{
			ovrTextureSwapChainDesc desc = {};
			desc.Type = ovrTexture_2D;
			desc.Format = OVR_FORMAT_R8G8B8A8_UNORM_SRGB;
			desc.ArraySize = 1;
			desc.Width = mRecommendedTexSize[i].w;
			desc.Height = mRecommendedTexSize[i].h;
			desc.MipLevels = (mEnableMipmapping == true) ? 3 : 1;
			desc.SampleCount = 1;
			desc.StaticImage = ovrFalse;

			ovrResult result = ovr_CreateTextureSwapChainGL(mSession, &desc, &mTextureChainColor[i]);
			if (!OVR_SUCCESS(result))
				return false;

			int length = 0;
			ovr_GetTextureSwapChainLength(mSession, mTextureChainColor[i], &length);

			mInfo.mTexture[i].mNum = length;

			for (int j = 0; j < length; j++)
			{
				unsigned int chainTexId;
				ovr_GetTextureSwapChainBufferGL(mSession, mTextureChainColor[i], j, &chainTexId);
				mInfo.mTexture[i].mTexIDColor[j] = chainTexId;
			}
		}
		#ifdef PROVIDE_DEPTH
		//------------
		{
			ovrTextureSwapChainDesc desc = {};
			desc.Type = ovrTexture_2D;
			desc.Format = OVR_FORMAT_D24_UNORM_S8_UINT; // OVR_FORMAT_D32_FLOAT
			desc.ArraySize = 1;
			desc.Width = mRecommendedTexSize[i].w;
			desc.Height = mRecommendedTexSize[i].h;
			desc.MipLevels = 1;
			desc.SampleCount = 1;
			desc.StaticImage = ovrFalse;

			ovrResult result = ovr_CreateTextureSwapChainGL(mSession, &desc, &mTextureChainDepth[i]);
			if (!OVR_SUCCESS(result))
				return false;

			int length = 0;
			ovr_GetTextureSwapChainLength(mSession, mTextureChainDepth[i], &length);

			if (length != mInfo.mTexture[i].mNum)
				return false;

			mInfo.mTexture[i].mNum = length;

			for (int j = 0; j < length; j++)
			{
				unsigned int chainTexId;
				ovr_GetTextureSwapChainBufferGL(mSession, mTextureChainDepth[i], j, &chainTexId);
				mInfo.mTexture[i].mTexIDDepth[j] = chainTexId;
			}
		}
		#endif
		//------------

        mLayer.ColorTexture[i] = mTextureChainColor[i];
		#ifdef PROVIDE_DEPTH
		mLayer.DepthTexture[i] = mTextureChainDepth[i];
		#endif
        mLayer.Viewport[i] = { { 0, 0 }, { mRecommendedTexSize[i].w, mRecommendedTexSize[i].h } };
    }


    // FloorLevel will give tracking poses where the floor height is 0
    //ovr_SetTrackingOriginType( mSession, ovrTrackingOrigin_FloorLevel );

    ovr_SetTrackingOriginType(mSession, ovrTrackingOrigin_EyeLevel);

    // Initialize our single full screen Fov layer.
	#ifdef PROVIDE_DEPTH
    mLayer.Header.Type = ovrLayerType_EyeFovDepth;
	#else
	mLayer.Header.Type = ovrLayerType_EyeFov;
	#endif	
	mLayer.Header.Flags = ovrLayerFlag_TextureOriginAtBottomLeft | ovrLayerFlag_HighQuality;
    return true;
}


void piVRHMDOculus::BeginFrame( int *texIndexLeft, int *texIndexRight, bool *outNeedsMipMapping)
{
    // update mFrame now, so it is correct in call to ovr_GetPredictedDisplayTime below
    mFrame++;

    // take care of haptics first
    for( int i=0; i<2; i++ )
    {
        HapticState *hs = mHapticState + i;
        if( hs->mState==1 )
        {
            const float dt = float(mTimer.GetTime() - hs->mTime );
            if( dt > hs->mDuration )
            {
                const ovrControllerType ct = (i==0) ? ovrControllerType_LTouch : ovrControllerType_RTouch;
                ovr_SetControllerVibration( mSession, ct, 0.0f, 0.0f );
                hs->mState = 0;
            }
        }
    }

    // go on with rendering

    ovrEyeRenderDesc    eyeRenderDesc[2];

    eyeRenderDesc[0] = ovr_GetRenderDesc( mSession, ovrEye_Left,  mHmdDesc.DefaultEyeFov[0] );
    eyeRenderDesc[1] = ovr_GetRenderDesc( mSession, ovrEye_Right, mHmdDesc.DefaultEyeFov[1] );

	ovrPosef HmdToEyeOffset[2] = { eyeRenderDesc[0].HmdToEyePose, eyeRenderDesc[1].HmdToEyePose };

    double   sensorSampleTime;
    ovrPosef EyeRenderPose[2];
    ovr_GetEyePoses(mSession, mFrame, ovrTrue, HmdToEyeOffset, EyeRenderPose, &sensorSampleTime);

    mLayer.Fov[0] = eyeRenderDesc[0].Fov;
    mLayer.Fov[1] = eyeRenderDesc[1].Fov;
    mLayer.RenderPose[0] = EyeRenderPose[0];
    mLayer.RenderPose[1] = EyeRenderPose[1];
    mLayer.SensorSampleTime = sensorSampleTime;

    // Get both eye poses simultaneously, with IPD offset already included.
    double predictedDisplayInSeconds = ovr_GetPredictedDisplayTime(mSession, mFrame);
    ovrTrackingState hmdState = ovr_GetTrackingState(mSession, predictedDisplayInSeconds, ovrTrue);
    ovr_CalcEyePoses(hmdState.HeadPose.ThePose, HmdToEyeOffset, mLayer.RenderPose);
   
    ovrTrackerPose trackerPose = ovr_GetTrackerPose(mSession, 0);
    mState.mTrackerConnected = ( trackerPose.TrackerFlags & ovrTracker_Connected ) != 0;
    mState.mPositionTracked = ( hmdState.StatusFlags & ovrStatus_PositionTracked ) != 0;

    mat4x4 rot = setRotation4(quat(&hmdState.HeadPose.ThePose.Orientation.x));
    mat4x4 tra = setTranslation(-hmdState.HeadPose.ThePose.Position.x, -hmdState.HeadPose.ThePose.Position.y, -hmdState.HeadPose.ThePose.Position.z);
    mat4x4 tmp = transpose(rot) * tra;
    memcpy(mInfo.mHead.mCamera, &tmp, 16 * sizeof(float));

    const double time = mTimer.GetTimeMs();

	ovrInputState inputState;

    
    if (ovr_GetInputState(mSession, ovrControllerType_Remote, &inputState) >= 0)
    {
        mInfo.mHead.mRemote.mEnabled = (inputState.ControllerType & ovrControllerType_Remote) != 0;

        iButtonLogic(&mInfo.mHead.mRemote.mUpButton, (inputState.Buttons & ovrButton_Up) != 0, time);
        iButtonLogic(&mInfo.mHead.mRemote.mDownButton, (inputState.Buttons & ovrButton_Down) != 0, time);
        iButtonLogic(&mInfo.mHead.mRemote.mLeftButton, (inputState.Buttons & ovrButton_Left) != 0, time);
        iButtonLogic(&mInfo.mHead.mRemote.mRightButton, (inputState.Buttons & ovrButton_Right) != 0, time);

        iButtonLogic(&mInfo.mHead.mRemote.mEnterButton, (inputState.Buttons & ovrButton_Enter) != 0, time);
        iButtonLogic(&mInfo.mHead.mRemote.mVolumeUpButton, (inputState.Buttons & ovrButton_VolUp) != 0, time);
        iButtonLogic(&mInfo.mHead.mRemote.mVolumeUpButton, (inputState.Buttons & ovrButton_VolDown) != 0, time);
        iButtonLogic(&mInfo.mHead.mRemote.mHomeButton, (inputState.Buttons & ovrButton_Home) != 0, time);
    }

    if (ovr_GetInputState(mSession, ovrControllerType_Touch, &inputState) >= 0)
    {
        mInfo.mHead.mController[0].mEnabled = ((inputState.ControllerType & ovrControllerType_LTouch) != 0);
        if (mInfo.mHead.mController[0].mEnabled )
        {
            
			iJoystickLogic(&mInfo.mHead.mController[0].mThumbstick, inputState.Thumbstick[ovrHand_Left].x, inputState.Thumbstick[ovrHand_Left].y);

            mInfo.mHead.mController[0].mIndexTrigger = inputState.IndexTrigger[ovrHand_Left];
            mInfo.mHead.mController[0].mHandTrigger = inputState.HandTrigger[ovrHand_Left];

			iButtonLogic(&mInfo.mHead.mController[0].mThumbstickButton, (inputState.Buttons & ovrButton_LThumb) != 0, time);
            iButtonLogic( &mInfo.mHead.mController[0].mUpButton, (inputState.Buttons & ovrButton_Y) != 0, time);
            iButtonLogic( &mInfo.mHead.mController[0].mDownButton, (inputState.Buttons & ovrButton_X) != 0, time);

			iTouchLogic(&mInfo.mHead.mController[0].mThumbstickTouch, (inputState.Touches & ovrTouch_LThumb) != 0);
			iTouchLogic(&mInfo.mHead.mController[0].mDownTouch, (inputState.Touches & ovrTouch_X) != 0);
			iTouchLogic(&mInfo.mHead.mController[0].mUpTouch, (inputState.Touches & ovrTouch_Y) != 0);
			iTouchLogic(&mInfo.mHead.mController[0].mIndexTriggerTouch, (inputState.Touches & ovrTouch_LIndexTrigger) != 0);
        }

        mInfo.mHead.mController[1].mEnabled = ((inputState.ControllerType & ovrControllerType_RTouch) != 0);
        if (mInfo.mHead.mController[1].mEnabled)
        {
            mInfo.mHead.mController[1].mEnabled = true;
            
			iJoystickLogic(&mInfo.mHead.mController[1].mThumbstick, inputState.Thumbstick[ovrHand_Right].x, inputState.Thumbstick[ovrHand_Right].y);

            mInfo.mHead.mController[1].mIndexTrigger = inputState.IndexTrigger[ovrHand_Right];
            mInfo.mHead.mController[1].mHandTrigger = inputState.HandTrigger[ovrHand_Right];

			iButtonLogic(&mInfo.mHead.mController[1].mThumbstickButton, (inputState.Buttons & ovrButton_RThumb) != 0, time);
            iButtonLogic(&mInfo.mHead.mController[1].mUpButton, (inputState.Buttons & ovrButton_B) != 0, time);
            iButtonLogic(&mInfo.mHead.mController[1].mDownButton, (inputState.Buttons & ovrButton_A) != 0, time);

			iTouchLogic(&mInfo.mHead.mController[1].mThumbstickTouch, (inputState.Touches & ovrTouch_RThumb) != 0);
			iTouchLogic(&mInfo.mHead.mController[1].mDownTouch, (inputState.Touches & ovrTouch_A) != 0);
			iTouchLogic(&mInfo.mHead.mController[1].mUpTouch, (inputState.Touches & ovrTouch_B) != 0);
			iTouchLogic(&mInfo.mHead.mController[1].mIndexTriggerTouch, (inputState.Touches & ovrTouch_RIndexTrigger) != 0);
        }

		/*
		ovrTouch_A	User in touching A button on the right controller.
		ovrTouch_B	User in touching B button on the right controller.
		ovrTouch_RThumb	User has a finger on the thumb stick of the right controller.
		ovrTouch_RThumbRest	User has a finger on the textured thumb rest of the right controller.
		ovrTouch_RIndexTrigger	User in touching the index finger trigger on the right controller.
		ovrTouch_X	User in touching X button on the left controller.
		ovrTouch_Y	User in touching Y button on the left controller.
		ovrTouch_LThumb	User has a finger on the thumb stick of the left controller.
		ovrTouch_LThumbRest	User has a finger on the textured thumb rest of the left controller.
		ovrTouch_LIndexTrigger	User in touching the index finger trigger on the left controller.
		ovrTouch_RIndexPointing	Users right index finger is pointing forward past the trigger.
		ovrTouch_RThumbUp	Users right thumb is up and away from buttons on the controller, a gesture that can be interpreted as right thumbs up.
		ovrTouch_LIndexPointing	Users left index finger is pointing forward past the trigger.
		ovrTouch_LThumbUp	Users left thumb is up and away from buttons on the controller, a gesture that can be interpreted as left thumbs up.
		*/
    }
    else
    {
        mInfo.mHead.mController[0].mEnabled = false;
        mInfo.mHead.mController[1].mEnabled = false;
    }

    for( int i=0; i<2; i++ )
    {
        ovrPosef ph0 = hmdState.HandPoses[i].ThePose;

        ovrVector3f vel = hmdState.HandPoses[i].LinearVelocity;
		ovrVector3f angVel = hmdState.HandPoses[i].AngularVelocity;

        mat4x4 rot = setRotation4(quat(&ph0.Orientation.x));
        mat4x4 tra = setTranslation(ph0.Position.x, ph0.Position.y, ph0.Position.z);
        mat4x4 tmp = tra * rot;
        memcpy(mInfo.mHead.mController[i].mLocation, &tmp, 16 * sizeof(float));
        mInfo.mHead.mController[i].mVelocity[0] = vel.x;
        mInfo.mHead.mController[i].mVelocity[1] = vel.y;
        mInfo.mHead.mController[i].mVelocity[2] = vel.z;
		mInfo.mHead.mController[i].mAngularVelocity[0] = angVel.x;
		mInfo.mHead.mController[i].mAngularVelocity[1] = angVel.y;
		mInfo.mHead.mController[i].mAngularVelocity[2] = angVel.z;

    }

    //ovrSwapTextureSet *ts = mTextureSet;

    //if (isVisible)
    {
        //ts->CurrentIndex = (ts->CurrentIndex + 1) % ts->TextureCount;

        for( int eyeID = 0; eyeID<2; eyeID++ )
        {
            mat4x4 rot = setRotation4(quat(&mLayer.RenderPose[eyeID].Orientation.x));
            mat4x4 tra = setTranslation(-mLayer.RenderPose[eyeID].Position.x, -mLayer.RenderPose[eyeID].Position.y, -mLayer.RenderPose[eyeID].Position.z);
            mat4x4 tmp = transpose(rot) * tra;
            memcpy(mInfo.mEye[eyeID].mCamera, &tmp, 16 * sizeof(float));

            mInfo.mEye[eyeID].mProjection[0] = mLayer.Fov[eyeID].UpTan;
            mInfo.mEye[eyeID].mProjection[1] = mLayer.Fov[eyeID].DownTan;
            mInfo.mEye[eyeID].mProjection[2] = mLayer.Fov[eyeID].LeftTan;
            mInfo.mEye[eyeID].mProjection[3] = mLayer.Fov[eyeID].RightTan;

            mInfo.mEye[eyeID].mVP[0] = mLayer.Viewport[eyeID].Pos.x;
            mInfo.mEye[eyeID].mVP[1] = mLayer.Viewport[eyeID].Pos.y;
            mInfo.mEye[eyeID].mVP[2] = mLayer.Viewport[eyeID].Size.w;
            mInfo.mEye[eyeID].mVP[3] = mLayer.Viewport[eyeID].Size.h;
        }
    }


    mInfo.mHead.mProjection[0] = mLayer.Fov[0].UpTan;
    mInfo.mHead.mProjection[1] = mLayer.Fov[0].DownTan;
    mInfo.mHead.mProjection[2] = mLayer.Fov[0].LeftTan;
    mInfo.mHead.mProjection[3] = mLayer.Fov[1].RightTan; 

    *outNeedsMipMapping = mEnableMipmapping;
    ovr_GetTextureSwapChainCurrentIndex(mSession, mTextureChainColor[0], texIndexLeft);
    ovr_GetTextureSwapChainCurrentIndex(mSession, mTextureChainColor[1], texIndexRight);
}

void piVRHMDOculus::EndFrame( void )
{
    for( int i=0; i<2; i++ )
    {
        ovr_CommitTextureSwapChain( mSession, mTextureChainColor[i] );
		#ifdef PROVIDE_DEPTH
		ovr_CommitTextureSwapChain(mSession, mTextureChainDepth[i]);
		#endif
    }

    // Submit frame with one layer we have.
    ovrLayerHeader* layers = &mLayer.Header;
    ovrResult       result = ovr_SubmitFrame(mSession, mFrame, nullptr, &layers, 1);
	ovrSessionStatus sessionStatus;

	if (result == ovrSuccess_NotVisible)
	{
		mState.mIsVisible = false;
	}
	else if (result == ovrError_DisplayLost)
	{
		mState.mShouldQuit = true;
		mState.mHMDLost = true;
		// We can either immediately quit or do the following:
		/*
		<destroy render target and graphics device>
			ovr_Destroy(session);

		do
		{ // Spin while trying to recreate session.
			result = ovr_Create(&session, &luid);
		}
		while (OVR_FAILURE(result) && !shouldQuit);

		if (OVR_SUCCESS(result))
		{
			<recreate graphics device with luid>
				<recreate render target via ovr_CreateTextureSwapChain>
		}
		*/
	}
	else if (OVR_FAILURE(result))
	{
		mState.mShouldQuit = true;
	}
	else
	{
		mState.mIsVisible = true;
	}

    ovr_GetSessionStatus( mSession, &sessionStatus);

	if (sessionStatus.ShouldQuit)
	{
		mState.mShouldQuit = true;
	}
	if (sessionStatus.ShouldRecenter)
	{
		ovr_RecenterTrackingOrigin(mSession); // or ovr_ClearShouldRecenterFlag(session) to ignore the request.
	}

	ovrMessage *response = ovr_PopMessage();
	if (response)
	{
		int messageType = ovr_Message_GetType(response);
		if (messageType == ovrMessage_Entitlement_GetIsViewerEntitled)
		{
			if (ovr_Message_IsError(response) != 0)
			{
				// User is not entitled.
				mState.mNotEntitled = true;
				mState.mShouldQuit = true;
			}
			else
			{
				// User IS entitled.			
				mState.mNotEntitled = false;
			}
		}
		else
		{
			//  Handle other Platform SDK messages here.
		}
	}

}

void piVRHMDOculus::SetTrackingOrigin(void)
{
    ovr_RecenterTrackingOrigin(mSession);
}

void piVRHMDOculus::GetHmdState(HmdState * state)
{
	ovrSessionStatus sessionStatus;
	ovr_GetSessionStatus(mSession, &sessionStatus);
	// these can also be set to true in endframe, so we only set them here if true
	if (sessionStatus.IsVisible) mState.mIsVisible = true;
	if (sessionStatus.ShouldQuit) mState.mShouldQuit = true;
	state->mIsVisible = mState.mIsVisible;
	state->mHMDWorn = (sessionStatus.HmdMounted!=0);
	state->mShouldQuit = mState.mShouldQuit;
	state->mHMDLost = mState.mHMDLost;
	state->mNotEntitled = mState.mNotEntitled;
	state->mTrackerConnected = mState.mTrackerConnected;
	state->mPositionTracked = mState.mPositionTracked;
}

void * piVRHMDOculus::GetSoundOutputGUID(void)
{
	return (void*)&mSoundGUID;
}

void piVRHMDOculus::SetTrackingOriginType(TrackingOrigin type)
{
	switch (type)
	{
	case FloorLevel: ovr_SetTrackingOriginType(mSession, ovrTrackingOrigin_FloorLevel); break;
	case EyeLevel: ovr_SetTrackingOriginType(mSession, ovrTrackingOrigin_EyeLevel); break;
	}
}

/*
void piVRHMDOculus::Haptic( int id, float frequency, float amplitude, float duration )
{
    mHapticState[id].mState = 1;
    mHapticState[id].mDuration = duration;
    mHapticState[id].mTime = piTimer_GetTime();
    const ovrControllerType ct = (id==0) ? ovrControllerType_LTouch : ovrControllerType_RTouch;
    ovr_SetControllerVibration(mSession, ct, frequency, amplitude);
}*/


}
