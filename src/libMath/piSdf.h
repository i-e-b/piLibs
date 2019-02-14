#pragma once

#include "piVecTypes.h"
#include "piShading.h"

namespace piLibs {

inline float sdSphere(const vec3 & p, float s)
{
	return length(p) - s;
}

inline float sdCappedCylinder(const vec3 & p, const vec2 & h)
{
	const vec2 d = abs(vec2(length(p.xz()), p.y)) - h;
	return fminf(fmaxf(d.x, d.y), 0.0) + length(vmax(d, 0.0));
}

inline float sdTorus(const vec3 & p, const vec2 & t)
{
	const vec2 q = vec2(length(p.xz()) - t.x, p.y);
	return length(q) - t.y;
}

inline float sdSqSegment(const vec3 & p, const vec3 & a, const vec3 & b)
{
	const vec3 pa = p - a, ba = b - a;
	const float h = clamp01(dot(pa, ba) / dot(ba, ba) );
	return lengthSquared(pa - ba*h);
}

inline vec2 sdSqHSegment(const vec3 & p, const vec3 & a, const vec3 & b)
{
	const vec3 pa = p - a, ba = b - a;
	const float h = clamp01(dot(pa, ba) / dot(ba, ba) );
	return vec2( lengthSquared(pa - ba*h), h );
}

inline float sdBox(const vec3 & p, const vec3 & b)
{
    const vec3 d = abs(p) - b;
    return fminf(maxcomp(d), 0.0f) + length(vmax(d, 0.0f));
}

inline float sdCapsule(const vec3 & p, const vec3 & a, const vec3 & b, float r)
{
	const vec3 pa = p - a, ba = b - a;
	const float h = clamp01(dot(pa, ba) / dot(ba, ba));
	return length(pa - ba*h) - r;
}

static inline float dot2( const vec3 & v) { return dot(v, v); }

// (squared) distance to a triangle
inline float udSqTriangle( const vec3 & p, const vec3 & v1, const vec3 & v2, const vec3 & v3 )
{
	const vec3 v21 = v2 - v1; const vec3 p1 = p - v1;
	const vec3 v32 = v3 - v2; const vec3 p2 = p - v2;
	const vec3 v13 = v1 - v3; const vec3 p3 = p - v3;
	const vec3 nor = cross(v21, v13);

	return (sign(dot(cross(v21, nor), p1)) +
                sign(dot(cross(v32, nor), p2)) +
                sign(dot(cross(v13, nor), p3))<2.0f)
                ?
                std::fminf(std::fminf( dot2(v21*clamp01(dot(v21, p1) / dot2(v21)) - p1),
                                       dot2(v32*clamp01(dot(v32, p2) / dot2(v32)) - p2)),
                                       dot2(v13*clamp01(dot(v13, p3) / dot2(v13)) - p3))
                :
                dot(nor, p1)*dot(nor, p1) / dot2(nor);
}

// (squared) distance to a quad
inline float udSqQuad(const vec3 & p, const vec3 & v1, const vec3 & v2, const vec3 & v3, const vec3 & v4)
{
	const vec3 v21 = v2 - v1; const vec3 p1 = p - v1;
	const vec3 v32 = v3 - v2; const vec3 p2 = p - v2;
	const vec3 v43 = v4 - v3; const vec3 p3 = p - v3;
	const vec3 v14 = v1 - v4; const vec3 p4 = p - v4;
	const vec3 nor = cross(v21, v14);

	return (sign(dot(cross(v21, nor), p1)) +
                sign(dot(cross(v32, nor), p2)) +
                sign(dot(cross(v43, nor), p3)) +
                sign(dot(cross(v14, nor), p4))<3.0f)
                ?
                std::fminf(std::fminf(dot2(v21*clamp01(dot(v21, p1) / dot2(v21)) - p1),
                                      dot2(v32*clamp01(dot(v32, p2) / dot2(v32)) - p2)),
                           std::fminf(dot2(v43*clamp01(dot(v43, p3) / dot2(v43)) - p3),
                                      dot2(v14*clamp01(dot(v14, p4) / dot2(v14)) - p4)))
                :
                dot(nor, p1)*dot(nor, p1) / dot2(nor);
}

inline float sdQuad(const vec3 & p, const vec3 & v1, const vec3 & v2, const vec3 & v3, const vec3 & v4)
{
    const vec3 v21 = v2 - v1; const vec3 p1 = p - v1;
    const vec3 v32 = v3 - v2; const vec3 p2 = p - v2;
    const vec3 v43 = v4 - v3; const vec3 p3 = p - v3;
    const vec3 v14 = v1 - v4; const vec3 p4 = p - v4;
    const vec3 nor = cross(v21, v14);

    const float sig = sign( dot(nor,p1) );

    return sig * sqrtf((sign(dot(cross(v21, nor), p1)) +
                        sign(dot(cross(v32, nor), p2)) +
                        sign(dot(cross(v43, nor), p3)) +
                        sign(dot(cross(v14, nor), p4))<3.0f)
                        ?
                        std::fminf(std::fminf(dot2(v21*clamp01(dot(v21, p1) / dot2(v21)) - p1),
                                              dot2(v32*clamp01(dot(v32, p2) / dot2(v32)) - p2)),
                                   std::fminf(dot2(v43*clamp01(dot(v43, p3) / dot2(v43)) - p3),
                                              dot2(v14*clamp01(dot(v14, p4) / dot2(v14)) - p4)))
                        :
                        dot(nor, p1)*dot(nor, p1) / dot2(nor));
}

}