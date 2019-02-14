#pragma once

#include "piSoundEngineBackend.h"

namespace piLibs {

piSoundEngineBackend * piCreateSoundEngineBackend(piSoundEngineBackend::API api);
void                   piDestroySoundEngineBackend(piSoundEngineBackend *me);

} // namespace piLibs
