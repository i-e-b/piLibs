#pragma once

#include "../../libSystem/piTypes.h"
#include "../../libMath/piVecTypes.h"

namespace piLibs
{

	namespace piTransforms
	{
		namespace piNormal
		{
			vec2 octahedral(const vec3 & v);
			vec2 polar(const vec3 & v);
			vec2 cube(const vec3 & v, uint8_t *face);

			vec3 ioctahedral(const vec2 & v);
			vec3 ipolar(const vec2 & v);
			vec3 icube(const vec2 & v, uint8_t face);
		}
	}

} // namespace piLibs