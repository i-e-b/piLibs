#include <malloc.h>
#include "piSoundEngineNULL.h"

namespace piLibs {

	struct iSoundEngineBackend
	{
		piSoundEngine *mEngine;
	};

	class piSoundEngineNULL : public piSoundEngine
	{
	public:
		int AddSound(const wchar_t *filename)
		{
			return 0;
		}

		int AddSound(const int frequency, int precision, int length, void *buffer)
		{
			return 0;
		}
		void  DelSound(int id)
		{
		}
		bool Play(int id, bool doLoop, float volume, int offset)
		{
			return true;
		}
		bool Stop(int id)
		{
			return true;
		}
		void  PauseAllSounds(void)
		{
		}
		void  ResumeAllSounds(void)
		{
		}

		void  SetListener(const double * lst2world)
		{
		}

		void SetPosition(int id, const double * pos)
		{
		}

		void SetOrientation(int id, const double * dir, const double * up)
		{
		}
		void SetPositionOrientation(int id, const double * pos, const double * dir, const double * up)
		{
		}
		bool  GetIsPlaying(int id)
		{
			return true;
		}

		float GetVolume(int id) const
		{
			return 0.0f;
		}
		bool  SetVolume(int id, float volume)
		{
			return true;
		}
		bool  GetSpatialize(int id) const { return false; }
		bool  SetSpatialize(int id, bool spatialize) { return false; }
		bool  CanChangeSpatialize(int id) const { return false; }
		bool  GetLooping(int id) const
		{
			return false;
		}
		void SetLooping(int id, bool looping)
		{
		}
		bool  GetPaused(int id) const
		{
			return false;
		}
		void  SetPaused(int id, bool paused)
		{
		}
		int   GetAttenMode(int id) const { return 0; }
		void  SetAttenMode(int id, int attenMode) {}
		float GetAttenRadius(int id) const { return 0.0f; }
		void  SetAttenRadius(int id, float attenRadius) {}
		float GetAttenMin(int id) const { return 0.0f; }
		void  SetAttenMin(int id, float attenMin) {}
		float GetAttenMax(int id) const { return 0.0f; }
		void  SetAttenMax(int id, float attenMax) {}

	public:
		piSoundEngineNULL(iSoundEngineBackend *bk) { mBk = bk; }
	private:
		iSoundEngineBackend * mBk;

	};

	piSoundEngineBackendNULL::piSoundEngineBackendNULL() :piSoundEngineBackend()
	{
	}
	piSoundEngineBackendNULL::~piSoundEngineBackendNULL()
	{
	}
	bool piSoundEngineBackendNULL::doInit()
	{
		iSoundEngineBackend * me = (iSoundEngineBackend*)malloc(sizeof(iSoundEngineBackend));
		if (!me) return false;
		mData = me;
		me->mEngine = new piSoundEngineNULL(me);
		return true;
	}

	void piSoundEngineBackendNULL::doDeinit(void)
	{
		iSoundEngineBackend * me = (iSoundEngineBackend*)mData;
		delete me->mEngine;
		free(me);
	}

	
	int piSoundEngineBackendNULL::GetNumDevices(void)
	{
		return 1;
	}

	const wchar_t *piSoundEngineBackendNULL::GetDeviceName(int id) const
	{
		return L"Null";
	}

	int piSoundEngineBackendNULL::GetDeviceFromGUID(void *deviceGUID)
	{
		return 0;
	}


	bool piSoundEngineBackendNULL::Init(void *hwnd, int deviceID, int maxSoundsOverrideUnused)
	{
		iSoundEngineBackend * me = (iSoundEngineBackend*)mData;
		return true;
	}

	void piSoundEngineBackendNULL::Deinit(void)
	{
		iSoundEngineBackend * me = (iSoundEngineBackend*)mData;
	}

	void piSoundEngineBackendNULL::Tick(double dt)
	{
	}

	piSoundEngine * piSoundEngineBackendNULL::GetEngine(void)
	{
		iSoundEngineBackend * me = (iSoundEngineBackend*)mData;
		return me->mEngine;
	}
	bool piSoundEngineBackendNULL::ResizeMixBuffers(int const& mixSamples, int const& spatialSamples)
	{
		return true;
	}


}
