#include "piSoundEngineNULL.h"
#include "windows/piSoundEngineDS.h"
#include "windows/piSoundEngineOVR.h"
#include "windows/piSoundEngineBASS.h"

namespace piLibs
{
	piSoundEngineBackend * piCreateSoundEngineBackend(piSoundEngineBackend::API api)
	{
		piSoundEngineBackend *me = nullptr;
		     if (api == piSoundEngineBackend::API::Null)           me = new piSoundEngineBackendNULL();
		else if (api == piSoundEngineBackend::API::DirectSound)    me = new piSoundEngineBackendDS();
		else if (api == piSoundEngineBackend::API::DirectSoundOVR) me = new piSoundEngineBackendOVR();
		else return nullptr;

		if (!me->doInit())
			return false;

		return me;
	}

	void piDestroySoundEngineBackend(piSoundEngineBackend *me)
	{
		me->doDeinit();
		delete me;
	}

}
