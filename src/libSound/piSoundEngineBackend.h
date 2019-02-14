#pragma once

#include "piSoundEngine.h"

namespace piLibs {

class piSoundEngineBackend
{
public:
	enum class API : int
	{
		Null = 0,
		DirectSound = 1,
		DirectSoundOVR = 2,
		BASS = 3
	};

    virtual bool           Init(void *hwnd, int deviceID, int maxSoundsOverride) = 0;
    virtual void           Deinit(void) = 0;
    virtual int            GetNumDevices( void ) = 0;
    virtual const wchar_t *GetDeviceName(int id) const = 0;
	virtual int            GetDeviceFromGUID(void *deviceGUID) = 0;
    virtual bool           ResizeMixBuffers(int const& mixSamples, int const& spatialSamples) = 0;
    virtual void           Tick(double dt) = 0;
	virtual piSoundEngine *GetEngine( void ) = 0;

protected:
	piSoundEngineBackend() {}
	friend piSoundEngineBackend * piCreateSoundEngineBackend(piSoundEngineBackend::API api);
	friend void                   piDestroySoundEngineBackend(piSoundEngineBackend *me);
	virtual ~piSoundEngineBackend() {}
	virtual bool doInit(void) = 0;
	virtual void doDeinit(void) = 0;

};

} // namespace piLibs
