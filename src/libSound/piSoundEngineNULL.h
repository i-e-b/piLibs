#pragma once

#include "piSound.h"

namespace piLibs {

	class piSoundEngineBackendNULL : public piSoundEngineBackend
	{
	public:
		bool           Init(void* hwnd, int deviceID, int maxSoundsOverride);
		void           Deinit();
		int            GetNumDevices(void);
		const wchar_t *GetDeviceName(int id) const;
		int            GetDeviceFromGUID(void *deviceGUID);
		bool           ResizeMixBuffers(int const& mixSamples, int const& spatialSamples);
		void           Tick(double dt);
		piSoundEngine * GetEngine(void);

	public:
		void *mData;

	private:
		friend piSoundEngineBackend * piCreateSoundEngineBackend(piSoundEngineBackend::API api);
		friend void                   piDestroySoundEngineBackend(piSoundEngineBackend *me);
		piSoundEngineBackendNULL();
		~piSoundEngineBackendNULL();
		bool doInit(void);
		void doDeinit(void);
	};

}