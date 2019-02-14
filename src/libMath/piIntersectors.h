#ifndef _INTERSECTORS_H_
#define _INTERSECTORS_H_

#include <cmath>

#include "piVecTypes.h"

namespace piLibs {

    inline float iRayBox( const vec3 & ro, const vec3 & rd,      // ray
                          const mat4x4 & tx, const vec3 & br )   // box, br (x,y,z) are the semizes, tx is the position/rotation matrix
    {
        // convert from ray to box space
	    const vec3 rdd = (tx*vec4(rd,0.0f)).xyz;
        const vec3 roo = (tx*vec4(ro,1.0f)).xyz;

	    // ray-box intersection in box space
        const vec3 m = 1.0f/rdd;
        const vec3 n = m*roo;
        const vec3 k = abs(m)*br;
	
        const vec3 t1 = -1.0f*n - k;
        const vec3 t2 = -1.0f*n + k;

	    const float tN = fmax( fmax( t1.x, t1.y ), t1.z );
	    const float tF = fmin( fmin( t2.x, t2.y ), t2.z );
	
	    if( tN > tF || tF < 0.0f) return -1.0f;

	    return tN;
    }

	// ray-axis-aligned-box intersection (could precompute m)
    inline float iRayAABox( const vec3 & ro, const vec3 & rd,      // ray
                            const vec3 & bo, const vec3 & br )     // bo = box origin, br(x,y,z) is the semi-sizes
    {
        const vec3 m = 1.0f/rd;
        const vec3 n = m*(ro-bo);
        const vec3 k = abs(m)*br;
	
        const vec3 t1 = -1.0f*n - k;
        const vec3 t2 = -1.0f*n + k;

	    const float tN = fmax( fmax( t1.x, t1.y ), t1.z );
	    const float tF = fmin( fmin( t2.x, t2.y ), t2.z );
	
	    //vec3 nor = -sign(rdd)*step(t1.yzx,t1.xyz)*step(t1.zxy,t1.xyz);

	    if( tN > tF || tF < 0.0f) return -1.0f;

	    return tN;
    }

    inline vec2 iRaySphere( const vec3 & ro, const vec3 & rd, const vec4 & sph ) // sph = (centerX,centerY,centerZ,radius)
    {
	    const vec3 oc = ro - sph.xyz;
	    const float b = dot( oc, rd );
	    const float c = dot( oc, oc ) - sph.w*sph.w;
	    float h = b*b - c;
	    if( h<0.0 ) return vec2(-1.0f);
        h = sqrtf( h );
	    return vec2( -b-h, -b+h );
    }

    inline float iRayPlane( const vec3 & ro, const vec3 & rd, const vec4 & pla )
    {
        return (-pla.w - dot(ro,pla.xyz()))/dot(pla.xyz(),rd);
    }

    inline float iRayVerticalInfiniteCylinder( const vec3 & ro, const vec3 & rd, 
                                               const vec3 & cyl )               // x, y = position,   z = radius
    {
        const vec2  d = ro.xy() - cyl.xy();
        const float a = dot( rd.xz(), rd.xz() );
        const float b = dot( rd.xz(), d );
        const float c = dot( d, d ) - cyl.z*cyl.z;
        const float t = b*b - a*c;
        if( t<0.0f ) return -1.0f;
        return -(b+sqrtf(t))/a;
    }

    // http://www.iquilezles.org/blog/?p=732
    inline float iRayInfiniteCylinder( const vec3 & ro, const vec3 & rd, 
                                       const vec3 & cc, const vec3 & ca, float ra )  // center and (normalized) axis, radius
    {
        const vec3  oc = ro - cc;
        const float a = 1.0f - dot(ca,rd)*dot(ca,rd);
        const float b = dot( oc, rd) - dot(oc,ca)*dot(rd,ca);
        const float c = dot( oc, oc) - dot(oc,ca)*dot(oc,ca) - ra*ra;
        const float t = b*b - a*c;
        if( t<0.0f ) return -1.0f;
        return -(b+sqrtf(t))/a;
    }

    // https://www.shadertoy.com/view/4lcSRn
    vec4 iRayCappedCylinder( const vec3 & ro, const vec3 & rd, 
                    const vec3 & cc, const vec3 & ca, float cr, float ch ) // cc center, ca orientation axis, cr radius, ch height
    {
        const vec3  oc = ro - cc;

        const float card = dot(ca,rd);
        const float caoc = dot(ca,oc);
    
        const float a = 1.0f - card*card;
        const float b = dot( oc, rd) - caoc*card;
        const float c = dot( oc, oc) - caoc*caoc - cr*cr;
        float h = b*b - a*c;
        if( h<0.0 ) return vec4(-1.0f);
        h = sqrtf(h);
        const float t1 = (-b-h)/a;
        const float t2 = (-b+h)/a;

        const float y = caoc + t1*card;

        // body
        if( fabsf(y)<ch/2.0f ) return vec4( t1, normalize( oc+t1*rd - ca*y ) );
    
        // caps
        const float sy = (y<0.0)?-1.0f:1.0f;
        float tp = ( sy*ch/2.0f - caoc)/card;
        if( tp>t1 && tp<t2 )
        {
            return vec4(tp,ca*sy);
        }

        return vec4(-1.0);
    }


    // https://www.shadertoy.com/view/4sBGDy
    inline float iTorus( const vec3 & ro, const vec3 & rd, const vec2 & torus ) // x = external radius, y = internal radius
    {
	    const float Ra2 = torus.x*torus.x;
	    const float ra2 = torus.y*torus.y;
	
	    const float m = dot(ro,ro);
	    const float n = dot(ro,rd);
		
	    const float k = (m - ra2 - Ra2)/2.0f;
	    const float a = n;
	    const float b = n*n + Ra2*rd.z*rd.z + k;
	    const float c = k*n + Ra2*ro.z*rd.z;
	    const float d = k*k + Ra2*ro.z*ro.z - Ra2*ra2;
	
        //----------------------------------

	    float p = -3.0f*a*a     + 2.0f*b;
	    float q =  2.0f*a*a*a   - 2.0f*a*b   + 2.0f*c;
	    float r = -3.0f*a*a*a*a + 4.0f*a*a*b - 8.0f*a*c + 4.0f*d;
	    p /= 3.0f;
	    r /= 3.0f;
	    float Q = p*p + r;
	    float R = 3.0f*r*p - p*p*p - q*q;
	
	    float h = R*R - Q*Q*Q;
	    float z = 0.0f;
	    if( h < 0.0f )
	    {
		    float sQ = sqrtf(Q);
		    z = 2.0f*sQ*cosf( acosf(R/(sQ*Q)) / 3.0f );
	    }
	    else
	    {
		    float sQ = powf( sqrtf(h) + fabsf(R), 1.0f/3.0f );
		    z = copysignf( fabsf( sQ + Q/sQ ), R );

	    }
	
	    z = p - z;
	
        //----------------------------------
	
	    float d1 = z   - 3.0f*p;
	    float d2 = z*z - 3.0f*r;

	    if( fabsf(d1)<1.0e-4 )
	    {
		    if( d2<0.0f ) return -1.0f;
		    d2 = sqrtf(d2);
	    }
	    else
	    {
		    if( d1<0.0f ) return -1.0f;
		    d1 = sqrtf( d1*0.5f );
		    d2 = q/d1;
	    }

        //----------------------------------
	
	    float result = 1e20f;

	    h = d1*d1 - z + d2;
	    if( h>0.0f )
	    {
		    h = sqrtf(h);
		    float t1 = -d1 - h - a;
		    float t2 = -d1 + h - a;
		         if( t1>0.0f ) result=t1;
		    else if( t2>0.0f ) result=t2;
	    }

	    h = d1*d1 - z - d2;
	    if( h>0.0f )
	    {
		    h = sqrtf(h);
		    float t1 = d1 - h - a;
		    float t2 = d1 + h - a;
		         if( t1>0.0f ) result=fminf(result,t1);
		    else if( t2>0.0f ) result=fminf(result,t2);
	    }

	    return result;
    }

} // namespace piLibs

#endif