#pragma once

//#define PROVIDE_DEPTH

#include <functional>

namespace piLibs {

class piVRHMD
{
public:
    typedef struct
    {
        bool  mStatePressed;
        bool  mEventDown;
        bool  mEventUp;
        bool  mEventDoubleClick;
        bool  mEventSingleClick;
        int   mInternal1;
        double mInternal2;
    }Button;

	typedef struct
	{
		bool mStateTouched;
		bool mEventTouchBegin;
		bool mEventTouchEnd;
	}Touch;

	typedef struct
	{
		float mX; // Horizontal and vertical thumbstick axis values , in the range -1.0f to 1.0f.
		float mY;
		
		bool mEventSwipeUp;
		bool mEventSwipeDown;
		bool mEventSwipeLeft;
		bool mEventSwipeRight;

		int mInternalX;
		int mInternalY;

	}Joystick;

    typedef struct
    {
        bool  mEnabled;
        float mLocation[16];
        float mVelocity[3];
		float mAngularVelocity[3];

        float mIndexTrigger; // Left and right finger trigger values, in the range 0.0 to 1.0f.
        float mHandTrigger; // Left and right hand trigger values , in the range 0.0 to 1.0f.
        
		Joystick mThumbstick;

		Touch mUpTouch;
		Touch mDownTouch;
		Touch mThumbstickTouch;
		Touch mIndexTriggerTouch;
		
		Button mUpButton;
        Button mDownButton;
		Button mThumbstickButton;

        //void (*Vibrate)(int id, float frequency, float amplitude, float duration);
        std::function<void(int id, float frequency, float amplitude, float duration)> Vibrate;

    }Controller;

    typedef struct
    {
        bool   mEnabled;
        Button mLeftButton;
        Button mRightButton;
        Button mUpButton;
        Button mDownButton;
        Button mEnterButton;
        Button mVolumeUpButton;
        Button mVolumeDownButton;
        Button mHomeButton;
    }Remote;

    typedef struct
    {
        float mCamera[16];
        float mProjection[4];
        Controller mController[2];
        Remote     mRemote;
    }HeadInfo;

    typedef struct
    {
        int   mVP[4];
        float mProjection[4];
        float mCamera[16];
    }EyeInfo;

    typedef struct
    {
        int                 mNum;
        unsigned int        mTexIDColor[64];
		#ifdef PROVIDE_DEPTH
		unsigned int        mTexIDDepth[64];
		#endif
    }TextureChain;

    typedef struct
    {
        // init
        int          mXres;
        int          mYres;
        int          mVRXres;
        int          mVRYres;
        TextureChain mTexture[2];
        unsigned int mMirrorTexID;

        // per frame
        HeadInfo     mHead;
        EyeInfo      mEye[2];
    }HmdInfo;
    
    HmdInfo mInfo;

	typedef struct
	{
		bool mShouldQuit;
		bool mHMDWorn;
		bool mIsVisible;
		bool mHMDLost;
		bool mNotEntitled;
		bool mTrackerConnected;
		bool mPositionTracked;
	} HmdState;

	typedef enum
	{
		FloorLevel, EyeLevel
	} 
	TrackingOrigin;


	HmdState mState;

    virtual bool AttachToWindow( bool createMirrorTexture, int mirrorTextureSizeX, int mirrorTextureSizeY) = 0;
    virtual void BeginFrame( int *texIndexLeft, int *texIndexRight, bool *outNeedsMipMapping) = 0;
    virtual void EndFrame( void ) = 0;
	virtual void GetHmdState(HmdState * state) = 0;
	virtual void *GetSoundOutputGUID(void) = 0;
    virtual void SetTrackingOrigin(void) = 0;
    virtual void SetTrackingOriginType(TrackingOrigin type) = 0;
	

    //virtual void Haptic(int id, float frequency, float amplitude, float duration) = 0;	
};

class piVR
{
public:
    typedef enum
    {
        Oculus_Rift = 0,
        HTC_Vive = 1
    }HwType;

    static piVR *Create(HwType hw, const char * appID);
    static void  Destroy(piVR * me);

    virtual piVRHMD  *CreateHmd(int deviceID, float pixelDensity) = 0;
    virtual void      DestroyHmd(piVRHMD * me) = 0;
	virtual void GetLastError(char * errorString) = 0;
};



} // namespace piLibs
