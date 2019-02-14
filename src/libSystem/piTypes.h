#pragma once

#include <stdint.h>

namespace piLibs {

#ifdef WINDOWS
 #define PIAPICALL __stdcall
#endif


#ifdef MACOS
#endif

#ifdef LINUX
 #define PIAPICALL
#endif

typedef uint16_t          half;


half  float2half(float x);
float half2float(half x);

} // namespace piLibs