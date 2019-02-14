#pragma once

#include <cmath>
#include <cstdint>

namespace piLibs
{

    //--------------------------------------------------------------------------------
    // ivec2 
    //--------------------------------------------------------------------------------

    struct ivec2
    {
        int x, y;

        ivec2() {}

        explicit ivec2(int a, int b)      { x = a;    y = b; }
		explicit ivec2(const uint8_t *v)  { x = v[0]; y = v[1]; }
		explicit ivec2(const uint16_t *v) { x = v[0]; y = v[1]; }
		explicit ivec2(const uint32_t *v) { x = v[0]; y = v[1]; }

        int & operator [](int i) { return ((int*)this)[i]; }
        const int & operator [](int i) const { return ((int*)this)[i]; }

        ivec2 & operator =(ivec2  const & v) { x = v.x;  y = v.y;  return *this; }
        ivec2 & operator+=(int const & s)    { x += s;   y += s;   return *this; }
        ivec2 & operator+=(ivec2  const & v) { x += v.x; y += v.y; return *this; }
        ivec2 & operator-=(int const & s)    { x -= s;   y -= s;   return *this; }
        ivec2 & operator-=(ivec2  const & v) { x -= v.x; y -= v.y; return *this; }
        ivec2 & operator*=(int const & s)    { x *= s;   y *= s;   return *this; }
        ivec2 & operator*=(ivec2  const & v) { x *= v.x; y *= v.y; return *this; }
        ivec2 & operator/=(int const & s)    { x /= s;   y /= s;   return *this; }
        ivec2 & operator/=(ivec2  const & v) { x /= v.x; y /= v.y; return *this; }

        ivec2 xx() const { return ivec2(x, x); }
        ivec2 xy() const { return ivec2(x, y); }
        ivec2 yx() const { return ivec2(y, x); }
        ivec2 yy() const { return ivec2(y, y); }
    };


	//--------------------------------------------------------------------------------
	// ivec3 
	//--------------------------------------------------------------------------------

	struct ivec3
	{
		int x, y, z;

		ivec3() {}

		explicit ivec3(int a, int b, int c) { x = a;    y = b;    z = c; }
		explicit ivec3(int s)               { x = s;    y = s;    z = s; }
		explicit ivec3(const uint8_t *v)    { x = v[0]; y = v[1]; z = v[2]; }
		explicit ivec3(const uint16_t *v)   { x = v[0]; y = v[1]; z = v[2]; }
		explicit ivec3(const uint32_t *v)   { x = v[0]; y = v[1]; z = v[2]; }

		int & operator [](int i) { return ((int*)this)[i]; }
		const int & operator [](int i) const { return ((int*)this)[i]; }

		ivec3 & operator =(ivec3 const & v) { x = v.x;  y = v.y;  z = v.z;  return *this; }
		ivec3 & operator+=(int   const & s) { x += s;   y += s;   z += s;   return *this; }
		ivec3 & operator+=(ivec3 const & v) { x += v.x; y += v.y; z += v.z; return *this; }
		ivec3 & operator-=(int   const & s) { x -= s;   y -= s;   z -= s;   return *this; }
		ivec3 & operator-=(ivec3 const & v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		ivec3 & operator*=(int   const & s) { x *= s;   y *= s;   z *= s;   return *this; }
		ivec3 & operator*=(ivec3 const & v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		ivec3 & operator/=(int   const & s) { x /= s;   y /= s;   z /= s;   return *this; }
		ivec3 & operator/=(ivec3 const & v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		const bool operator== (const ivec3 & v) const { return x == v.x && y == v.y && z == v.z; }
		const bool operator== (ivec3 & v) const { return x == v.x && y == v.y && z == v.z; }
		const bool operator!= (const ivec3 & v) const { return x != v.x || y != v.y || z != v.z; }
		const bool operator!= (ivec3 & v) const { return x != v.x || y != v.y || z != v.z; }
	};

	//--------------------------------------------------------------------------------
	// ivec4
	//--------------------------------------------------------------------------------

	struct ivec4
	{
		int x, y, z, w;

		ivec4() {}

		explicit ivec4(int a, int b, int c, int d) { x = a;    y = b;    z = c;    w = d; }
		explicit ivec4(int s)                      { x = s;    y = s;    z = s;    w = s; }
		explicit ivec4(const uint32_t *v)          { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }

		int & operator [](int i) { return ((int*)this)[i]; }
		const int & operator [](int i) const { return ((int*)this)[i]; }

		ivec4 & operator =(ivec4 const & v) { x = v.x;  y = v.y;  z = v.z;  w = v.w;  return *this; }
		ivec4 & operator+=(int   const & s) { x += s;   y += s;   z += s;   w += s;   return *this; }
		ivec4 & operator+=(ivec4 const & v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		ivec4 & operator-=(int   const & s) { x -= s;   y -= s;   z -= s;   w -= s;     return *this; }
		ivec4 & operator-=(ivec4 const & v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
		ivec4 & operator*=(int   const & s) { x *= s;   y *= s;   z *= s;   w *= s;   return *this; }
		ivec4 & operator*=(ivec4 const & v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
		ivec4 & operator/=(int   const & s) { x /= s;   y /= s;   z /= s;   w /= s;   return *this; }
		ivec4 & operator/=(ivec4 const & v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

		const bool operator== (const ivec4 & v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
		const bool operator== (ivec4 & v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
		const bool operator!= (const ivec4 & v) const { return x != v.x || y != v.y || z != v.z && w != v.w; }
		const bool operator!= (ivec4 & v) const { return x != v.x || y != v.y || z != v.z && w != v.w; }
	};


	//--------------------------------------------------------------------------------
	// vec2 
	//--------------------------------------------------------------------------------

	struct vec2
	{
		float x, y;

		vec2() {}

		explicit vec2(float a)               { x = a;          y = a; }
		explicit vec2(float a, float b)      { x = a;          y = b; }
		explicit vec2(float const * const v) { x = v[0];       y = v[1]; }
		explicit vec2(const ivec2 & v)       { x = (float)v.x; y = (float)v.y; }

		float & operator [](int i) { return ((float*)this)[i]; }
		const float & operator [](int i) const { return ((float*)this)[i]; }

		vec2 operator-(void) const { return vec2(-x, -y); }
		vec2 & operator =(vec2  const & v) { x = v.x;  y = v.y;  return *this; }
		vec2 & operator+=(float const & s) { x += s;   y += s;   return *this; }
		vec2 & operator+=(vec2  const & v) { x += v.x; y += v.y; return *this; }
		vec2 & operator-=(float const & s) { x -= s;   y -= s;   return *this; }
		vec2 & operator-=(vec2  const & v) { x -= v.x; y -= v.y; return *this; }
		vec2 & operator*=(float const & s) { x *= s;   y *= s;   return *this; }
		vec2 & operator*=(vec2  const & v) { x *= v.x; y *= v.y; return *this; }
		vec2 & operator/=(float const & s) { x /= s;   y /= s;   return *this; }
		vec2 & operator/=(vec2  const & v) { x /= v.x; y /= v.y; return *this; }

		vec2 xx() const { return vec2(x, x); }
		vec2 xy() const { return vec2(x, y); }
		vec2 yx() const { return vec2(y, x); }
		vec2 yy() const { return vec2(y, y); }
	};

	//--------------------------------------------------------------------------------
	// vec3 
	//--------------------------------------------------------------------------------

	struct vec3
	{
		float x, y, z;

		vec3() {}

		explicit vec3(float a)                   { x = a;          y = a;          z = a; }
		explicit vec3(float a, float b, float c) { x = a;          y = b;          z = c; }
		explicit vec3(const float * v)           { x = v[0];       y = v[1];       z = v[2]; }
		explicit vec3(vec2 const & v, float s)   { x = v.x;        y = v.y;        z = s; }
		explicit vec3(float s, vec2 const & v)   { x = s;          y = v.x;        z = v.y; }
		explicit vec3(const ivec3 & v)           { x = float(v.x); y = float(v.y); z = float(v.z); }

		float & operator [](int i) { return ((float*)this)[i]; }
		const float & operator [](int i) const { return ((float*)this)[i]; }

		vec3 operator-(void) const { return vec3(-x, -y, -z); }
		vec3 & operator =(vec3  const & v) { x = v.x;  y = v.y;  z = v.z;  return *this; }
		vec3 & operator+=(float const & s) { x += s;   y += s;   z += s;   return *this; }
		vec3 & operator+=(vec3  const & v) { x += v.x; y += v.y; z += v.z; return *this; }
		vec3 & operator-=(float const & s) { x -= s;   y -= s;   z -= s;   return *this; }
		vec3 & operator-=(vec3  const & v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		vec3 & operator*=(float const & s) { x *= s;   y *= s;   z *= s;   return *this; }
		vec3 & operator*=(vec3  const & v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		vec3 & operator/=(float const & s) { x /= s;   y /= s;   z /= s;   return *this; }
		vec3 & operator/=(vec3  const & v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		vec2 xx() const { return vec2(x, x); }
		vec2 xy() const { return vec2(x, y); }
		vec2 xz() const { return vec2(x, z); }
		vec2 yx() const { return vec2(y, x); }
		vec2 yy() const { return vec2(y, y); }
		vec2 yz() const { return vec2(y, z); }
		vec2 zx() const { return vec2(z, x); }
		vec2 zy() const { return vec2(z, y); }
		vec2 zz() const { return vec2(z, z); }

		vec3 xxx() const { return vec3(x, x, x); }
		vec3 xxy() const { return vec3(x, x, y); }
		vec3 xxz() const { return vec3(x, x, z); }
		vec3 xyx() const { return vec3(x, y, x); }
		vec3 xyy() const { return vec3(x, y, y); }
		vec3 xyz() const { return vec3(x, y, z); }
		vec3 xzx() const { return vec3(x, z, x); }
		vec3 xzy() const { return vec3(x, z, y); }
		vec3 xzz() const { return vec3(x, z, z); }
		vec3 yxx() const { return vec3(y, x, x); }
		vec3 yxy() const { return vec3(y, x, y); }
		vec3 yxz() const { return vec3(y, x, z); }
		vec3 yyx() const { return vec3(y, y, x); }
		vec3 yyy() const { return vec3(y, y, y); }
		vec3 yyz() const { return vec3(y, y, z); }
		vec3 yzx() const { return vec3(y, z, x); }
		vec3 yzy() const { return vec3(y, z, y); }
		vec3 yzz() const { return vec3(y, z, z); }
		vec3 zxx() const { return vec3(z, x, x); }
		vec3 zxy() const { return vec3(z, x, y); }
		vec3 zxz() const { return vec3(z, x, z); }
		vec3 zyx() const { return vec3(z, y, x); }
		vec3 zyy() const { return vec3(z, y, y); }
		vec3 zyz() const { return vec3(z, y, z); }
		vec3 zzx() const { return vec3(z, z, x); }
		vec3 zzy() const { return vec3(z, z, y); }
		vec3 zzz() const { return vec3(z, z, z); }
	};

	//--------------------------------------------------------------------------------
	// vec4 
	//--------------------------------------------------------------------------------

	struct vec4
	{
		float x, y, z, w;

		vec4() {}

		explicit vec4(float a, float b, float c, float d) { x = a;    y = b;    z = c;    w = d; }
		explicit vec4(float const * const v)              { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }
		explicit vec4(vec3 const & v, const float s)      { x = v.x;  y = v.y;  z = v.z;  w = s; }
		explicit vec4(vec2 const & a, vec2 const & b)     { x = a.x;  y = a.y;  z = b.x;  w = b.y; }
		explicit vec4(const float s, vec3 const & v)      { x = s;    y = v.x; 	z = v.y;  w = v.z; }
		explicit vec4(float s)                            { x = s;    y = s;    z = s;    w = s; }

		float & operator [](int i) { return ((float*)this)[i]; }
		const float & operator [](int i) const { return ((float*)this)[i]; }

		vec4 operator-(void) const { return vec4(-x, -y, -z, -w); }
		vec4 & operator =(vec4  const & v) { x = v.x;  y = v.y;  z = v.z;  w = v.w;  return *this; }
		vec4 & operator+=(float const & s) { x += s;   y += s;   z += s;   w += s;   return *this; }
		vec4 & operator+=(vec4  const & v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		vec4 & operator-=(float const & s) { x -= s;   y -= s;   z -= s;   w -= s;   return *this; }
		vec4 & operator-=(vec4  const & v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
		vec4 & operator*=(float const & s) { x *= s;   y *= s;   z *= s;   w *= s;   return *this; }
		vec4 & operator*=(vec4  const & v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
		vec4 & operator/=(float const & s) { x /= s;   y /= s;   z /= s;   w /= s;   return *this; }
		vec4 & operator/=(vec4  const & v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

		vec2 xx() const { return vec2(x, x); }
		vec2 xy() const { return vec2(x, y); }
		vec2 xz() const { return vec2(x, z); }
		vec2 yx() const { return vec2(y, x); }
		vec2 yy() const { return vec2(y, y); }
		vec2 yz() const { return vec2(y, z); }
		vec2 zx() const { return vec2(z, x); }
		vec2 zy() const { return vec2(z, y); }
		vec2 zz() const { return vec2(z, z); }
		vec2 wz() const { return vec2(w, z); }

		vec3 xxx() const { return vec3(x, x, x); }
		vec3 xxy() const { return vec3(x, x, y); }
		vec3 xxz() const { return vec3(x, x, z); }
		vec3 xxw() const { return vec3(x, x, w); }
		vec3 xyx() const { return vec3(x, y, x); }
		vec3 xyy() const { return vec3(x, y, y); }
		vec3 xyz() const { return vec3(x, y, z); }
		vec3 xyw() const { return vec3(x, y, w); }
		vec3 xzx() const { return vec3(x, z, x); }
		vec3 xzy() const { return vec3(x, z, y); }
		vec3 xzz() const { return vec3(x, z, z); }
		vec3 xzw() const { return vec3(x, z, w); }
		vec3 yxx() const { return vec3(y, x, x); }
		vec3 yxy() const { return vec3(y, x, y); }
		vec3 yxz() const { return vec3(y, x, z); }
		vec3 yxw() const { return vec3(y, x, w); }
		vec3 yyx() const { return vec3(y, y, x); }
		vec3 yyy() const { return vec3(y, y, y); }
		vec3 yyz() const { return vec3(y, y, z); }
		vec3 yyw() const { return vec3(y, y, w); }
		vec3 yzx() const { return vec3(y, z, x); }
		vec3 yzy() const { return vec3(y, z, y); }
		vec3 yzz() const { return vec3(y, z, z); }
		vec3 yzw() const { return vec3(y, z, w); }
		vec3 zxx() const { return vec3(z, x, x); }
		vec3 zxy() const { return vec3(z, x, y); }
		vec3 zxz() const { return vec3(z, x, z); }
		vec3 zxw() const { return vec3(z, x, w); }
		vec3 zyx() const { return vec3(z, y, x); }
		vec3 zyy() const { return vec3(z, y, y); }
		vec3 zyz() const { return vec3(z, y, z); }
		vec3 zzx() const { return vec3(z, z, x); }
		vec3 zzy() const { return vec3(z, z, y); }
		vec3 zzz() const { return vec3(z, z, z); }
		vec3 zzw() const { return vec3(z, z, w); }
		vec3 www() const { return vec3(w, w, w); }
	};

	//--------------------------------------------------------------------------------
	// vec2d 
	//--------------------------------------------------------------------------------

	struct vec2d
	{
		double x, y;

		vec2d() {}

		explicit vec2d(double a)               { x = a;           y = a; }
		explicit vec2d(double a, double b)     { x = a;           y = b; }
		explicit vec2d(double const * const v) { x = v[0];        y = v[1]; }
		explicit vec2d(const ivec2 & v)        { x = (double)v.x; y = (double)v.y; }
		
		double & operator [](int i) { return ((double*)this)[i]; }
		const double & operator [](int i) const { return ((double*)this)[i]; }

		vec2d operator-(void) const { return vec2d(-x, -y); }
		vec2d & operator =(vec2d  const & v) { x = v.x;  y = v.y;  return *this; }
		vec2d & operator+=(double const & s) { x += s;   y += s;   return *this; }
		vec2d & operator+=(vec2d  const & v) { x += v.x; y += v.y; return *this; }
		vec2d & operator-=(double const & s) { x -= s;   y -= s;   return *this; }
		vec2d & operator-=(vec2d  const & v) { x -= v.x; y -= v.y; return *this; }
		vec2d & operator*=(double const & s) { x *= s;   y *= s;   return *this; }
		vec2d & operator*=(vec2d  const & v) { x *= v.x; y *= v.y; return *this; }
		vec2d & operator/=(double const & s) { x /= s;   y /= s;   return *this; }
		vec2d & operator/=(vec2d  const & v) { x /= v.x; y /= v.y; return *this; }

		vec2d xx() const { return vec2d(x, x); }
		vec2d xy() const { return vec2d(x, y); }
		vec2d yx() const { return vec2d(y, x); }
		vec2d yy() const { return vec2d(y, y); }
	};

	//--------------------------------------------------------------------------------
	// vec3d 
	//--------------------------------------------------------------------------------

	struct vec3d
	{
		double x, y, z;

		vec3d() {}
		
		explicit vec3d(double a)                     { x = a;    y = a;    z = a; }
		explicit vec3d(double a, double b, double c) { x = a;    y = b;    z = c; }
		
		explicit vec3d(const double * v)             { x = v[0]; y = v[1]; z = v[2]; }
		explicit vec3d(const vec2d & v, double s)    { x = v.x;  y = v.y;  z = s; }
		explicit vec3d(double s, vec2d const & v)    { x = s;    y = v.x;  z = v.y; }
		explicit vec3d(const ivec3 & v)              { x = double(v.x); y = double(v.y); z = double(v.z); }
		
		double & operator [](int i) { return ((double*)this)[i]; }
		const double & operator [](int i) const { return ((double*)this)[i]; }

		vec3d operator-(void) const { return vec3d(-x, -y, -z); }
		vec3d & operator =(vec3d  const & v) { x = v.x;  y = v.y;  z = v.z;  return *this; }
		vec3d & operator+=(double const & s) { x += s;   y += s;   z += s;   return *this; }
		vec3d & operator+=(vec3d  const & v) { x += v.x; y += v.y; z += v.z; return *this; }
		vec3d & operator-=(double const & s) { x -= s;   y -= s;   z -= s;   return *this; }
		vec3d & operator-=(vec3d  const & v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		vec3d & operator*=(double const & s) { x *= s;   y *= s;   z *= s;   return *this; }
		vec3d & operator*=(vec3d  const & v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		vec3d & operator/=(double const & s) { x /= s;   y /= s;   z /= s;   return *this; }
		vec3d & operator/=(vec3d  const & v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		vec2d xx() const { return vec2d(x, x); }
		vec2d xy() const { return vec2d(x, y); }
		vec2d xz() const { return vec2d(x, z); }
		vec2d yx() const { return vec2d(y, x); }
		vec2d yy() const { return vec2d(y, y); }
		vec2d yz() const { return vec2d(y, z); }
		vec2d zx() const { return vec2d(z, x); }
		vec2d zy() const { return vec2d(z, y); }
		vec2d zz() const { return vec2d(z, z); }

		vec3d xxx() const { return vec3d(x, x, x); }
		vec3d xxy() const { return vec3d(x, x, y); }
		vec3d xxz() const { return vec3d(x, x, z); }
		vec3d xyx() const { return vec3d(x, y, x); }
		vec3d xyy() const { return vec3d(x, y, y); }
		vec3d xyz() const { return vec3d(x, y, z); }
		vec3d xzx() const { return vec3d(x, z, x); }
		vec3d xzy() const { return vec3d(x, z, y); }
		vec3d xzz() const { return vec3d(x, z, z); }
		vec3d yxx() const { return vec3d(y, x, x); }
		vec3d yxy() const { return vec3d(y, x, y); }
		vec3d yxz() const { return vec3d(y, x, z); }
		vec3d yyx() const { return vec3d(y, y, x); }
		vec3d yyy() const { return vec3d(y, y, y); }
		vec3d yyz() const { return vec3d(y, y, z); }
		vec3d yzx() const { return vec3d(y, z, x); }
		vec3d yzy() const { return vec3d(y, z, y); }
		vec3d yzz() const { return vec3d(y, z, z); }
		vec3d zxx() const { return vec3d(z, x, x); }
		vec3d zxy() const { return vec3d(z, x, y); }
		vec3d zxz() const { return vec3d(z, x, z); }
		vec3d zyx() const { return vec3d(z, y, x); }
		vec3d zyy() const { return vec3d(z, y, y); }
		vec3d zyz() const { return vec3d(z, y, z); }
		vec3d zzx() const { return vec3d(z, z, x); }
		vec3d zzy() const { return vec3d(z, z, y); }
		vec3d zzz() const { return vec3d(z, z, z); }
	};

	//--------------------------------------------------------------------------------
	// vec4d 
	//--------------------------------------------------------------------------------

	struct vec4d
	{
		double x, y, z, w;

		vec4d() {}

		explicit vec4d(double a, double b, double c, double d) { x = a;    y = b;    z = c;    w = d; }
		explicit vec4d(double const * const v)                 { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }
		explicit vec4d(const vec2d & a, const vec2d & b)       { x = a.x;  y = a.y;  z = b.x;  w = b.y; }
		explicit vec4d(const vec3d & v, const double s)        { x = v.x;  y = v.y;  z = v.z;  w = s; }
		explicit vec4d(const double s, const vec3d & v)        { x = s;    y = v.x;  z = v.y;  w = v.z; }
		explicit vec4d(double s)                               { x = s;    y = s;    z = s;    w = s; }

		double & operator [](int i) { return ((double*)this)[i]; }
		const double & operator [](int i) const { return ((double*)this)[i]; }

		vec4d & operator =(vec4d  const & v) { x = v.x;  y = v.y;  z = v.z;  w = v.w;  return *this; }
		vec4d & operator+=(double const & s) { x += s;   y += s;   z += s;   w += s;   return *this; }
		vec4d & operator+=(vec4d  const & v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		vec4d & operator-=(double const & s) { x -= s;   y -= s;   z -= s;   w -= s;   return *this; }
		vec4d & operator-=(vec4d  const & v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
		vec4d & operator*=(double const & s) { x *= s;   y *= s;   z *= s;   w *= s;   return *this; }
		vec4d & operator*=(vec4d  const & v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
		vec4d & operator/=(double const & s) { x /= s;   y /= s;   z /= s;   w /= s;   return *this; }
		vec4d & operator/=(vec4d  const & v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

		vec2d xx() const { return vec2d(x, x); }
		vec2d xy() const { return vec2d(x, y); }
		vec2d xz() const { return vec2d(x, z); }
		vec2d yx() const { return vec2d(y, x); }
		vec2d yy() const { return vec2d(y, y); }
		vec2d yz() const { return vec2d(y, z); }
		vec2d zx() const { return vec2d(z, x); }
		vec2d zy() const { return vec2d(z, y); }
		vec2d zz() const { return vec2d(z, z); }
		vec2d wz() const { return vec2d(w, z); }

		vec3d xxx() const { return vec3d(x, x, x); }
		vec3d xxy() const { return vec3d(x, x, y); }
		vec3d xxz() const { return vec3d(x, x, z); }
		vec3d xxw() const { return vec3d(x, x, w); }
		vec3d xyx() const { return vec3d(x, y, x); }
		vec3d xyy() const { return vec3d(x, y, y); }
		vec3d xyz() const { return vec3d(x, y, z); }
		vec3d xyw() const { return vec3d(x, y, w); }
		vec3d xzx() const { return vec3d(x, z, x); }
		vec3d xzy() const { return vec3d(x, z, y); }
		vec3d xzz() const { return vec3d(x, z, z); }
		vec3d xzw() const { return vec3d(x, z, w); }
		vec3d yxx() const { return vec3d(y, x, x); }
		vec3d yxy() const { return vec3d(y, x, y); }
		vec3d yxz() const { return vec3d(y, x, z); }
		vec3d yxw() const { return vec3d(y, x, w); }
		vec3d yyx() const { return vec3d(y, y, x); }
		vec3d yyy() const { return vec3d(y, y, y); }
		vec3d yyz() const { return vec3d(y, y, z); }
		vec3d yyw() const { return vec3d(y, y, w); }
		vec3d yzx() const { return vec3d(y, z, x); }
		vec3d yzy() const { return vec3d(y, z, y); }
		vec3d yzz() const { return vec3d(y, z, z); }
		vec3d yzw() const { return vec3d(y, z, w); }
		vec3d zxx() const { return vec3d(z, x, x); }
		vec3d zxy() const { return vec3d(z, x, y); }
		vec3d zxz() const { return vec3d(z, x, z); }
		vec3d zxw() const { return vec3d(z, x, w); }
		vec3d zyx() const { return vec3d(z, y, x); }
		vec3d zyy() const { return vec3d(z, y, y); }
		vec3d zyz() const { return vec3d(z, y, z); }
		vec3d zzx() const { return vec3d(z, z, x); }
		vec3d zzy() const { return vec3d(z, z, y); }
		vec3d zzz() const { return vec3d(z, z, z); }
		vec3d zzw() const { return vec3d(z, z, w); }
		vec3d www() const { return vec3d(w, w, w); }
	};


	//--------------------------------------------------------------------------------
	// mat2x2
	//--------------------------------------------------------------------------------

	struct mat2x2
	{
		float m[4];

		mat2x2() {}

		explicit mat2x2(float a0, float a1, float a2, float a3) { m[0] = a0; m[1] = a1; m[2] = a2; m[3] = a3; }

		float & operator [](int i) { return m[i]; }
		const float & operator [](int i) const { return m[i]; }

		static inline mat2x2 identity() { return mat2x2(1.0f, 0.0f, 0.0f, 1.0f); }
	};

	//--------------------------------------------------------------------------------
	// mat2x2d
	//--------------------------------------------------------------------------------

	struct mat2x2d
	{
		double m[4];

		mat2x2d() {}

		explicit mat2x2d(double a0, double a1, double a2, double a3) { m[0] = a0; m[1] = a1; m[2] = a2; m[3] = a3; }

		double & operator [](int i) { return m[i]; }
		const double & operator [](int i) const { return m[i]; }

		static inline mat2x2d identity() { return mat2x2d(1.0, 0.0, 0.0, 1.0); }
	};


	//--------------------------------------------------------------------------------
	// mat3x3 
	//--------------------------------------------------------------------------------

	struct mat3x3
	{
		float m[9];

		mat3x3() {}

		explicit mat3x3(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8)
		{
			m[0] = a0; m[1] = a1; m[2] = a2;
			m[3] = a3; m[4] = a4; m[5] = a5;
			m[6] = a6; m[7] = a7; m[8] = a8;
		}

		explicit mat3x3(const vec3 & a, const vec3 & b, const vec3 & c)
		{
			m[0] = a.x; m[1] = b.x; m[2] = c.x;
			m[3] = a.y; m[4] = b.y; m[5] = c.y;
			m[6] = a.z; m[7] = b.z; m[8] = c.z;
		}

		float & operator [](int i) { return m[i]; }
		const float & operator [](int i) const { return m[i]; }

		vec3 x() const { return vec3(m[0], m[3], m[6]); }
		vec3 y() const { return vec3(m[1], m[4], m[7]); }
		vec3 z() const { return vec3(m[2], m[5], m[8]); }

		static inline mat3x3 identity() { return mat3x3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	};

	//--------------------------------------------------------------------------------
	// mat3x3d 
	//--------------------------------------------------------------------------------

	struct mat3x3d
	{
		double m[9];

		mat3x3d() {}

		explicit mat3x3d(double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
		{
			m[0] = a0; m[1] = a1; m[2] = a2;
			m[3] = a3; m[4] = a4; m[5] = a5;
			m[6] = a6; m[7] = a7; m[8] = a8;
		}

		double & operator [](int i) { return m[i]; }
		const double & operator [](int i) const { return m[i]; }

		vec3d x() const { return vec3d(m[0], m[3], m[6]); }
		vec3d y() const { return vec3d(m[1], m[4], m[7]); }
		vec3d z() const { return vec3d(m[2], m[5], m[8]); }

		static inline mat3x3d identity() { return mat3x3d(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0); }
	};

	//--------------------------------------------------------------------------------
	// mat4x4 
	//--------------------------------------------------------------------------------

	struct mat4x4
	{
		float m[16];

		mat4x4() {}

		explicit mat4x4(float a00, float a01, float a02, float a03,
			float a04, float a05, float a06, float a07,
			float a08, float a09, float a10, float a11,
			float a12, float a13, float a14, float a15)
		{
			m[0] = a00; m[1] = a01; m[2] = a02; m[3] = a03;
			m[4] = a04; m[5] = a05; m[6] = a06; m[7] = a07;
			m[8] = a08; m[9] = a09; m[10] = a10; m[11] = a11;
			m[12] = a12; m[13] = a13; m[14] = a14; m[15] = a15;
		}

		explicit mat4x4(const float *v)
		{
			m[0] = v[0]; m[1] = v[1]; m[2] = v[2]; m[3] = v[3];
			m[4] = v[4]; m[5] = v[5]; m[6] = v[6]; m[7] = v[7];
			m[8] = v[8]; m[9] = v[9]; m[10] = v[10]; m[11] = v[11];
			m[12] = v[12]; m[13] = v[13]; m[14] = v[14]; m[15] = v[15];
		}

		float & operator [](int i) { return m[i]; }
		const float & operator [](int i) const { return m[i]; }

		static inline mat4x4 identity() { return mat4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	};

	//--------------------------------------------------------------------------------
	// mat4x4d 
	//--------------------------------------------------------------------------------

	struct mat4x4d
	{
		double m[16];

		mat4x4d() {}

		explicit mat4x4d(double a00, double a01, double a02, double a03,
			double a04, double a05, double a06, double a07,
			double a08, double a09, double a10, double a11,
			double a12, double a13, double a14, double a15)
		{
			m[0] = a00; m[1] = a01; m[2] = a02; m[3] = a03;
			m[4] = a04; m[5] = a05; m[6] = a06; m[7] = a07;
			m[8] = a08; m[9] = a09; m[10] = a10; m[11] = a11;
			m[12] = a12; m[13] = a13; m[14] = a14; m[15] = a15;
		}

		explicit mat4x4d(const double *v)
		{
			m[0] = v[0]; m[1] = v[1]; m[2] = v[2]; m[3] = v[3];
			m[4] = v[4]; m[5] = v[5]; m[6] = v[6]; m[7] = v[7];
			m[8] = v[8]; m[9] = v[9]; m[10] = v[10]; m[11] = v[11];
			m[12] = v[12]; m[13] = v[13]; m[14] = v[14]; m[15] = v[15];
		}

		double & operator [](int i) { return m[i]; }
		const double & operator [](int i) const { return m[i]; }

		static inline mat4x4d identity() { return mat4x4d(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0); }
	};

	//--------------------------------------------------------------------------------
	// bound2
	//--------------------------------------------------------------------------------

	struct bound2
	{
		float mMinX;
		float mMaxX;
		float mMinY;
		float mMaxY;

		bound2() {}

		explicit bound2(float mix, float max, float miy, float may)         { mMinX = mix;     mMaxX = max;     mMinY = miy;     mMaxY = may; }
		explicit bound2(float infi)                                         { mMinX = infi;    mMaxX = -infi;   mMinY = infi;    mMaxY = -infi; }
		explicit bound2(float const * const v)                              { mMinX = v[0];    mMaxX = v[1];    mMinY = v[2];    mMaxY = v[3]; }
		explicit bound2(float const * const vmin, float const * const vmax) { mMinX = vmin[0]; mMaxX = vmax[0]; mMinY = vmin[1]; mMaxY = vmax[1]; }
		explicit bound2(const vec2 & mi, const vec2 & ma)                   { mMinX = mi.x;    mMaxX = ma.x;    mMinY = mi.y;    mMaxY = ma.y; }

		float & operator [](int i) { return ((float*)this)[i]; }
		const float & operator [](int i) const { return ((float*)this)[i]; }
	};

	//--------------------------------------------------------------------------------
	// bound2d
	//--------------------------------------------------------------------------------

	struct bound2d
	{
		double mMinX;
		double mMaxX;
		double mMinY;
		double mMaxY;

		bound2d() {}

		explicit bound2d(double mix, double max, double miy, double may) { mMinX = mix; mMaxX = max; mMinY = miy; mMaxY = may; }
		explicit bound2d(double infi) { mMinX = infi; mMaxX = -infi; mMinY = infi; mMaxY = -infi; }
		explicit bound2d(double const * const v) { mMinX = v[0]; mMaxX = v[1]; mMinY = v[2]; mMaxY = v[3]; }
		explicit bound2d(double const * const vmin, double const * const vmax) { mMinX = vmin[0]; mMaxX = vmax[0]; mMinY = vmin[1]; mMaxY = vmax[1]; }
		explicit bound2d(const vec2d & mi, const vec2d & ma) { mMinX = mi.x; mMaxX = ma.x; mMinY = mi.y; mMaxY = ma.y; }

		double & operator [](int i) { return ((double*)this)[i]; }
		const double & operator [](int i) const { return ((double*)this)[i]; }
	};

	//--------------------------------------------------------------------------------
	// bound3 
	//--------------------------------------------------------------------------------

	struct bound3
	{
		float mMinX;
		float mMaxX;
		float mMinY;
		float mMaxY;
		float mMinZ;
		float mMaxZ;

		bound3() {}

		explicit bound3(float mix, float max, float miy, float may, float miz, float maz) { mMinX = mix; mMaxX = max; mMinY = miy; mMaxY = may; mMinZ = miz; mMaxZ = maz; }
		explicit bound3(float infi) { mMinX = infi; mMaxX = -infi; mMinY = infi; mMaxY = -infi; mMinZ = infi; mMaxZ = -infi; }
		explicit bound3(float const * const v) { mMinX = v[0]; mMaxX = v[1]; mMinY = v[2]; mMaxY = v[3]; mMinZ = v[4]; mMaxZ = v[5]; }
		explicit bound3(float const * const vmin, float const * const vmax) { mMinX = vmin[0]; mMaxX = vmax[0]; mMinY = vmin[1]; mMaxY = vmax[1]; mMinZ = vmin[2]; mMaxZ = vmax[2]; }
		explicit bound3(const vec3 & mi, const vec3 & ma) { mMinX = mi.x; mMaxX = ma.x; mMinY = mi.y; mMaxY = ma.y; mMinZ = mi.z; mMaxZ = ma.z; }
		explicit bound3(const vec3 & mima ) { mMinX = mima.x; mMaxX = mima.x; mMinY = mima.y; mMaxY = mima.y; mMinZ = mima.z; mMaxZ = mima.z; }

		float & operator [](int i) { return ((float*)this)[i]; }
		const float & operator [](int i) const { return ((float*)this)[i]; }

		bound2 xy() const { return bound2(mMinX, mMaxX, mMinY, mMaxY); }
		bound2 xz() const { return bound2(mMinX, mMaxX, mMinZ, mMaxZ); }
		bound2 yz() const { return bound2(mMinY, mMaxY, mMinZ, mMaxZ); }
	};

	//--------------------------------------------------------------------------------
	// bound3d
	//--------------------------------------------------------------------------------

	struct bound3d
	{
		double mMinX;
		double mMaxX;
		double mMinY;
		double mMaxY;
		double mMinZ;
		double mMaxZ;

		bound3d() {}

		explicit bound3d(double mix, double max, double miy, double may, double miz, double maz) { mMinX = mix; mMaxX = max; mMinY = miy; mMaxY = may; mMinZ = miz; mMaxZ = maz; }
		explicit bound3d(double infi) { mMinX = infi; mMaxX = -infi; mMinY = infi; mMaxY = -infi; mMinZ = infi; mMaxZ = -infi; }
		explicit bound3d(double const * const v) { mMinX = v[0]; mMaxX = v[1]; mMinY = v[2]; mMaxY = v[3]; mMinZ = v[4]; mMaxZ = v[5]; }
		explicit bound3d(double const * const vmin, double const * const vmax) { mMinX = vmin[0]; mMaxX = vmax[0]; mMinY = vmin[1]; mMaxY = vmax[1]; mMinZ = vmin[2]; mMaxZ = vmax[2]; }
		explicit bound3d(const vec3d & mi, const vec3d & ma) { mMinX = mi.x; mMaxX = ma.x; mMinY = mi.y; mMaxY = ma.y; mMinZ = mi.z; mMaxZ = ma.z; }
		explicit bound3d(const vec3d & mima) { mMinX = mima.x; mMaxX = mima.x; mMinY = mima.y; mMaxY = mima.y; mMinZ = mima.z; mMaxZ = mima.z; }

		double & operator [](int i) { return ((double*)this)[i]; }
		const double & operator [](int i) const { return ((double*)this)[i]; }

		bound2d xy() const { return bound2d(mMinX, mMaxX, mMinY, mMaxY); }
		bound2d xz() const { return bound2d(mMinX, mMaxX, mMinZ, mMaxZ); }
		bound2d yz() const { return bound2d(mMinY, mMaxY, mMinZ, mMaxZ); }
	};

	//--------------------------------------------------------------------------------
	// quat
	//--------------------------------------------------------------------------------
	struct quat
	{
		float x, y, z, w;

		quat() {}

		explicit quat(float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }
		explicit quat(float const * const v) { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }

		static inline quat identity() { return quat(0.0f, 0.0f, 0.0f, 1.0f); }
	};


	//--------------------------------------------------------------------------------
	// quatd
	//--------------------------------------------------------------------------------
	struct quatd
	{
		double x, y, z, w;

		quatd() {}

		explicit quatd(double a, double b, double c, double d) { x = a; y = b; z = c; w = d; }
		explicit quatd(double const * const v) { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }

		static inline quatd identity() { return quatd(0.0, 0.0, 0.0, 1.0); }
	};

	//--------------------------------------------------------------------------------
	// trans3d
	//--------------------------------------------------------------------------------
	struct trans3d
	{

		quatd  mRotation;
		double mScale;
		vec3d  mTranslation;

		// final transform is T*v = T.mRotation*T.mScale*v + T.mTranslation;

		trans3d() {}

		explicit trans3d(const quatd & r, double s, const vec3d & t)
		{
			mRotation = r;
			mScale = s;
			mTranslation = t;
		}

		static trans3d identity(void)
		{
			return trans3d(quatd::identity(), 1.0, vec3d(0.0, 0.0, 0.0));
		}
	};



	//=========================================================================================================================================
	// implementations
	//=========================================================================================================================================


    inline ivec2 operator+(ivec2  const & v, int    const & s) { return ivec2(v.x + s, v.y + s); }
    inline ivec2 operator+(int    const & s, ivec2  const & v) { return ivec2(s + v.x, s + v.y); }
    inline ivec2 operator+(ivec2  const & a, ivec2  const & b) { return ivec2(a.x + b.x, a.y + b.y); }
    inline ivec2 operator-(ivec2  const & v, int    const & s) { return ivec2(v.x - s, v.y - s); }
    inline ivec2 operator-(int    const & s, ivec2  const & v) { return ivec2(s - v.x, s - v.y); }
    inline ivec2 operator-(ivec2  const & a, ivec2  const & b) { return ivec2(a.x - b.x, a.y - b.y); }
    inline ivec2 operator*(ivec2  const & v, int    const & s) { return ivec2(v.x * s, v.y * s); }
    inline ivec2 operator*(int    const & s, ivec2  const & v) { return ivec2(s * v.x, s * v.y); }
    inline ivec2 operator*(ivec2  const & a, ivec2  const & b) { return ivec2(a.x * b.x, a.y * b.y); }
    inline ivec2 operator/(ivec2  const & v, int    const & s) { return ivec2(v.x / s, v.y / s); }
    inline ivec2 operator/(int    const & s, ivec2  const & v) { return ivec2(s / v.x, s / v.y); }
    inline ivec2 operator/(ivec2  const & a, ivec2  const & b) { return ivec2(a.x / b.x, a.y / b.y); }
	inline ivec3 operator+(ivec3  const & v, int    const & s) { return ivec3(v.x + s, v.y + s, v.z + s); }
	inline ivec3 operator+(int    const & s, ivec3  const & v) { return ivec3(s + v.x, s + v.y, s + v.z); }
	inline ivec3 operator+(ivec3  const & a, ivec3  const & b) { return ivec3(a.x + b.x, a.y + b.y, a.z + b.z); }
	inline ivec3 operator-(ivec3  const & v, int    const & s) { return ivec3(v.x - s, v.y - s, v.z - s); }
	inline ivec3 operator-(int    const & s, ivec3  const & v) { return ivec3(s - v.x, s - v.y, s - v.z); }
	inline ivec3 operator-(ivec3  const & a, ivec3  const & b) { return ivec3(a.x - b.x, a.y - b.y, a.z - b.z); }
	inline ivec3 operator*(ivec3  const & v, int    const & s) { return ivec3(v.x * s, v.y * s, v.z * s); }
	inline ivec3 operator*(int    const & s, ivec3  const & v) { return ivec3(s * v.x, s * v.y, s * v.z); }
	inline ivec3 operator*(ivec3  const & a, ivec3  const & b) { return ivec3(a.x * b.x, a.y * b.y, a.z * b.z); }
	inline ivec3 operator/(ivec3  const & v, int    const & s) { return ivec3(v.x / s, v.y / s, v.z / s); }
	inline ivec3 operator/(int    const & s, ivec3  const & v) { return ivec3(s / v.x, s / v.y, s / v.z); }
	inline ivec3 operator/(ivec3  const & a, ivec3  const & b) { return ivec3(a.x / b.x, a.y / b.y, a.z / b.z); }
	inline vec2  operator+(vec2   const & v, float  const & s) { return vec2(v.x + s, v.y + s); }
	inline vec2  operator+(float  const & s, vec2   const & v) { return vec2(s + v.x, s + v.y); }
	inline vec2  operator+(vec2   const & a, vec2   const & b) { return vec2(a.x + b.x, a.y + b.y); }
	inline vec2  operator-(vec2   const & v, float  const & s) { return vec2(v.x - s, v.y - s); }
	inline vec2  operator-(float  const & s, vec2   const & v) { return vec2(s - v.x, s - v.y); }
	inline vec2  operator-(vec2   const & a, vec2   const & b) { return vec2(a.x - b.x, a.y - b.y); }
	inline vec2  operator*(vec2   const & v, float  const & s) { return vec2(v.x * s, v.y * s); }
	inline vec2  operator*(float  const & s, vec2   const & v) { return vec2(s * v.x, s * v.y); }
	inline vec2  operator*(vec2   const & a, vec2   const & b) { return vec2(a.x * b.x, a.y * b.y); }
	inline vec2  operator/(vec2   const & v, float  const & s) { return vec2(v.x / s, v.y / s); }
	inline vec2  operator/(float  const & s, vec2   const & v) { return vec2(s / v.x, s / v.y); }
	inline vec2  operator/(vec2   const & a, vec2   const & b) { return vec2(a.x / b.x, a.y / b.y); }
	inline vec3  operator+(vec3   const & v, float  const & s) { return vec3(v.x + s, v.y + s, v.z + s); }
	inline vec3  operator+(float  const & s, vec3   const & v) { return vec3(s + v.x, s + v.y, s + v.z); }
	inline vec3  operator+(vec3   const & a, vec3   const & b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
	inline vec3  operator-(vec3   const & v, float  const & s) { return vec3(v.x - s, v.y - s, v.z - s); }
	inline vec3  operator-(float  const & s, vec3   const & v) { return vec3(s - v.x, s - v.y, s - v.z); }
	inline vec3  operator-(vec3   const & a, vec3   const & b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
	inline vec3  operator*(vec3   const & v, float  const & s) { return vec3(v.x * s, v.y * s, v.z * s); }
	inline vec3  operator*(float  const & s, vec3   const & v) { return vec3(s * v.x, s * v.y, s * v.z); }
	inline vec3  operator*(vec3   const & a, vec3   const & b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
	inline vec3  operator/(vec3   const & v, float  const & s) { return vec3(v.x / s, v.y / s, v.z / s); }
	inline vec3  operator/(float  const & s, vec3   const & v) { return vec3(s / v.x, s / v.y, s / v.z); }
	inline vec3  operator/(vec3   const & a, vec3   const & b) { return vec3(a.x / b.x, a.y / b.y, a.z / b.z); }
	inline vec4  operator+(vec4   const & v, float  const & s) { return vec4(v.x + s, v.y + s, v.z + s, v.w + s); }
	inline vec4  operator+(float  const & s, vec4   const & v) { return vec4(s + v.x, s + v.y, s + v.z, s + v.w); }
	inline vec4  operator+(vec4   const & a, vec4   const & b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	inline vec4  operator-(vec4   const & v, float  const & s) { return vec4(v.x - s, v.y - s, v.z - s, v.w - s); }
	inline vec4  operator-(float  const & s, vec4   const & v) { return vec4(s - v.x, s - v.y, s - v.z, s - v.w); }
	inline vec4  operator-(vec4   const & a, vec4   const & b) { return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	inline vec4  operator*(vec4   const & v, float  const & s) { return vec4(v.x * s, v.y * s, v.z * s, v.w * s); }
	inline vec4  operator*(float  const & s, vec4   const & v) { return vec4(s * v.x, s * v.y, s * v.z, s * v.w); }
	inline vec4  operator*(vec4   const & a, vec4   const & b) { return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	inline vec4  operator/(vec4   const & v, float  const & s) { return vec4(v.x / s, v.y / s, v.z / s, v.w / s); }
	inline vec4  operator/(float  const & s, vec4   const & v) { return vec4(s / v.x, s / v.y, s / v.z, s / v.w); }
	inline vec4  operator/(vec4   const & a, vec4   const & b) { return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	inline vec2d operator+(vec2d  const & v, double const & s) { return vec2d(v.x + s, v.y + s); }
	inline vec2d operator+(double const & s, vec2d  const & v) { return vec2d(s + v.x, s + v.y); }
	inline vec2d operator+(vec2d  const & a, vec2d  const & b) { return vec2d(a.x + b.x, a.y + b.y); }
	inline vec2d operator-(vec2d  const & v, double const & s) { return vec2d(v.x - s, v.y - s); }
	inline vec2d operator-(double const & s, vec2d  const & v) { return vec2d(s - v.x, s - v.y); }
	inline vec2d operator-(vec2d  const & a, vec2d  const & b) { return vec2d(a.x - b.x, a.y - b.y); }
	inline vec2d operator*(vec2d  const & v, double const & s) { return vec2d(v.x * s, v.y * s); }
	inline vec2d operator*(double const & s, vec2d  const & v) { return vec2d(s * v.x, s * v.y); }
	inline vec2d operator*(vec2d  const & a, vec2d  const & b) { return vec2d(a.x * b.x, a.y * b.y); }
	inline vec2d operator/(vec2d  const & v, double const & s) { return vec2d(v.x / s, v.y / s); }
	inline vec2d operator/(double const & s, vec2d  const & v) { return vec2d(s / v.x, s / v.y); }
	inline vec2d operator/(vec2d  const & a, vec2d  const & b) { return vec2d(a.x / b.x, a.y / b.y); }
	inline vec3d operator+(vec3d  const & v, double const & s) { return vec3d(v.x + s, v.y + s, v.z + s); }
	inline vec3d operator+(double const & s, vec3d  const & v) { return vec3d(s + v.x, s + v.y, s + v.z); }
	inline vec3d operator+(vec3d  const & a, vec3d  const & b) { return vec3d(a.x + b.x, a.y + b.y, a.z + b.z); }
	inline vec3d operator-(vec3d  const & v, double const & s) { return vec3d(v.x - s, v.y - s, v.z - s); }
	inline vec3d operator-(double const & s, vec3d  const & v) { return vec3d(s - v.x, s - v.y, s - v.z); }
	inline vec3d operator-(vec3d  const & a, vec3d  const & b) { return vec3d(a.x - b.x, a.y - b.y, a.z - b.z); }
	inline vec3d operator*(vec3d  const & v, double const & s) { return vec3d(v.x * s, v.y * s, v.z * s); }
	inline vec3d operator*(double const & s, vec3d  const & v) { return vec3d(s * v.x, s * v.y, s * v.z); }
	inline vec3d operator*(vec3d  const & a, vec3d  const & b) { return vec3d(a.x * b.x, a.y * b.y, a.z * b.z); }
	inline vec3d operator/(vec3d  const & v, double const & s) { return vec3d(v.x / s, v.y / s, v.z / s); }
	inline vec3d operator/(double const & s, vec3d  const & v) { return vec3d(s / v.x, s / v.y, s / v.z); }
	inline vec3d operator/(vec3d  const & a, vec3d  const & b) { return vec3d(a.x / b.x, a.y / b.y, a.z / b.z); }
	inline vec4d operator+(vec4d  const & v, double const & s) { return vec4d(v.x + s, v.y + s, v.z + s, v.w + s); }
	inline vec4d operator+(double const & s, vec4d  const & v) { return vec4d(s + v.x, s + v.y, s + v.z, s + v.w); }
	inline vec4d operator+(vec4d  const & a, vec4d  const & b) { return vec4d(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	inline vec4d operator-(vec4d  const & v, double const & s) { return vec4d(v.x - s, v.y - s, v.z - s, v.w - s); }
	inline vec4d operator-(double const & s, vec4d  const & v) { return vec4d(s - v.x, s - v.y, s - v.z, s - v.w); }
	inline vec4d operator-(vec4d  const & a, vec4d  const & b) { return vec4d(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	inline vec4d operator*(vec4d  const & v, double const & s) { return vec4d(v.x * s, v.y * s, v.z * s, v.w * s); }
	inline vec4d operator*(double const & s, vec4d  const & v) { return vec4d(s * v.x, s * v.y, s * v.z, s * v.w); }
	inline vec4d operator*(vec4d  const & a, vec4d  const & b) { return vec4d(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	inline vec4d operator/(vec4d  const & v, double const & s) { return vec4d(v.x / s, v.y / s, v.z / s, v.w / s); }
	inline vec4d operator/(double const & s, vec4d  const & v) { return vec4d(s / v.x, s / v.y, s / v.z, s / v.w); }
	inline vec4d operator/(vec4d  const & a, vec4d  const & b) { return vec4d(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }

	// vector transformation
	inline vec2  operator*(mat2x2  const & m, vec2  const & v) { return vec2(v.x*m[0] + v.y*m[1], v.x*m[2] + v.y*m[3]); }
	inline vec3  operator*(mat3x3  const & m, vec3  const & v) { return vec3(v.x*m[0] + v.y*m[1] + v.z*m[2], v.x*m[3] + v.y*m[4] + v.z*m[5], v.x*m[6] + v.y*m[7] + v.z*m[8]); }
	inline vec4  operator*(mat4x4  const & m, vec4  const & v) { return vec4(v.x*m[0] + v.y*m[1] + v.z*m[2] + v.w*m[3], v.x*m[4] + v.y*m[5] + v.z*m[6] + v.w*m[7], v.x*m[8] + v.y*m[9] + v.z*m[10] + v.w*m[11], v.x*m[12] + v.y*m[13] + v.z*m[14] + v.w*m[15]); }
	inline vec2d operator*(mat2x2d const & m, vec2d const & v) { return vec2d(v.x*m[0] + v.y*m[1], v.x*m[2] + v.y*m[3]); }
	inline vec3d operator*(mat3x3d const & m, vec3d const & v) { return vec3d(v.x*m[0] + v.y*m[1] + v.z*m[2], v.x*m[3] + v.y*m[4] + v.z*m[5], v.x*m[6] + v.y*m[7] + v.z*m[8]); }
	inline vec4d operator*(mat4x4d const & m, vec4d const & v) { return vec4d(v.x*m[0] + v.y*m[1] + v.z*m[2] + v.w*m[3], v.x*m[4] + v.y*m[5] + v.z*m[6] + v.w*m[7], v.x*m[8] + v.y*m[9] + v.z*m[10] + v.w*m[11], v.x*m[12] + v.y*m[13] + v.z*m[14] + v.w*m[15]); }
	inline vec3d operator*(quatd   const & q, vec3d const & v) { return v + 2.0*(mat3x3d(-q.y*q.y - q.z*q.z,  q.x*q.y - q.z*q.w,  q.x*q.z + q.y*q.w, q.x*q.y + q.z*q.w, -q.x*q.x - q.z*q.z,  q.y*q.z - q.x*q.w, q.x*q.z - q.y*q.w,  q.y*q.z + q.x*q.w, -q.x*q.x - q.y*q.y)*v); }
	inline vec4d operator*(trans3d const & t, vec4d const & v) { return vec4d(t.mRotation*(t.mScale*v.xyz()) + v.w*t.mTranslation, v.w); }


	// concatenation
	inline mat3x3 operator*(mat3x3 const & a, mat3x3 const & b)
	{
		return mat3x3(a[0] * b[0] + a[1] * b[3] + a[2] * b[6], a[0] * b[1] + a[1] * b[4] + a[2] * b[7], a[0] * b[2] + a[1] * b[5] + a[2] * b[8],
			          a[3] * b[0] + a[4] * b[3] + a[5] * b[6], a[3] * b[1] + a[4] * b[4] + a[5] * b[7], a[3] * b[2] + a[4] * b[5] + a[5] * b[8],
			          a[6] * b[0] + a[7] * b[3] + a[8] * b[6], a[6] * b[1] + a[7] * b[4] + a[8] * b[7], a[6] * b[2] + a[7] * b[5] + a[8] * b[8]);
	}
	inline mat4x4 operator*(mat4x4 const & a, mat4x4 const & b)
	{
		mat4x4 res;
		for (int i = 0; i<4; i++)
		{
			const float x = a.m[4 * i + 0];
			const float y = a.m[4 * i + 1];
			const float z = a.m[4 * i + 2];
			const float w = a.m[4 * i + 3];
			res.m[4 * i + 0] = x * b[0] + y * b[4] + z * b[8] + w * b[12];
			res.m[4 * i + 1] = x * b[1] + y * b[5] + z * b[9] + w * b[13];
			res.m[4 * i + 2] = x * b[2] + y * b[6] + z * b[10] + w * b[14];
			res.m[4 * i + 3] = x * b[3] + y * b[7] + z * b[11] + w * b[15];
		}

		return res;
	}
	inline mat4x4d operator*(mat4x4d const & a, mat4x4d const & b)
	{
		mat4x4d res;
		for (int i = 0; i < 4; i++)
		{
			const double x = a.m[4 * i + 0];
			const double y = a.m[4 * i + 1];
			const double z = a.m[4 * i + 2];
			const double w = a.m[4 * i + 3];
			res.m[4 * i + 0] = x * b[0] + y * b[4] + z * b[8] + w * b[12];
			res.m[4 * i + 1] = x * b[1] + y * b[5] + z * b[9] + w * b[13];
			res.m[4 * i + 2] = x * b[2] + y * b[6] + z * b[10] + w * b[14];
			res.m[4 * i + 3] = x * b[3] + y * b[7] + z * b[11] + w * b[15];
		}
		return res;
	}
	inline quatd operator*(quatd const & a, quatd const & b)
	{
		return quatd(a.x * b.w + a.w * b.x + a.y * b.z - a.z * b.y, a.y * b.w + a.w * b.y + a.z * b.x - a.x * b.z,
			a.z * b.w + a.w * b.z + a.x * b.y - a.y * b.x,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
	}
	inline trans3d operator*(trans3d const & a, trans3d const & b)
	{
		return trans3d(a.mRotation * b.mRotation, a.mScale * b.mScale, a.mTranslation + a.mRotation*(a.mScale*b.mTranslation));
	}


	// transforms
	inline vec3  vtransform(const mat4x4  & m, const vec3  & v) { return vec3( v.x*m[0] + v.y*m[1] + v.z*m[2] + m[3], v.x*m[4] + v.y*m[5] + v.z*m[6] + m[7], v.x*m[8] + v.y*m[9] + v.z*m[10] + m[11]); }
	inline vec3d vtransform(const mat4x4d & m, const vec3d & v) { return vec3d(v.x*m[0] + v.y*m[1] + v.z*m[2] + m[3], v.x*m[4] + v.y*m[5] + v.z*m[6] + m[7], v.x*m[8] + v.y*m[9] + v.z*m[10] + m[11]); }
	inline vec4  vtransform(const mat4x4  & m, const vec4  & v) { return vec4( v.x*m[0] + v.y*m[1] + v.z*m[2] + v.w*m[3], v.x*m[4] + v.y*m[5] + v.z*m[6] + v.w*m[7], v.x*m[8] + v.y*m[9] + v.z*m[10] + v.w*m[11], v.x*m[12] + v.y*m[13] + v.z*m[14] + v.w*m[15]); }
	inline vec4d vtransform(const mat4x4d & m, const vec4d & v) { return vec4d(v.x*m[0] + v.y*m[1] + v.z*m[2] + v.w*m[3], v.x*m[4] + v.y*m[5] + v.z*m[6] + v.w*m[7], v.x*m[8] + v.y*m[9] + v.z*m[10] + v.w*m[11], v.x*m[12] + v.y*m[13] + v.z*m[14] + v.w*m[15]); }
	inline vec4d vtransform(const trans3d & t, const vec4d & v) { return vec4d(t.mRotation*(t.mScale*v.xyz()) + v.w*t.mTranslation, v.w); }
	inline vec3d vtransform(const trans3d & t, const vec3d & v) { return t.mRotation*(t.mScale*v.xyz()) + t.mTranslation; }

	inline vec3  ntransform(const mat4x4  & m, const vec3  & v) { return vec3(v.x*m[0] + v.y*m[1] + v.z*m[2], v.x*m[4] + v.y*m[5] + v.z*m[6], v.x*m[8] + v.y*m[9] + v.z*m[10]); }
	inline vec3d ntransform(const mat4x4d & m, const vec3d & v) { return vec3d(v.x*m[0] + v.y*m[1] + v.z*m[2], v.x*m[4] + v.y*m[5] + v.z*m[6], v.x*m[8] + v.y*m[9] + v.z*m[10]); }
	inline vec3d ntransform(trans3d const & t, vec3d const & v) { return t.mRotation*(t.mScale*v.xyz()); }

	inline bound2  include(const bound2  & a, const vec2    & p) { return bound2(  (p.x<a.mMinX) ? p.x : a.mMinX, (p.x>a.mMaxX) ? p.x : a.mMaxX, (p.y<a.mMinY) ? p.y : a.mMinY, (p.y>a.mMaxY) ? p.y : a.mMaxY); }
	inline bound3  include(const bound3  & a, const vec3    & p) { return bound3(  (p.x<a.mMinX) ? p.x : a.mMinX, (p.x>a.mMaxX) ? p.x : a.mMaxX, (p.y<a.mMinY) ? p.y : a.mMinY, (p.y>a.mMaxY) ? p.y : a.mMaxY, (p.z<a.mMinZ) ? p.z : a.mMinZ, (p.z>a.mMaxZ) ? p.z : a.mMaxZ); }
	inline bound3  include(const bound3  & a, const bound3  & b) { return bound3(  fminf(a.mMinX, b.mMinX), fmaxf(a.mMaxX, b.mMaxX), fminf(a.mMinY, b.mMinY), fmaxf(a.mMaxY, b.mMaxY), fminf(a.mMinZ, b.mMinZ), fmaxf(a.mMaxZ, b.mMaxZ)); }
	inline bound2d include(const bound2d & a, const vec2d   & p) { return bound2d( (p.x<a.mMinX) ? p.x : a.mMinX, (p.x>a.mMaxX) ? p.x : a.mMaxX, (p.y<a.mMinY) ? p.y : a.mMinY, (p.y>a.mMaxY) ? p.y : a.mMaxY); }
	inline bound3d include(const bound3d & a, const vec3d   & p) { return bound3d( (p.x<a.mMinX) ? p.x : a.mMinX, (p.x>a.mMaxX) ? p.x : a.mMaxX, (p.y<a.mMinY) ? p.y : a.mMinY, (p.y>a.mMaxY) ? p.y : a.mMaxY,  (p.z<a.mMinZ) ? p.z : a.mMinZ, (p.z>a.mMaxZ) ? p.z : a.mMaxZ); }
	inline bound3d include(const bound3d & a, const bound3d & b) { return bound3d( fmin(a.mMinX, b.mMinX), fmax(a.mMaxX, b.mMaxX), fmin(a.mMinY, b.mMinY), fmax(a.mMaxY, b.mMaxY), fmin(a.mMinZ, b.mMinZ), fmax(a.mMaxZ, b.mMaxZ)); }

	inline bound3  expand(const bound3  & a, const bound3  & b) { return bound3( a.mMinX + b.mMinX, a.mMaxX + b.mMaxX, a.mMinY + b.mMinY, a.mMaxY + b.mMaxY, a.mMinZ + b.mMinZ, a.mMaxZ + b.mMaxZ); }
	inline bound3  expand(const bound3  & a, const float     b) { return bound3( a.mMinX - b, a.mMaxX + b, a.mMinY - b, a.mMaxY + b, a.mMinZ - b, a.mMaxZ + b); }
	inline bound3d expand(const bound3d & a, const bound3d & b) { return bound3d(a.mMinX + b.mMinX, a.mMaxX + b.mMaxX, a.mMinY + b.mMinY, a.mMaxY + b.mMaxY, a.mMinZ + b.mMinZ, a.mMaxZ + b.mMaxZ); }
	inline bound3d expand(const bound3d & a, const double    b) { return bound3d(a.mMinX - b, a.mMaxX + b, a.mMinY - b, a.mMaxY + b, a.mMinZ - b, a.mMaxZ + b); }

	inline bool contains(bound2  const & b, vec2  const & p) { return (p.x >= b.mMinX && p.x <= b.mMaxX && p.y >= b.mMinY && p.y <= b.mMaxY); }
	inline bool contains(bound3  const & b, vec3  const & p) { return (p.x >= b.mMinX && p.x <= b.mMaxX && p.y >= b.mMinY && p.y <= b.mMaxY && p.z >= b.mMinZ && p.z <= b.mMaxZ); }
	inline bool contains(bound2d const & b, vec2d const & p) { return (p.x >= b.mMinX && p.x <= b.mMaxX && p.y >= b.mMinY && p.y <= b.mMaxY); }
	inline bool contains(bound3d const & b, vec3d const & p) { return (p.x >= b.mMinX && p.x <= b.mMaxX && p.y >= b.mMinY && p.y <= b.mMaxY && p.z >= b.mMinZ && p.z <= b.mMaxZ); }

	inline bool overlap(bound2  const & a, bound2  const & b) { return (a.mMaxX >= b.mMinX && a.mMinX <= b.mMaxX && a.mMaxY >= b.mMinY && a.mMinY <= b.mMaxY); }
	inline bool overlap(bound3  const & a, bound3  const & b) { return (a.mMaxX >= b.mMinX && a.mMinX <= b.mMaxX && a.mMaxY >= b.mMinY && a.mMinY <= b.mMaxY && a.mMaxZ >= b.mMinZ && a.mMinZ <= b.mMaxZ); }
	inline bool overlap(bound2d const & a, bound2d const & b) { return (a.mMaxX >= b.mMinX && a.mMinX <= b.mMaxX && a.mMaxY >= b.mMinY && a.mMinY <= b.mMaxY); }
	inline bool overlap(bound3d const & a, bound3d const & b) { return (a.mMaxX >= b.mMinX && a.mMinX <= b.mMaxX && a.mMaxY >= b.mMinY && a.mMinY <= b.mMaxY && a.mMaxZ >= b.mMinZ && a.mMinZ <= b.mMaxZ); }

	inline bound3 btransform(bound3 const & bbox, const mat4x4 & m)
	{
		bound3 res = bound3(vtransform(m, vec3(bbox.mMinX, bbox.mMinY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3(bbox.mMaxX, bbox.mMinY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3(bbox.mMinX, bbox.mMaxY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3(bbox.mMaxX, bbox.mMaxY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3(bbox.mMinX, bbox.mMinY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3(bbox.mMaxX, bbox.mMinY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3(bbox.mMinX, bbox.mMaxY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3(bbox.mMaxX, bbox.mMaxY, bbox.mMaxZ)));
		return res;
	}
	inline bound3d btransform(bound3d const & bbox, const mat4x4d & m)
	{
		bound3d res = bound3d(vtransform(m, vec3d(bbox.mMinX, bbox.mMinY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMaxX, bbox.mMinY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMinX, bbox.mMaxY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMaxX, bbox.mMaxY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMinX, bbox.mMinY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMaxX, bbox.mMinY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMinX, bbox.mMaxY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMaxX, bbox.mMaxY, bbox.mMaxZ)));
		return res;
	}
	inline bound3d btransform(bound3d const & bbox, const trans3d & m)
	{
		bound3d res = bound3d(vtransform(m, vec3d(bbox.mMinX, bbox.mMinY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMaxX, bbox.mMinY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMinX, bbox.mMaxY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMaxX, bbox.mMaxY, bbox.mMinZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMinX, bbox.mMinY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMaxX, bbox.mMinY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMinX, bbox.mMaxY, bbox.mMaxZ)));
		res = include(res, vtransform(m, vec3d(bbox.mMaxX, bbox.mMaxY, bbox.mMaxZ)));
		return res;
	}


	inline void store(uint8_t  *d, const ivec2 & s) { d[0] = s.x; d[1] = s.y; }
	inline void store(uint16_t *d, const ivec2 & s) { d[0] = s.x; d[1] = s.y; }
	inline void store(uint32_t *d, const ivec2 & s) { d[0] = s.x; d[1] = s.y; }
	inline void store(uint8_t  *d, const ivec3 & s) { d[0] = s.x; d[1] = s.y; d[2] = s.z; }
	inline void store(uint16_t *d, const ivec3 & s) { d[0] = s.x; d[1] = s.y; d[2] = s.z; }
	inline void store(uint32_t *d, const ivec3 & s) { d[0] = s.x; d[1] = s.y; d[2] = s.z; }

    inline ivec2 vmin(const ivec2 & v, const ivec2 & m)  { return ivec2((v.x<m.x) ? v.x : m.x, (v.y<m.y) ? v.y : m.y); }
	inline ivec3 vmin(const ivec3 & v, const ivec3 & m)  { return ivec3((v.x<m.x) ? v.x : m.x, (v.y<m.y) ? v.y : m.y, (v.z<m.z) ? v.z : m.z); }
	inline ivec2 vmin(const ivec2 & v, int   m)          { return ivec2((v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m  ); }
	inline ivec3 vmin(const ivec3 & v, int   m)          { return ivec3((v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m,   (v.z<m  ) ? v.z : m); }
	inline ivec4 vmin(const ivec4 & v, int   m)          { return ivec4((v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m,   (v.z<m  ) ? v.z : m,   (v.w<m  ) ? v.w : m  ); }
	inline vec2  vmin(const vec2  & v, float m)          { return vec2( (v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m  ); }
	inline vec3  vmin(const vec3  & v, float m)          { return vec3( (v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m,   (v.z<m  ) ? v.z : m); }
	inline vec4  vmin(const vec4  & v, float m)          { return vec4( (v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m,   (v.z<m  ) ? v.z : m,   (v.w<m  ) ? v.w : m  ); }
	inline vec2  vmin(const vec2  & v, const vec2 & m)   { return vec2( (v.x<m.x) ? v.x : m.x, (v.y<m.y) ? v.y : m.y); }
	inline vec3  vmin(const vec3  & v, const vec3 & m)   { return vec3( (v.x<m.x) ? v.x : m.x, (v.y<m.y) ? v.y : m.y, (v.z<m.z) ? v.z : m.z); }
	inline vec4  vmin(const vec4  & v, const vec4 & m)   { return vec4( (v.x<m.x) ? v.x : m.x, (v.y<m.y) ? v.y : m.y, (v.z<m.z) ? v.z : m.z, (v.w<m.w) ? v.w : m.w); }
	inline vec2d vmin(const vec2d & v, double m)         { return vec2d((v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m  ); }
	inline vec3d vmin(const vec3d & v, double m)         { return vec3d((v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m,   (v.z<m  ) ? v.z : m); }
	inline vec4d vmin(const vec4d & v, double m)         { return vec4d((v.x<m  ) ? v.x : m,   (v.y<m  ) ? v.y : m,   (v.z<m  ) ? v.z : m,   (v.w<m  ) ? v.w : m  ); }

	inline ivec2 vmax(const ivec2 & v, int   m)          { return ivec2((v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m); }
	inline ivec3 vmax(const ivec3 & v, int   m)          { return ivec3((v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m,   (v.z>m  ) ? v.z : m); }
	inline ivec4 vmax(const ivec4 & v, int   m)          { return ivec4((v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m,   (v.z>m  ) ? v.z : m, (v.w>m) ? v.w : m); }
	inline ivec2 vmax(const ivec2 & v, const ivec2 & b)  { return ivec2((v.x>b.x) ? v.x : b.x, (v.y>b.y) ? v.y : b.y); }
	inline ivec3 vmax(const ivec3 & v, const ivec3 & b)  { return ivec3((v.x>b.x) ? v.x : b.x, (v.y>b.y) ? v.y : b.y, (v.z>b.z) ? v.z : b.z); }
	inline vec2  vmax(const vec2  & v, float m)          { return vec2( (v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m); }
	inline vec3  vmax(const vec3  & v, float m)          { return vec3( (v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m,   (v.z>m  ) ? v.z : m); }
	inline vec4  vmax(const vec4  & v, float m)          { return vec4( (v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m,   (v.z>m  ) ? v.z : m,   (v.w>m  ) ? v.w : m  ); }
	inline vec2  vmax(const vec2  & v, const vec2 & b)   { return vec2( (v.x>b.x) ? v.x : b.x, (v.y>b.y) ? v.y : b.y ); }
	inline vec3  vmax(const vec3  & v, const vec3 & b)   { return vec3( (v.x>b.x) ? v.x : b.x, (v.y>b.y) ? v.y : b.y, (v.z>b.z) ? v.z : b.z); }
	inline vec4  vmax(const vec4  & v, const vec4 & b)   { return vec4( (v.x>b.x) ? v.x : b.x, (v.y>b.y) ? v.y : b.y, (v.z>b.z) ? v.z : b.z, (v.w>b.w) ? v.w : b.w); }
	inline vec2d vmax(const vec2d & v, double m)         { return vec2d((v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m); }
	inline vec3d vmax(const vec3d & v, double m)         { return vec3d((v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m,   (v.z>m  ) ? v.z : m); }
	inline vec4d vmax(const vec4d & v, double m)         { return vec4d((v.x>m  ) ? v.x : m,   (v.y>m  ) ? v.y : m,   (v.z>m  ) ? v.z : m,   (v.w>m  ) ? v.w : m  ); }

	inline float  mincomp(const vec2  & v) { return (v.x<v.y) ? v.x : v.y; }
	inline double mincomp(const vec2d & v) { return (v.x<v.y) ? v.x : v.y; }
	inline float  mincomp(const vec3  & v) { return (v.x<v.y && v.x<v.z) ? v.x : ((v.y<v.z) ? v.y : v.z); }
	inline double mincomp(const vec3d & v) { return (v.x<v.y && v.x<v.z) ? v.x : ((v.y<v.z) ? v.y : v.z); }

	inline float  maxcomp(const vec2  & v) { return (v.x>v.y) ? v.x : v.y; }
	inline double maxcomp(const vec2d & v) { return (v.x>v.y) ? v.x : v.y; }
	inline float  maxcomp(const vec3  & v) { return (v.x>v.y && v.x>v.z) ? v.x : ((v.y>v.z) ? v.y : v.z); }
	inline double maxcomp(const vec3d & v) { return (v.x>v.y && v.x>v.z) ? v.x : ((v.y>v.z) ? v.y : v.z); }

	inline int   clamp(const int     v, int    mi, int    ma) { return (v<mi) ? mi : ((v>ma) ? ma : v); }
	inline ivec2 clamp(const ivec2 & v, int    mi, int    ma) { return ivec2((v.x<mi) ? mi : ((v.x>ma) ? ma : v.x), (v.y<mi) ? mi : ((v.y>ma) ? ma : v.y)); }
	inline ivec3 clamp(const ivec3 & v, int    mi, int    ma) { return ivec3((v.x<mi) ? mi : ((v.x>ma) ? ma : v.x), (v.y<mi) ? mi : ((v.y>ma) ? ma : v.y), (v.z<mi) ? mi : ((v.z>ma) ? ma : v.z)); }
	inline vec2  clamp(const vec2  & v, float  mi, float  ma) { return vmax(vmin(v, ma), mi); }
	inline vec3  clamp(const vec3  & v, float  mi, float  ma) { return vmax(vmin(v, ma), mi); }
	inline vec2d clamp(const vec2d & v, double mi, double ma) { return vmax(vmin(v, ma), mi); }
	inline vec3d clamp(const vec3d & v, double mi, double ma) { return vmax(vmin(v, ma), mi); }

	inline vec2  clamp01(const vec2  & v) { return vmax(vmin(v, 1.0f), 0.0f); }
	inline vec3  clamp01(const vec3  & v) { return vmax(vmin(v, 1.0f),  0.0f); }
	inline vec4  clamp01(const vec4  & v) { return vmax(vmin(v, 1.0f), 0.0f); }
	inline vec2d clamp01(const vec2d & v) { return vmax(vmin(v, 1.0), 0.0); }
	inline vec3d clamp01(const vec3d & v) { return vmax(vmin(v, 1.0 ),  0.0); }
	inline vec4d clamp01(const vec4d & v) { return vmax(vmin(v, 1.0), 0.0); }
	inline vec2  clamp1( const vec2  & v) { return vmax(vmin(v, 1.0f), -1.0f); }
	inline vec3  clamp1( const vec3  & v) { return vmax(vmin(v, 1.0f), -1.0f); }
	inline vec4  clamp1( const vec4  & v) { return vmax(vmin(v, 1.0f), -1.0f); }
	inline vec2d clamp1( const vec2d & v) { return vmax(vmin(v, 1.0 ), -1.0); }
	inline vec3d clamp1( const vec3d & v) { return vmax(vmin(v, 1.0), -1.0); }
	inline vec4d clamp1( const vec4d & v) { return vmax(vmin(v, 1.0), -1.0); }

	inline float  dot(vec2  const & a, vec2  const & b) { return a.x*b.x + a.y*b.y; }
	inline float  dot(vec3  const & a, vec3  const & b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
	inline float  dot(vec4  const & a, vec4  const & b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }
	inline double dot(vec2d const & a, vec2d const & b) { return a.x*b.x + a.y*b.y; }
	inline double dot(vec3d const & a, vec3d const & b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
	inline double dot(vec4d const & a, vec4d const & b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }

    inline vec2  floor(vec2  const & v) { return vec2( std::floorf(v.x), std::floorf(v.y)); }
	inline vec3  floor(vec3  const & v) { return vec3( std::floorf(v.x), std::floorf(v.y), std::floorf(v.z)); }
	inline vec2d floor(vec2d const & v) { return vec2d(std::floor( v.x), std::floor( v.y)); }
	inline vec3d floor(vec3d const & v) { return vec3d(std::floor( v.x), std::floor( v.y), std::floor( v.z)); }

    inline vec2  normalize(vec2  const & v) { const float  im = 1.0f / std::sqrtf(v.x*v.x + v.y*v.y);                     return vec2( v.x*im, v.y*im); }
	inline vec3  normalize(vec3  const & v) { const float  im = 1.0f / std::sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);           return vec3( v.x*im, v.y*im, v.z*im); }
	inline vec4  normalize(vec4  const & v) { const float  im = 1.0f / std::sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); return vec4( v.x*im, v.y*im, v.z*im, v.w*im); }
	inline vec2d normalize(vec2d const & v) { const double im = 1.0  / std::sqrt( v.x*v.x + v.y*v.y);                     return vec2d(v.x*im, v.y*im); }
	inline vec3d normalize(vec3d const & v) { const double im = 1.0  / std::sqrt( v.x*v.x + v.y*v.y + v.z*v.z);           return vec3d(v.x*im, v.y*im, v.z*im); }
	inline vec4d normalize(vec4d const & v) { const double im = 1.0  / std::sqrt( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); return vec4d(v.x*im, v.y*im, v.z*im, v.w*im); }

	inline vec2  normalizeSafe(vec2  const & v) { const float  m2 = v.x*v.x + v.y*v.y;           if (m2 <= 0.000000001f) return vec2( 0.0f); const float  im = 1.0f / std::sqrtf(m2); return vec2(v.x*im, v.y*im); }
	inline vec3  normalizeSafe(vec3  const & v) { const float  m2 = v.x*v.x + v.y*v.y + v.z*v.z; if (m2 <= 0.000000001f) return vec3( 0.0f); const float  im = 1.0f / std::sqrtf(m2); return vec3(v.x*im, v.y*im, v.z*im); }
	inline vec3d normalizeSafe(vec3d const & v) { const double m2 = v.x*v.x + v.y*v.y + v.z*v.z; if (m2 <= 0.000000001 ) return vec3d(0.0 ); const double im = 1.0 / std::sqrt(m2); return vec3d( v.x*im, v.y*im, v.z*im); }

    inline vec2  mix(vec2  const & a, vec2  const & b, float  const f) { return vec2( a.x*(1.0f - f) + f*b.x, a.y*(1.0f - f) + f*b.y); }
	inline vec3  mix(vec3  const & a, vec3  const & b, float  const f) { return vec3( a.x*(1.0f - f) + f*b.x, a.y*(1.0f - f) + f*b.y, a.z*(1.0f - f) + f*b.z); }
	inline vec4  mix(vec4  const & a, vec4  const & b, float  const f) { return vec4( a.x*(1.0f - f) + f*b.x, a.y*(1.0f - f) + f*b.y, a.z*(1.0f - f) + f*b.z, a.w*(1.0f - f) + f*b.w); }
	inline vec2d mix(vec2d const & a, vec2d const & b, double const f) { return vec2d(a.x*(1.0  - f) + f*b.x, a.y*(1.0  - f) + f*b.y); }
	inline vec3d mix(vec3d const & a, vec3d const & b, double const f) { return vec3d(a.x*(1.0  - f) + f*b.x, a.y*(1.0  - f) + f*b.y, a.z*(1.0  - f) + f*b.z); }
	inline vec4d mix(vec4d const & a, vec4d const & b, double const f) { return vec4d(a.x*(1.0  - f) + f*b.x, a.y*(1.0  - f) + f*b.y, a.z*(1.0  - f) + f*b.z, a.w*(1.0  - f) + f*b.w); }

    inline float  length(vec2  const & v) { return std::sqrtf(v.x*v.x + v.y*v.y); }
	inline float  length(vec3  const & v) { return std::sqrtf(v.x*v.x + v.y*v.y + v.z*v.z); }
	inline float  length(vec4  const & v) { return std::sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); }
	inline double length(vec2d const & v) { return std::sqrt(v.x*v.x + v.y*v.y); }
	inline double length(vec3d const & v) { return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
	inline double length(vec4d const & v) { return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); }

	inline float  lengthSquared(vec2  const & v) { return v.x*v.x + v.y*v.y; }
	inline float  lengthSquared(vec3  const & v) { return v.x*v.x + v.y*v.y + v.z*v.z; }
	inline float  lengthSquared(vec4  const & v) { return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w; }
	inline double lengthSquared(vec2d const & v) { return v.x*v.x + v.y*v.y; }
	inline double lengthSquared(vec3d const & v) { return v.x*v.x + v.y*v.y + v.z*v.z; }
	inline double lengthSquared(vec4d const & v) { return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w; }

	inline float  inverseLength(vec2  const & v) { return 1.0f / std::sqrtf(v.x*v.x + v.y*v.y); }
	inline float  inverseLength(vec3  const & v) { return 1.0f / std::sqrtf(v.x*v.x + v.y*v.y + v.z*v.z); }
	inline float  inverseLength(vec4  const & v) { return 1.0f / std::sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); }
	inline double inverseLength(vec2d const & v) { return 1.0  / std::sqrt( v.x*v.x + v.y*v.y); }
	inline double inverseLength(vec3d const & v) { return 1.0  / std::sqrt( v.x*v.x + v.y*v.y + v.z*v.z); }
	inline double inverseLength(vec4d const & v) { return 1.0  / std::sqrt( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); }

	inline vec2  abs(const vec2  & v) { return vec2( std::fabsf(v.x), std::fabsf(v.y)); }
	inline vec3  abs(const vec3  & v) { return vec3( std::fabsf(v.x), std::fabsf(v.y), std::fabsf(v.z)); }
	inline vec4  abs(const vec4  & v) { return vec4( std::fabsf(v.x), std::fabsf(v.y), std::fabsf(v.z), std::fabsf(v.w)); }
	inline vec2d abs(const vec2d & v) { return vec2d(std::fabs( v.x), std::fabs( v.y)); }
	inline vec3d abs(const vec3d & v) { return vec3d(std::fabs( v.x), std::fabs( v.y), std::fabs(v.z)); }
	inline vec4d abs(const vec4d & v) { return vec4d(std::fabs( v.x), std::fabs( v.y), std::fabs(v.z), std::fabs(v.w)); }

	inline vec2  sin(const vec2  & v) { return vec2(std::sinf(v.x), std::sinf(v.y)); }
	inline vec2d sin(const vec2d & v) { return vec2d(std::sin(v.x), std::sin(v.y)); }
	inline vec3  sin(const vec3  & v) { return vec3(std::sinf(v.x), std::sinf(v.y), std::sinf(v.z)); }
	inline vec3d sin(const vec3d & v) { return vec3d(std::sin(v.x), std::sin(v.y), std::sin(v.z)); }
	inline vec2  cos(const vec2  & v) { return vec2(std::cosf(v.x), std::cosf(v.y)); }
	inline vec3  cos(const vec3  & v) { return vec3(std::cosf(v.x), std::cosf(v.y), std::cosf(v.z)); }
	inline vec2d cos(const vec2d & v) { return vec2d(std::cos(v.x), std::cos(v.y)); }
	inline vec3d cos(const vec3d & v) { return vec3d(std::cos(v.x), std::cos(v.y), std::cos(v.z)); }

	inline vec2  sqrt(const vec2  & v) { return vec2( std::sqrtf(v.x), std::sqrtf(v.y)); }
	inline vec3  sqrt(const vec3  & v) { return vec3( std::sqrtf(v.x), std::sqrtf(v.y), std::sqrtf(v.z)); }
	inline vec4  sqrt(const vec4  & v) { return vec4(std::sqrtf(v.x), std::sqrtf(v.y), std::sqrtf(v.z), std::sqrtf(v.w)); }
	inline vec2d sqrt(const vec2d & v) { return vec2d(std::sqrt( v.x), std::sqrt( v.y)); }
	inline vec3d sqrt(const vec3d & v) { return vec3d(std::sqrt( v.x), std::sqrt( v.y), std::sqrt(v.z)); }
	inline vec4d sqrt(const vec4d & v) { return vec4d(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z), std::sqrt(v.w)); }

	inline vec3  pow(const vec3  & v, const float   f) { return vec3( std::powf(v.x, f),   std::powf(v.y, f),   std::powf(v.z, f)); }
	inline vec3  pow(const vec3  & v, const vec3  & f) { return vec3( std::powf(v.x, f.x), std::powf(v.y, f.y), std::powf(v.z, f.z)); }
	inline vec3d pow(const vec3d & v, const double  f) { return vec3d(std::pow( v.x, f),   std::pow( v.y, f),   std::pow(v.z, f)); }
	inline vec3d pow(const vec3d & v, const vec3d & f) { return vec3d(std::pow( v.x, f.x), std::pow( v.y, f.y), std::pow(v.z, f.z)); }

	inline vec2  squared(const vec2  & v) { return v*v; }
	inline vec3  squared(const vec3  & v) { return v*v; }
	inline vec4  squared(const vec4  & v) { return v*v; }
	inline quat  squared(quat  const & a) { return quat(2.0f*a.x*a.w, 2.0f*a.y*a.w, 2.0f*a.z*a.w, a.w*a.w - a.x*a.x - a.y*a.y - a.z*a.z); }
	inline vec2d squared(const vec2d & v) { return v*v; }
	inline vec3d squared(const vec3d & v) { return v*v; }
	inline vec4d squared(const vec4d & v) { return v*v; }
	inline quatd squared(quatd const & a) { return quatd(2.0*a.x*a.w, 2.0*a.y*a.w, 2.0*a.z*a.w, a.w*a.w - a.x*a.x - a.y*a.y - a.z*a.z); }

	inline vec2  sign(const vec2  & v) { return vec2( (v.x >= 0.0f) ? 1.0f : -1.0f, (v.y >= 0.0f) ? 1.0f : -1.0f); }
	inline vec3  sign(const vec3  & v) { return vec3( (v.x >= 0.0f) ? 1.0f : -1.0f, (v.y >= 0.0f) ? 1.0f : -1.0f, (v.z >= 0.0f) ? 1.0f : -1.0f); }
	inline vec4  sign(const vec4  & v) { return vec4( (v.x >= 0.0f) ? 1.0f : -1.0f, (v.y >= 0.0f) ? 1.0f : -1.0f, (v.z >= 0.0f) ? 1.0f : -1.0f, (v.w >= 0.0f) ? 1.0f : -1.0f); }
	inline vec2d sign(const vec2d & v) { return vec2d((v.x >= 0.0 ) ? 1.0  : -1.0 , (v.y >= 0.0 ) ? 1.0  : -1.0 ); }
	inline vec3d sign(const vec3d & v) { return vec3d((v.x >= 0.0 ) ? 1.0  : -1.0 , (v.y >= 0.0 ) ? 1.0  : -1.0 , (v.z >= 0.0 ) ? 1.0  : -1.0 ); }
	inline vec4d sign(const vec4d & v) { return vec4d((v.x >= 0.0 ) ? 1.0  : -1.0 , (v.y >= 0.0 ) ? 1.0  : -1.0 , (v.z >= 0.0 ) ? 1.0  : -1.0 , (v.w >= 0.0 ) ? 1.0  : -1.0 ); }

	inline vec2  mod(const vec2  & v, float  s) { return vec2( std::fmodf(v.x, s), std::fmodf(v.y, s)); }
	inline vec3  mod(const vec3  & v, float  s) { return vec3( std::fmodf(v.x, s), std::fmodf(v.y, s), std::fmodf(v.z, s)); }
	inline vec4  mod(const vec4  & v, float  s) { return vec4( std::fmodf(v.x, s), std::fmodf(v.y, s), std::fmodf(v.z, s), std::fmodf(v.w, s)); }
	inline vec2d mod(const vec2d & v, double s) { return vec2d(std::fmod( v.x, s), std::fmod( v.y, s)); }
	inline vec3d mod(const vec3d & v, double s) { return vec3d(std::fmod( v.x, s), std::fmod( v.y, s), std::fmod( v.z, s)); }
	inline vec4d mod(const vec4d & v, double s) { return vec4d(std::fmod( v.x, s), std::fmod( v.y, s), std::fmod( v.z, s), std::fmod( v.w, s)); }

	inline vec2  log(const vec2  & v) { return vec2( std::logf(v.x), std::logf(v.y)); }
	inline vec3  log(const vec3  & v) { return vec3( std::logf(v.x), std::logf(v.y), std::logf(v.z)); }
	inline vec4  log(const vec4  & v) { return vec4( std::logf(v.x), std::logf(v.y), std::logf(v.z), std::logf(v.w)); }
	inline vec2d log(const vec2d & v) { return vec2d(std::log( v.x), std::log( v.y)); }
	inline vec3d log(const vec3d & v) { return vec3d(std::log( v.x), std::log( v.y), std::log( v.z)); }
	inline vec4d log(const vec4d & v) { return vec4d(std::log( v.x), std::log( v.y), std::log( v.z), std::log( v.w)); }
	inline quatd log(const quatd & q)
	{
		const double b = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z);
		if (std::abs(b) <= 0.00001*std::abs(q.w))
		{
			if (q.w<0.0) return quatd(0.0, 0.0, 0.0, 0.0);
			return quatd(0.0, 00, 0.0, std::log(q.w));
		}
		const double v = std::atan2(b, q.w);
		const double f = v / b;
		return quatd(f*q.x, f*q.y, f*q.z, std::log(q.w*q.w + b*b) / 2.0);
	}

	inline vec2  exp(const vec2  & v) { return vec2( std::expf(v.x), std::expf(v.y)); }
	inline vec3  exp(const vec3  & v) { return vec3( std::expf(v.x), std::expf(v.y), std::expf(v.z)); }
	inline vec4  exp(const vec4  & v) { return vec4( std::expf(v.x), std::expf(v.y), std::expf(v.z), std::expf(v.w)); }
	inline vec2d exp(const vec2d & v) { return vec2d(std::exp( v.x), std::exp( v.y)); }
	inline vec3d exp(const vec3d & v) { return vec3d(std::exp( v.x), std::exp( v.y), std::exp( v.z)); }
	inline vec4d exp(const vec4d & v) { return vec4d(std::exp( v.x), std::exp( v.y), std::exp( v.z), std::exp( v.w)); }
	inline quatd exp(const quatd & q)
	{
		const double b = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z);
		if (std::abs(b) <= 0.00001*std::abs(q.w))
			return quatd(0.0, 0., 0.0, std::exp(q.w));
		const double e = std::exp(q.w);
		const double f = std::sin(b) / b;
		return quatd(e*f*q.x, e*f*q.y, e*f*q.z, e*std::cos(b));
	}

	inline float  distance(const vec2   & a, const vec2  & b) { return length(a - b); }
	inline float  distance(const vec3   & a, const vec3  & b) { return length(a - b); }
	inline float  distance(const vec4   & a, const vec4  & b) { return length(a - b); }
	inline double distance(const vec2d  & a, const vec2d & b) { return length(a - b); }
	inline double distance(const vec3d  & a, const vec3d & b) { return length(a - b); }
	inline double distance(const vec4d  & a, const vec4d & b) { return length(a - b); }
	inline float  distance(const bound3 & b, const vec3 & p)
	{
		const vec3 bc = 0.5f*vec3(b.mMaxX + b.mMinX, b.mMaxY + b.mMinY, b.mMaxZ + b.mMinZ);
		const vec3 br = 0.5f*vec3(b.mMaxX - b.mMinX, b.mMaxY - b.mMinY, b.mMaxZ - b.mMinZ);
		vec3 d = abs(p - bc) - br;
		return fminf(maxcomp(d), 0.0f) + length(vmax(d, 0.0f));
	}
	inline double distance(const bound3d & b, const vec3d & p)
	{
		const vec3d bc = 0.5*vec3d(b.mMaxX + b.mMinX, b.mMaxY + b.mMinY, b.mMaxZ + b.mMinZ);
		const vec3d br = 0.5*vec3d(b.mMaxX - b.mMinX, b.mMaxY - b.mMinY, b.mMaxZ - b.mMinZ);
		const vec3d d = abs(p - bc) - br;
		return fmin(fmax(d.x, fmax(d.y, d.z)), 0.0) + length(vmax(d, 0.0));
	}

	inline float determinant(mat2x2 const & m) { return m.m[0] * m.m[3] - m.m[1] * m.m[2]; }
	inline float determinant(mat3x3 const & m) { return m.m[0] * m.m[4] * m.m[8] + m.m[3] * m.m[7] * m.m[2] + m.m[1] * m.m[5] * m.m[6] - m.m[2] * m.m[4] * m.m[6] - m.m[1] * m.m[3] * m.m[8] - m.m[5] * m.m[7] * m.m[0]; }
	inline float determinant(mat4x4 const & m)
	{
		const float inv0  =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
		const float inv4  = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
		const float inv8  =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
		const float inv12 = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
		return m[0] * inv0 + m[1] * inv4 + m[2] * inv8 + m[3] * inv12;
	}
	inline double determinant(mat2x2d const & m) { return m.m[0] * m.m[3] - m.m[1] * m.m[2]; }
	inline double determinant(mat3x3d const & m) { return m.m[0] * m.m[4] * m.m[8] + m.m[3] * m.m[7] * m.m[2] + m.m[1] * m.m[5] * m.m[6] - m.m[2] * m.m[4] * m.m[6] - m.m[1] * m.m[3] * m.m[8] - m.m[5] * m.m[7] * m.m[0]; }
	inline double determinant(mat4x4d const & m)
	{
		const double inv0  =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
		const double inv4  = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
		const double inv8  =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
		const double inv12 = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
		return m[0] * inv0 + m[1] * inv4 + m[2] * inv8 + m[3] * inv12;
	}

	inline mat2x2  transpose(mat2x2  const & m) { return mat2x2( m.m[0], m.m[2], m.m[1], m.m[3]); }
	inline mat3x3  transpose(mat3x3  const & m) { return mat3x3( m.m[0], m.m[3], m.m[6], m.m[1], m.m[4], m.m[7], m.m[2], m.m[5], m.m[8]); }
	inline mat4x4  transpose(mat4x4  const & m) { return mat4x4( m.m[0], m.m[4], m.m[8], m.m[12], m.m[1], m.m[5], m.m[9], m.m[13], m.m[2], m.m[6], m.m[10], m.m[14], m.m[3], m.m[7], m.m[11], m.m[15]); }
	inline mat2x2d transpose(mat2x2d const & m) { return mat2x2d(m.m[0], m.m[2], m.m[1], m.m[3]); }
	inline mat3x3d transpose(mat3x3d const & m) { return mat3x3d(m.m[0], m.m[3], m.m[6], m.m[1], m.m[4], m.m[7], m.m[2], m.m[5], m.m[8]); }
	inline mat4x4d transpose(mat4x4d const & m) { return mat4x4d(m.m[0], m.m[4], m.m[8], m.m[12], m.m[1], m.m[5], m.m[9], m.m[13], m.m[2], m.m[6], m.m[10], m.m[14], m.m[3], m.m[7], m.m[11], m.m[15]); }

	inline vec3   getsize(bound3  const & bbox) { return vec3(bbox.mMaxX - bbox.mMinX, bbox.mMaxY - bbox.mMinY, bbox.mMaxZ - bbox.mMinZ); }
	inline vec3d  getsize(bound3d const & bbox) { return vec3d(bbox.mMaxX - bbox.mMinX, bbox.mMaxY - bbox.mMinY, bbox.mMaxZ - bbox.mMinZ); }
	inline vec3   getradiius(bound3  const & bbox) { return vec3(0.5f*(bbox.mMaxX - bbox.mMinX), 0.5f*(bbox.mMaxY - bbox.mMinY), 0.5f*(bbox.mMaxZ - bbox.mMinZ)); }
	inline vec3d  getradiius(bound3d const & bbox) { return vec3d(0.5* (bbox.mMaxX - bbox.mMinX), 0.5* (bbox.mMaxY - bbox.mMinY), 0.5* (bbox.mMaxZ - bbox.mMinZ)); }
	inline vec3   getcenter(bound3  const & bbox) { return vec3(0.5f*(bbox.mMinX + bbox.mMaxX), 0.5f*(bbox.mMinY + bbox.mMaxY), 0.5f*(bbox.mMinZ + bbox.mMaxZ)); }
	inline vec3d  getcenter(bound3d const & bbox) { return vec3d(0.5* (bbox.mMinX + bbox.mMaxX), 0.5* (bbox.mMinY + bbox.mMaxY), 0.5* (bbox.mMinZ + bbox.mMaxZ)); }
	inline float     volume(bound3  const & bbox) { return (bbox.mMaxX - bbox.mMinX)*(bbox.mMaxY - bbox.mMinY)*(bbox.mMaxZ - bbox.mMinZ); }
	inline double    volume(bound3d const & bbox) { return (bbox.mMaxX - bbox.mMinX)*(bbox.mMaxY - bbox.mMinY)*(bbox.mMaxZ - bbox.mMinZ); }
	inline float  diagonalSquared(bound3  const & bbox) { const float  dx = bbox.mMaxX - bbox.mMinX, dy = bbox.mMaxY - bbox.mMinY, dz = bbox.mMaxZ - bbox.mMinZ; return dx*dx + dy*dy + dz*dz; }
	inline double diagonalSquared(bound3d const & bbox) { const double dx = bbox.mMaxX - bbox.mMinX, dy = bbox.mMaxY - bbox.mMinY, dz = bbox.mMaxZ - bbox.mMinZ; return dx*dx + dy*dy + dz*dz; }
	inline float  diagonal(bound3  const & bbox) { return std::sqrtf(diagonalSquared(bbox)); }
	inline double diagonal(bound3d const & bbox) { return std::sqrt(diagonalSquared(bbox)); }

	inline vec2  smoothstep(float  a, float  b, const vec2  & v) { vec2  x = clamp01((v - vec2( a)) / (b - a)); return x*x*(3.0f - 2.0f*x); }
	inline vec3  smoothstep(float  a, float  b, const vec3  & v) { vec3  x = clamp01((v - vec3( a)) / (b - a)); return x*x*(3.0f - 2.0f*x); }
	inline vec4  smoothstep(float  a, float  b, const vec4  & v) { vec4  x = clamp01((v - vec4( a)) / (b - a)); return x*x*(3.0f - 2.0f*x); }
	inline vec2d smoothstep(double a, double b, const vec2d & v) { vec2d x = clamp01((v - vec2d(a)) / (b - a)); return x*x*(3.0  - 2.0 *x); }
	inline vec3d smoothstep(double a, double b, const vec3d & v) { vec3d x = clamp01((v - vec3d(a)) / (b - a)); return x*x*(3.0  - 2.0 *x); }
	inline vec4d smoothstep(double a, double b, const vec4d & v) { vec4d x = clamp01((v - vec4d(a)) / (b - a)); return x*x*(3.0  - 2.0 *x); }


	// TODO - move this to class members
	inline mat3x3  setScale3(const vec3 & s) { return mat3x3(s.x, 0.0f, 0.0f, 0.0f, s.y, 0.0f, 0.0f, 0.0f, s.z); }
	inline mat4x4  setScale4(const vec3 & s) { return mat4x4(s.x, 0.0f, 0.0f, 0.0f, 0.0f, s.y, 0.0f, 0.0f, 0.0f, 0.0f, s.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	inline mat4x4  setScale4(float x, float y, float z) { return setScale4(vec3(x, y, z)); }
	inline mat4x4d setScale4(const vec3d & s) { return mat4x4d(s.x, 0.0, 0.0, 0.0, 0.0, s.y, 0.0, 0.0, 0.0, 0.0, s.z, 0.0, 0.0, 0.0, 0.0, 1.0); }
	inline mat4x4d setScale4(double x, double y, double z) { return setScale4(vec3d(x, y, z)); } 
	inline mat4x4d setScale4(double s) { return setScale4(vec3d(s, s, s)); }
	// TODO - move this to class members
	inline mat4x4d setTranslation(const vec3d & p) { return mat4x4d(1.0, 0.0, 0.0, p.x, 0.0, 1.0, 0.0, p.y, 0.0, 0.0, 1.0, p.z, 0.0, 0.0, 0.0, 1.0); }
	inline mat4x4d setTranslation(double x, double y, double z) { return setTranslation(vec3d(x, y, z)); }
	inline mat4x4  setTranslation(const vec3 & p) { return mat4x4(1.0f, 0.0f, 0.0f, p.x, 0.0f, 1.0f, 0.0f, p.y, 0.0f, 0.0f, 1.0f, p.z, 0.0f, 0.0f, 0.0f, 1.0f); }
	inline mat4x4  setTranslation(float x, float y, float z) { return setTranslation(vec3(x, y, z)); }
	inline trans3d setTranslationT(const vec3d & p) { return trans3d( quatd::identity(), 1.0, p); }

	inline mat4x4d setFlipX4(void) { return mat4x4d(-1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0); };
	inline mat4x4d setFlipY4(void) { return mat4x4d(1.0, 0.0, 0.0, 0.0, 0.0,-1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0); };
	inline mat4x4d setFlipZ4(void) { return mat4x4d(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0); };

	//----------------
	inline mat2x2 setRotation2(const float t)
	{
		const float co = cosf(t);
		const float si = sinf(t);
		return mat2x2(co, -si, si, co);
	}

	inline mat2x2 setRotation2(vec2 const & v)
	{
		return mat2x2(v.x, -v.y, v.y, v.x);
	}

	inline mat3x3d setRotation3(const quatd & q) // quaternion
	{
		return mat3x3d(q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z, 2.0*(q.x * q.y - q.w * q.z), 2.0*(q.x * q.z + q.w * q.y),
			2.0*(q.x * q.y + q.w * q.z), q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z, 2.0*(q.y * q.z - q.w * q.x),
			2.0*(q.x * q.z - q.w * q.y), 2.0*(q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);
	}
	inline mat4x4 setRotation4(const quat & q) // quaternion
	{
		return mat4x4(q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z, 2.0f*(q.x * q.y - q.w * q.z), 2.0f*(q.x * q.z + q.w * q.y), 0.0f,
			2.0f*(q.x * q.y + q.w * q.z), q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z, 2.0f*(q.y * q.z - q.w * q.x), 0.0f,
			2.0f*(q.x * q.z - q.w * q.y), 2.0f*(q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}
	inline mat4x4d setRotation4(const quatd & q) // quaternion
	{
		return mat4x4d(q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z, 2.0*(q.x * q.y - q.w * q.z), 2.0*(q.x * q.z + q.w * q.y), 0.0,
			2.0*(q.x * q.y + q.w * q.z), q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z, 2.0*(q.y * q.z - q.w * q.x), 0.0,
			2.0*(q.x * q.z - q.w * q.y), 2.0*(q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z, 0.0,
			0.0, 0.0, 0.0, 1.0);
	}

	inline mat3x3 setRotation3(const vec3 & a, const float t) // axis, angle
	{
		const float sint = sinf(t);
		const float cost = cosf(t);
		const float icost = 1.0f - cost;
		return mat3x3(a.x*a.x*icost + cost, a.y*a.x*icost - sint*a.z, a.z*a.x*icost + sint*a.y,
			          a.x*a.y*icost + sint*a.z, a.y*a.y*icost + cost, a.z*a.y*icost - sint*a.x,
			          a.x*a.z*icost - sint*a.y, a.y*a.z*icost + sint*a.x, a.z*a.z*icost + cost);
	}


	inline mat4x4 setRotation4(const vec3 & a, const float t) // axis, angle
	{
		const float sint = sinf(t);
		const float cost = cosf(t);
		const float icost = 1.0f - cost;
		return mat4x4(a.x*a.x*icost + cost, a.y*a.x*icost - sint*a.z, a.z*a.x*icost + sint*a.y, 0.0f,
			a.x*a.y*icost + sint*a.z, a.y*a.y*icost + cost, a.z*a.y*icost - sint*a.x, 0.0f,
			a.x*a.z*icost - sint*a.y, a.y*a.z*icost + sint*a.x, a.z*a.z*icost + cost, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline mat4x4d setRotation4(const vec3d & a, const double t) // axis, angle
	{
		const double sint = std::sin(t);
		const double cost = std::cos(t);
		const double icost = 1.0 - cost;
		return mat4x4d(a.x*a.x*icost + cost, a.y*a.x*icost - sint*a.z, a.z*a.x*icost + sint*a.y, 0.0,
			a.x*a.y*icost + sint*a.z, a.y*a.y*icost + cost, a.z*a.y*icost - sint*a.x, 0.0,
			a.x*a.z*icost - sint*a.y, a.y*a.z*icost + sint*a.x, a.z*a.z*icost + cost, 0.0,
			0.0, 0.0, 0.0, 1.0);
	}

	inline mat3x3 setRotation3(float x, float y, float z) //euler
	{
		const float a = sinf(x);
		const float b = cosf(x);
		const float c = sinf(y);
		const float d = cosf(y);
		const float e = sinf(z);
		const float f = cosf(z);
		const float ac = a*c;
		const float bc = b*c;
		return mat3x3(d*f, d*e, -c, ac*f - b*e, ac*e + b*f, a*d, bc*f + a*e, bc*e - a*f, b*d);
	}
	inline mat3x3d setRotation3(double x, double y, double z) //euler
	{
		const double a = std::sin(x);
		const double b = std::cos(x);
		const double c = std::sin(y);
		const double d = std::cos(y);
		const double e = std::sin(z);
		const double f = std::cos(z);
		const double ac = a*c;
		const double bc = b*c;
		return mat3x3d(d*f, d*e, -c, ac*f - b*e, ac*e + b*f, a*d, bc*f + a*e, bc*e - a*f, b*d);
	}
	inline mat4x4 setRotation4(const vec3 & r) //euler
	{
		const float a = sinf(r.x);
		const float b = cosf(r.x);
		const float c = sinf(r.y);
		const float d = cosf(r.y);
		const float e = sinf(r.z);
		const float f = cosf(r.z);
		const float ac = a*c;
		const float bc = b*c;
		return mat4x4(d*f, d*e, -c, 0.0f, ac*f - b*e, ac*e + b*f, a*d, 0.0f, bc*f + a*e, bc*e - a*f, b*d, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	inline mat4x4d setRotation4(const vec3d & r)  //euler
	{
		const double a = std::sin(r.x);
		const double b = std::cos(r.x);
		const double c = std::sin(r.y);
		const double d = std::cos(r.y);
		const double e = std::sin(r.z);
		const double f = std::cos(r.z);
		const double ac = a*c;
		const double bc = b*c;
		return mat4x4d(d*f, d*e, -c, 0.0, ac*f - b*e, ac*e + b*f, a*d, 0.0, bc*f + a*e, bc*e - a*f, b*d, 0.0, 0.0, 0.0, 0.0, 1.0);
	}
	inline mat3x3  setRotation3(const vec3  & xyz) { return setRotation3(xyz.x, xyz.y, xyz.z); }
	inline mat3x3d setRotation3(const vec3d & xyz) { return setRotation3(xyz.x, xyz.y, xyz.z); }
	inline mat4x4  setRotation4(float  x, float  y, float  z) { return setRotation4(vec3( x, y, z)); }
	inline mat4x4d setRotation4(double x, double y, double z) { return setRotation4(vec3d(x, y, z)); }

	inline mat4x4 setRotationX(const float t)
	{
		const float sint = sinf(t);
		const float cost = cosf(t);
		return mat4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cost, sint, 0.0f, 0.0f, -sint, cost, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline mat4x4d setRotationX(const double t)
	{
		const double sint = std::sin(t);
		const double cost = std::cos(t);
		return mat4x4d(1.0, 0.0, 0.0, 0.0, 0.0, cost, sint, 0.0, 0.0, -sint, cost, 0.0, 0.0, 0.0, 0.0, 1.0);
	}

	inline mat4x4 setRotationY(const float t)
	{
		const float sint = sinf(t);
		const float cost = cosf(t);
		return mat4x4(cost, 0.0f, -sint, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sint, 0.0f, cost, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline mat4x4 setRotationZ(const float t)
	{
		const float sint = sinf(t);
		const float cost = cosf(t);
		return mat4x4(cost, -sint, 0.0f, 0.0f, sint, cost, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline mat4x4d setRotationY(const double t)
	{
		const double sint = std::sin(t);
		const double cost = std::cos(t);
		return mat4x4d(cost, 0.0, -sint, 0.0, 0.0, 1.0, 0.0, 0.0, sint, 0.0, cost, 0.0, 0.0, 0.0, 0.0, 1.0);
	}

	inline mat4x4d setRotationZ(const double t)
	{
		const double sint = std::sin(t);
		const double cost = std::cos(t);
		return mat4x4d(cost, -sint, 0.0, 0.0, sint, cost, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	}
	

	inline mat4x4  setSwapYZ( void) { return mat4x4( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	inline mat4x4d setSwapYZd(void) { return mat4x4d(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0); }


	inline vec2d perpendicular(vec2d const & v) { return vec2d(v.y, -v.x); }
	inline vec2  perpendicular(vec2  const & v) { return vec2(v.y, -v.x); }

	inline vec2  fromPolar(const float  a) { return vec2(std::cosf(a), std::sinf(a)); }
	inline vec2d fromPolar(const double a) { return vec2d(std::cos(a), std::sin(a)); }

	inline vec3d cross(vec3d const & a, vec3d const & b) { return vec3d(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }
	inline vec3  cross(vec3  const & a, vec3  const & b) { return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }

	inline vec3  orientate(const vec3  & v, const vec3  & dir) { vec3  res = v; const float  kk = dot(dir, v); if (kk<0.0f) res -= 2.0f*dir*kk; return res; }
	inline vec3d orientate(const vec3d & v, const vec3d & dir) { vec3d res = v; const double kk = dot(dir, v); if (kk<0.0) res -= 2.0 *dir*kk; return res; }


	inline mat4x4 buildBase4(const vec3 & n)
	{
		const vec3 up = (std::fabsf(n.z) < 0.9f) ? vec3(0.0f, 0.0f, 1.0f) : vec3(1.0f, 0.0f, 0.0f);
		const vec3 vv = normalize(cross(n, up));
		const vec3 uu = normalize(cross(vv, n));
		return mat4x4(uu.x, vv.x, n.x, 0.0f, uu.y, vv.y, n.y, 0.0f, uu.z, vv.z, n.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	inline mat4x4d buildBase4(const vec3d & n)
	{
		const vec3d up = (std::fabs(n.z) < 0.9f) ? vec3d(0.0, 0.0, 1.0) : vec3d(1.0, 0.0, 0.0);
		const vec3d vv = normalize(cross(n, up));
		const vec3d uu = normalize(cross(vv, n));
		return mat4x4d(uu.x, vv.x, n.x, 0.0, uu.y, vv.y, n.y, 0.0, uu.z, vv.z, n.z, 0.0, 0.0, 0.0, 0.0, 1.0);
	}
	inline mat4x4  buildBase4(const vec3  & u, const vec3  & v, const vec3  & n) { return mat4x4(u.x, v.x, n.x, 0.0f, u.y, v.y, n.y, 0.0f, u.z, v.z, n.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	inline mat4x4d buildBase4(const vec3d & u, const vec3d & v, const vec3d & n) { return mat4x4d(u.x, v.x, n.x, 0.0, u.y, v.y, n.y, 0.0, u.z, v.z, n.z, 0.0, 0.0, 0.0, 0.0, 1.0); }

	inline mat3x3 buildBase(const vec3 & n)
	{
		const vec3 up = (std::fabsf(n.z) < 0.9f) ? vec3(0.0f, 0.0f, 1.0f) : vec3(1.0f, 0.0f, 0.0f);
		const vec3 vv = normalize(cross(n, up));
		const vec3 uu = normalize(cross(vv, n));
		return mat3x3(uu.x, vv.x, n.x, uu.y, vv.y, n.y, uu.z, vv.z, n.z);
	}
	inline void buildBase(const vec3 & n, vec3 & uu, vec3 & vv)
	{
		const vec3 up = (std::fabsf(n.z) < 0.9f) ? vec3(0.0f, 0.0f, 1.0f) : vec3(1.0f, 0.0f, 0.0f);
		vv = normalize(cross(n, up));
		uu = normalize(cross(vv, n));
	}
	inline void buildBase(const vec3d & n, vec3d & uu, vec3d & vv)
	{
		const vec3d up = (std::fabs(n.z) < 0.9f) ? vec3d(0.0, 0.0, 1.0) : vec3d(1.0, 0.0, 0.0);
		vv = normalize(cross(n, up));
		uu = normalize(cross(vv, n));
	}




    // make a plane that goes through pointa a, b, c
    inline vec4 makePlane(vec3 const & a, vec3 const & b, vec3 const & c)
    {
        //    const vec3 n = normalize( cross( c-a, b-a ) );
        const vec3 n = normalize(cross(b - a, c - a));
        return vec4(n, -dot(a, n));
    }

    inline vec3 intersectPlanes(vec4 const & p1, vec4 const & p2, vec4 const & p3)
    {
        const float den = dot(p1.xyz(), cross(p2.xyz(), p3.xyz()));

        if (den == 0.0f)
            return vec3(0.0f);

        vec3 res = p1.w * cross(p2.xyz(), p3.xyz()) +
            p2.w * cross(p3.xyz(), p1.xyz()) +
            p3.w * cross(p1.xyz(), p2.xyz());

        return res * (-1.0f / den);
    }

	inline vec3 rotate(const vec3 & v, float t, const vec3 & a)
    {
        const float sint = sinf(t);
        const float cost = cosf(t);
        const float icost = 1.0f - cost;

        const mat3x3 m = mat3x3(a.x*a.x*icost + cost,
            a.y*a.x*icost - sint*a.z,
            a.z*a.x*icost + sint*a.y,

            a.x*a.y*icost + sint*a.z,
            a.y*a.y*icost + cost,
            a.z*a.y*icost - sint*a.x,

            a.x*a.z*icost - sint*a.y,
            a.y*a.z*icost + sint*a.x,
            a.z*a.z*icost + cost);
        return m * v;
    }

    inline vec3 rotate(const vec3 & v, float cost, float sint, const vec3 & a)
    {
        const float icost = 1.0f - cost;

        const mat3x3 m = mat3x3(a.x*a.x*icost + cost,
            a.y*a.x*icost - sint*a.z,
            a.z*a.x*icost + sint*a.y,

            a.x*a.y*icost + sint*a.z,
            a.y*a.y*icost + cost,
            a.z*a.y*icost - sint*a.x,

            a.x*a.z*icost - sint*a.y,
            a.y*a.z*icost + sint*a.x,
            a.z*a.z*icost + cost);
        return m * v;
    }

    inline vec3 rotateX(const vec3 &v, float a)
    {
        const float si = sinf(a);
        const float co = cosf(a);

        return vec3(v[0], v[1] * co - v[2] * si, v[1] * si + v[2] * co);
    }

    inline vec3 rotateY(const vec3 & v, float a)
    {
        const float si = sinf(a);
        const float co = cosf(a);

        return vec3(v[0] * co + v[2] * si, v[1], -v[0] * si + v[2] * co);
    }

    inline vec3 rotateZ(const vec3 & v, float a)
    {
        const float si = sinf(a);
        const float co = cosf(a);

        return vec3(v[0] * co + v[1] * si, -v[0] * si + v[1] * co, v[2]);
    }

	inline bool isIdentity(const mat2x2 & m)
	{
		if (m.m[0] != 1.0)return false;
		if (m.m[1] != 0.0)return false;
		if (m.m[2] != 0.0)return false;
		if (m.m[3] != 1.0)return false;
		return true;
	}
	inline bool isIdentity(const quatd & t)
	{
		if (t.x != 0.0) return false;
		if (t.y != 0.0) return false;
		if (t.z != 0.0) return false;
		if (t.w != 1.0) return false;
		return true;
	}
	inline bool isIdentity(const trans3d & t)
	{
		if (!isIdentity(t.mRotation)) return false;
		if (t.mScale!=1.0) return false;
		if (t.mTranslation.x != 0.0) return false;
		if (t.mTranslation.y != 0.0) return false;
		if (t.mTranslation.z != 0.0) return false;
		return true;
	}

	inline quatd invert(const quatd & q)
	{
		const double im = 1.0 / (q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
		return quatd(-q.x*im, -q.y*im, -q.z*im, q.w*im);
	}

	inline trans3d invert(const trans3d & t)
	{
		const quatd q = invert(t.mRotation);
		const double s = 1.0 / t.mScale;
		return trans3d(q, s, q*(-s*t.mTranslation));
	}

    inline mat4x4 invertFast(mat4x4 const & m)
    {
        mat4x4 inv = mat4x4(  
			 m.m[5] * m.m[10] * m.m[15] - m.m[5] * m.m[11] * m.m[14] - m.m[9] * m.m[6] * m.m[15] + m.m[9] * m.m[7] * m.m[14] + m.m[13] * m.m[6] * m.m[11] - m.m[13] * m.m[7] * m.m[10],
            -m.m[1] * m.m[10] * m.m[15] + m.m[1] * m.m[11] * m.m[14] + m.m[9] * m.m[2] * m.m[15] - m.m[9] * m.m[3] * m.m[14] - m.m[13] * m.m[2] * m.m[11] + m.m[13] * m.m[3] * m.m[10],
             m.m[1] * m.m[ 6] * m.m[15] - m.m[1] * m.m[ 7] * m.m[14] - m.m[5] * m.m[2] * m.m[15] + m.m[5] * m.m[3] * m.m[14] + m.m[13] * m.m[2] * m.m[ 7] - m.m[13] * m.m[3] * m.m[ 6],
            -m.m[1] * m.m[ 6] * m.m[11] + m.m[1] * m.m[ 7] * m.m[10] + m.m[5] * m.m[2] * m.m[11] - m.m[5] * m.m[3] * m.m[10] - m.m[ 9] * m.m[2] * m.m[ 7] + m.m[ 9] * m.m[3] * m.m[ 6],
            -m.m[4] * m.m[10] * m.m[15] + m.m[4] * m.m[11] * m.m[14] + m.m[8] * m.m[6] * m.m[15] - m.m[8] * m.m[7] * m.m[14] - m.m[12] * m.m[6] * m.m[11] + m.m[12] * m.m[7] * m.m[10],
             m.m[0] * m.m[10] * m.m[15] - m.m[0] * m.m[11] * m.m[14] - m.m[8] * m.m[2] * m.m[15] + m.m[8] * m.m[3] * m.m[14] + m.m[12] * m.m[2] * m.m[11] - m.m[12] * m.m[3] * m.m[10],
            -m.m[0] * m.m[ 6] * m.m[15] + m.m[0] * m.m[ 7] * m.m[14] + m.m[4] * m.m[2] * m.m[15] - m.m[4] * m.m[3] * m.m[14] - m.m[12] * m.m[2] * m.m[ 7] + m.m[12] * m.m[3] * m.m[ 6],
             m.m[0] * m.m[ 6] * m.m[11] - m.m[0] * m.m[ 7] * m.m[10] - m.m[4] * m.m[2] * m.m[11] + m.m[4] * m.m[3] * m.m[10] + m.m[ 8] * m.m[2] * m.m[ 7] - m.m[ 8] * m.m[3] * m.m[ 6],
             m.m[4] * m.m[ 9] * m.m[15] - m.m[4] * m.m[11] * m.m[13] - m.m[8] * m.m[5] * m.m[15] + m.m[8] * m.m[7] * m.m[13] + m.m[12] * m.m[5] * m.m[11] - m.m[12] * m.m[7] * m.m[ 9],
            -m.m[0] * m.m[ 9] * m.m[15] + m.m[0] * m.m[11] * m.m[13] + m.m[8] * m.m[1] * m.m[15] - m.m[8] * m.m[3] * m.m[13] - m.m[12] * m.m[1] * m.m[11] + m.m[12] * m.m[3] * m.m[ 9],
             m.m[0] * m.m[ 5] * m.m[15] - m.m[0] * m.m[ 7] * m.m[13] - m.m[4] * m.m[1] * m.m[15] + m.m[4] * m.m[3] * m.m[13] + m.m[12] * m.m[1] * m.m[ 7] - m.m[12] * m.m[3] * m.m[ 5],
            -m.m[0] * m.m[ 5] * m.m[11] + m.m[0] * m.m[ 7] * m.m[ 9] + m.m[4] * m.m[1] * m.m[11] - m.m[4] * m.m[3] * m.m[ 9] - m.m[ 8] * m.m[1] * m.m[ 7] + m.m[ 8] * m.m[3] * m.m[ 5],
            -m.m[4] * m.m[ 9] * m.m[14] + m.m[4] * m.m[10] * m.m[13] + m.m[8] * m.m[5] * m.m[14] - m.m[8] * m.m[6] * m.m[13] - m.m[12] * m.m[5] * m.m[10] + m.m[12] * m.m[6] * m.m[ 9],
             m.m[0] * m.m[ 9] * m.m[14] - m.m[0] * m.m[10] * m.m[13] - m.m[8] * m.m[1] * m.m[14] + m.m[8] * m.m[2] * m.m[13] + m.m[12] * m.m[1] * m.m[10] - m.m[12] * m.m[2] * m.m[ 9],
            -m.m[0] * m.m[ 5] * m.m[14] + m.m[0] * m.m[ 6] * m.m[13] + m.m[4] * m.m[1] * m.m[14] - m.m[4] * m.m[2] * m.m[13] - m.m[12] * m.m[1] * m.m[ 6] + m.m[12] * m.m[2] * m.m[ 5],
             m.m[0] * m.m[ 5] * m.m[10] - m.m[0] * m.m[ 6] * m.m[ 9] - m.m[4] * m.m[1] * m.m[10] + m.m[4] * m.m[2] * m.m[ 9] + m.m[ 8] * m.m[1] * m.m[ 6] - m.m[ 8] * m.m[2] * m.m[ 5]);

        float det = m.m[0] * inv.m[0] + m.m[1] * inv.m[4] + m.m[2] * inv.m[8] + m.m[3] * inv.m[12];
        det = 1.0f / det;
        for (int i = 0; i < 16; i++) inv.m[i] = inv.m[i] * det;

        return inv;
    }

    inline mat4x4 invert(mat4x4 const & src, int *status = 0)
    {
        int   i, j, k, swap;
        float t, temp[4][4];


        for (i = 0; i<4; i++)
            for (j = 0; j<4; j++)
                temp[i][j] = src[i * 4 + j];

        float inv[16];
        for (i = 0; i<16; i++) inv[i] = 0.0f;
        inv[0] = 1.0f;
        inv[5] = 1.0f;
        inv[10] = 1.0f;
        inv[15] = 1.0f;

        for (i = 0; i<4; i++)
        {
            // Look for largest element in column
            swap = i;
            for (j = i + 1; j < 4; j++)
                if (fabsf(temp[j][i]) > fabsf(temp[i][i]))
                    swap = j;

            if (swap != i)
            {
                // Swap rows.
                for (k = 0; k<4; k++)
                {
                    t = temp[i][k];
                    temp[i][k] = temp[swap][k];
                    temp[swap][k] = t;

                    t = inv[i * 4 + k];
                    inv[i * 4 + k] = inv[swap * 4 + k];
                    inv[swap * 4 + k] = t;
                }
            }

            // pivot==0 -> singular matrix!
            if (temp[i][i] == 0)
            {
                if (status) status[0] = 0;
                return mat4x4(0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f);
            }

            t = temp[i][i];
            t = 1.0f / t;
            for (k = 0; k<4; k++)
            {
                temp[i][k] *= t;
                inv[i * 4 + k] *= t;
            }

            for (j = 0; j<4; j++)
            {
                if (j != i)
                {
                    t = temp[j][i];
                    for (k = 0; k<4; k++)
                    {
                        temp[j][k] -= temp[i][k] * t;
                        inv[j * 4 + k] -= inv[i * 4 + k] * t;
                    }
                }
            }
        }

        if (status) status[0] = 1;

        return mat4x4(inv[0], inv[1], inv[2], inv[3],
            inv[4], inv[5], inv[6], inv[7],
            inv[8], inv[9], inv[10], inv[11],
            inv[12], inv[13], inv[14], inv[15]);

    }

    inline mat4x4 extractRotation(mat4x4 const & m)
    {
        return mat4x4(m.m[0], m.m[4], m.m[8], 0.0f, m.m[1], m.m[5], m.m[9], 0.0f, m.m[2], m.m[6], m.m[10], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    inline vec3 extractTranslation(mat4x4 const & m)
    {
        return vec3(m.m[3], m.m[7], m.m[11]);
    }

    inline vec3 extractScale(mat4x4 const & m)
    {
        const vec3 v1a = vec3(1.0f, 0.0f, 0.0f);
        const vec3 v2a = vec3(0.0f, 1.0f, 0.0f);
        const vec3 v3a = vec3(0.0f, 0.0f, 1.0f);
        const vec3 v1b = (m*vec4(v1a, 0.0f)).xyz();
        const vec3 v2b = (m*vec4(v2a, 0.0f)).xyz();
        const vec3 v3b = (m*vec4(v3a, 0.0f)).xyz();

        return vec3(length(v1b), length(v2b), length(v3b));
    }

	inline float extractAverageScale(mat4x4 const & m)
	{
		return length((m* vec4(0.57735026919f, 0.57735026919f, 0.57735026919f, 0.0f)).xyz());
	}

    inline vec3 extractRotationEuler(const mat4x4 & m)
    {
        vec3 res = vec3(0.0f);
        if (m.m[0] == 1.0f)
        {
            res.x = atan2f(m.m[2], m.m[11]);
            res.y = 0.0f;
            res.z = 0.0f;

        }
        else if (m.m[0] == -1.0f)
        {
            res.x = atan2f(m.m[2], m.m[11]);
            res.y = 0.0f;
            res.z = 0.0f;
        }
        else
        {

            res.x = atan2f(-m.m[9], m.m[10]);
            res.y = atan2f(m.m[8], sqrtf(m.m[9] * m.m[9] + m.m[10] * m.m[10]));
            res.z = atan2f(m.m[4], m.m[0]);
        }
        return res;
    }
	    


    inline vec2 getNearFar_FromPerspectiveMatrix(const mat4x4 & m)
    {
        const float c = m.m[10];
        const float d = m.m[11];
        return vec2(d / (c - 1.0f), d / (c + 1.0f));
    }
    // Zeye = a / (Zbuffer[0..1] + b);
    inline vec2 getZBufferToZetaEye_FromPerspectiveMatrix(const mat4x4 & m)
    {
        return vec2(m.m[11] / 2.0f, (m.m[10] - 1.0f) / 2.0f);
    }
    // Zeye = a / (Zclip[-1..1] + b);
    inline vec2 getZClipToZetaEye_FromPerspectiveMatrix(const mat4x4 & m)
    {
        return vec2(0.0f, 0.0f);//vec2( -m.m[11], m.m[10] );
    }

    inline mat4x4 setOrtho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        const float x = 2.0f / (right - left);
        const float y = 2.0f / (top - bottom);
        const float a = (right + left) / (right - left);
        const float b = (top + bottom) / (top - bottom);
        const float c = -2.0f / (zfar - znear);
        const float d = -(zfar + znear) / (zfar - znear);
		return mat4x4(x, 0.0f, 0.0f, a, 0.0f, y, 0.0f, b, 0.0f, 0.0f, c, d, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	inline mat4x4d setOrtho(double left, double right, double bottom, double top, double znear, double zfar)
	{
		const double x = 2.0 / (right - left);
		const double y = 2.0 / (top - bottom);
		const double a = (right + left) / (right - left);
		const double b = (top + bottom) / (top - bottom);
		const double c = -2.0 / (zfar - znear);
		const double d = -(zfar + znear) / (zfar - znear);
		return mat4x4d(x, 0.0, 0.0, a, 0.0, y, 0.0, b, 0.0, 0.0, c, d, 0.0, 0.0, 0.0, 1.0);
	}
	
    inline mat4x4 setPerspective(float fovy, float aspect, float znear, float zfar)
    {
        const float tan = std::tanf(fovy * 3.141592653589f / 180.0f);
        const float x = 1.0f / (tan*aspect);
        const float y = 1.0f / (tan);
        const float c = -(zfar + znear) / (zfar - znear);
        const float d = -(2.0f * zfar * znear) / (zfar - znear);
        return mat4x4(x, 0.0f, 0.0f, 0.0f, 0.0f, y, 0.0f, 0.0f, 0.0f, 0.0f, c, d, 0.0f, 0.0f, -1.0f, 0.0f);
        // inverse is:
        //return mat4x4( tan*aspect, 0.0f,  0.0f,   0.0f, 0.0f,       tan,   0.0f,   0.0f, 0.0f,       0.0f,  0.0f,  -1.0f, 0.0f,       0.0f,  -(zfar-znear)/(2.0f*zfar*znear), (zfar+znear)/(2.0f*zfar*znear) );
    }
	inline mat4x4d setPerspective(double fovy, double aspect, double znear, double zfar)
	{
		const double tan = std::tan(fovy * 3.141592653589 / 180.0);
		const double x = 1.0 / (tan*aspect);
		const double y = 1.0 / (tan);
		const double c = -(zfar + znear) / (zfar - znear);
		const double d = -(2.0 * zfar * znear) / (zfar - znear);
		return mat4x4d(x, 0.0, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, 0.0, c, d, 0.0, 0.0, -1.0, 0.0);
		// inverse is:
		//return mat4x4d( tan*aspect, 0.0,  0.0,   0.0, 0.0,       tan,   0.0,   0.0, 0.0,       0.0,  0.0,  -1.0, 0.0,       0.0,  -(zfar-znear)/(2.0*zfar*znear), (zfar+znear)/(2.0*zfar*znear) );
	}


    inline mat4x4 setProjection(const vec4 & fov, float znear, float zfar)
    {
		const float x = 2.0f / (fov.w + fov.z);
		const float y = 2.0f / (fov.x + fov.y);
		const float a = (fov.w - fov.z) / (fov.w + fov.z);
		const float b = (fov.x - fov.y) / (fov.x + fov.y);
		const float c = -(zfar + znear) / (zfar - znear);
		const float d = -(2.0f*zfar*znear) / (zfar - znear);
        return mat4x4(x, 0.0f, a, 0.0f, 0.0f, y, b, 0.0f, 0.0f, 0.0f, c, d, 0.0f, 0.0f, -1.0f, 0.0f);
        // inverse is:
        //return mat4x4( 1.0/x, 0.0f,  0.0f,   a/x, 0.0f,  1.0/y, 0.0f,   b/x, 0.0f,  0.0f,  0.0f,   -1.0, 0.0f,  0.0f,  1.0f/d, c/d );
    }
	inline mat4x4d setProjection(const vec4d & fov, double znear, double zfar)
	{
		const double x = 2.0 / (fov.w + fov.z);
		const double y = 2.0 / (fov.x + fov.y);
		const double a = (fov.w - fov.z) / (fov.w + fov.z);
		const double b = (fov.x - fov.y) / (fov.x + fov.y);
		const double c = -(zfar + znear) / (zfar - znear);
		const double d = -(2.0*zfar*znear) / (zfar - znear);
		return mat4x4d(x, 0.0, a, 0.0, 0.0, y, b, 0.0, 0.0, 0.0, c, d, 0.0, 0.0, -1.0, 0.0);
		// inverse is:
		//return mat4x4d( 1.0/x, 0.0,  0.0,   a/x, 0.0,  1.0/y, 0.0,   b/x, 0.0,  0.0,  0.0,   -1.0, 0.0,  0.0,  1.0/d, c/d );
	}

	inline mat4x4d setFrustumMat(double left, double right, double bottom, double top, double znear, double zfar)
	{
		const double x = (2.0 * znear) / (right - left);
		const double y = (2.0 * znear) / (top - bottom);
		const double a = (right + left) / (right - left);
		const double b = (top + bottom) / (top - bottom);
		const double c = -(zfar + znear) / (zfar - znear);
		const double d = -(2.0 * zfar * znear) / (zfar - znear);
		return mat4x4d(x, 0.0, a, 0.0, 0.0, y, b, 0.0, 0.0, 0.0, c, d, 0.0, 0.0, -1.0, 0.0);
		// inverse is:
		//return mat4x4d( 1.0/x, 0.0,  0.0,   a/x, 0.0,  1.0/y, 0.0,   b/x, 0.0,  0.0,  0.0,   -1.0, 0.0,  0.0,  1.0/d, c/d );
	}

	inline mat4x4 setFrustumMat(float left, float right, float bottom, float top, float znear, float zfar)
	{
		const float x = (2.0f * znear) / (right - left);
		const float y = (2.0f * znear) / (top - bottom);
		const float a = (right + left) / (right - left);
		const float b = (top + bottom) / (top - bottom);
		const float c = -(zfar + znear) / (zfar - znear);
		const float d = -(2.0f * zfar * znear) / (zfar - znear);
		return mat4x4(x, 0.0f, a, 0.0f, 0.0f, y, b, 0.0f, 0.0f, 0.0f, c, d, 0.0f, 0.0f, -1.0f, 0.0f);
		// inverse is:
		//return mat4x4( 1.0/x, 0.0f,  0.0f,   a/x,
		//               0.0f,  1.0/y, 0.0f,   b/x,
		//               0.0f,  0.0f,  0.0f,   -1.0,
		//               0.0f,  0.0f,  1.0f/d, c/d );
	}
    inline mat4x4 setPerspectiveTiled(float fovy, float aspect, float znear, float zfar, const vec2 & off, const vec2 & wid)
    {
        const float ym = znear * std::tanf(fovy * 3.141592653589f / 180.0f);
		const float xm = ym * aspect;
        const float xmin = -xm + 2.0f*xm*off.x;
        const float ymin = -ym + 2.0f*ym*off.y;
        const float xmax = xmin + 2.0f*xm*wid.x;
        const float ymax = ymin + 2.0f*ym*wid.y;
        return setFrustumMat(xmin, xmax, ymin, ymax, znear, zfar);
    }
	inline mat4x4d setPerspectiveTiled(double fovy, double aspect, double znear, double zfar, const vec2 & off, const vec2 & wid)
	{
		const double ym = znear * std::tan(fovy * 3.141592653589 / 180.0);
		const double xm = ym * aspect;
		const double xmin = -xm + 2.0*xm*off.x;
		const double ymin = -ym + 2.0*ym*off.y;
		const double xmax = xmin + 2.0*xm*wid.x;
		const double ymax = ymin + 2.0*ym*wid.y;
		return setFrustumMat(xmin, xmax, ymin, ymax, znear, zfar);
	}



    //
    // faceid:
    //
    //        -----
    //        | 1 |
    //   ------------------
    //   | 0  | 2 | 4 | 5 |
    //   ------------------
    //        | 3 | 
    //        -----
    //
    inline mat4x4 setCubeFaceTiled(int faceid, float znear, float zfar, const vec2 & off, const vec2 & wid)
    {
        const float w = znear;
		const float xmin = -w + 2.0f*w*off.x;
		const float ymin = -w + 2.0f*w*off.y;
		const float xmax = xmin + 2.0f*w*wid.x;
        const float ymax = ymin + 2.0f*w*wid.y;
        mat4x4 m = setFrustumMat(xmin, xmax, ymin, ymax, znear, zfar);

        if (faceid == 0) m = m * mat4x4(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        if (faceid == 1) m = m * mat4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        if (faceid == 3) m = m * mat4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        if (faceid == 4) m = m * mat4x4(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        if (faceid == 5) m = m * mat4x4(-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

        return m;
    }
	inline mat4x4d setCubeFaceTiled(int faceid, double znear, double zfar, const vec2 & off, const vec2 & wid)
	{
		const double w = znear;
		const double xmin = -w + 2.0*w*off.x;
		const double ymin = -w + 2.0*w*off.y;
		const double xmax = xmin + 2.0*w*wid.x;
		const double ymax = ymin + 2.0*w*wid.y;
		mat4x4d m = setFrustumMat(xmin, xmax, ymin, ymax, znear, zfar);
		if (faceid == 0) m = m * mat4x4d(0.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		if (faceid == 1) m = m * mat4x4d(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		if (faceid == 3) m = m * mat4x4d(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		if (faceid == 4) m = m * mat4x4d(0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		if (faceid == 5) m = m * mat4x4d(-1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		return m;
	}




    inline mat4x4 setLookat(const vec3 & eye, const vec3 & tar, const vec3 & up)
    {
        mat4x4 mat;
        float im;

        const float dir[3] = { -tar[0] + eye[0], -tar[1] + eye[1], -tar[2] + eye[2] };

        // right vector
        mat[0] = dir[2] * up[1] - dir[1] * up[2];
        mat[1] = dir[0] * up[2] - dir[2] * up[0];
        mat[2] = dir[1] * up[0] - dir[0] * up[1];
        im = 1.0f / sqrtf(mat[0] * mat[0] + mat[1] * mat[1] + mat[2] * mat[2]);
        mat[0] *= im;
        mat[1] *= im;
        mat[2] *= im;
        // up vector
        mat[4] = mat[2] * dir[1] - mat[1] * dir[2];
        mat[5] = mat[0] * dir[2] - mat[2] * dir[0];
        mat[6] = mat[1] * dir[0] - mat[0] * dir[1];
        im = 1.0f / sqrtf(mat[4] * mat[4] + mat[5] * mat[5] + mat[6] * mat[6]);
        mat[4] *= im;
        mat[5] *= im;
        mat[6] *= im;
        // view vector
        mat[8] = dir[0];
        mat[9] = dir[1];
        mat[10] = dir[2];
        im = 1.0f / sqrtf(mat[8] * mat[8] + mat[9] * mat[9] + mat[10] * mat[10]);
        mat[8] *= im;
        mat[9] *= im;
        mat[10] *= im;

        mat[3] = -(mat[0] * eye[0] + mat[1] * eye[1] + mat[2] * eye[2]);
        mat[7] = -(mat[4] * eye[0] + mat[5] * eye[1] + mat[6] * eye[2]);
        mat[11] = -(mat[8] * eye[0] + mat[9] * eye[1] + mat[10] * eye[2]);

        mat[12] = 0.0f;
        mat[13] = 0.0f;
        mat[14] = 0.0f;
        mat[15] = 1.0f;

        return mat;
    }
	inline mat4x4d setLookat(const vec3d & eye, const vec3d & tar, const vec3d & up)
	{
		mat4x4d mat;

		double im;

		const double dir[3] = { -tar[0] + eye[0], -tar[1] + eye[1], -tar[2] + eye[2] };

		// right vector
		mat[0] = dir[2] * up[1] - dir[1] * up[2];
		mat[1] = dir[0] * up[2] - dir[2] * up[0];
		mat[2] = dir[1] * up[0] - dir[0] * up[1];
		im = 1.0 / std::sqrt(mat[0] * mat[0] + mat[1] * mat[1] + mat[2] * mat[2]);
		mat[0] *= im;
		mat[1] *= im;
		mat[2] *= im;
		// up vector
		mat[4] = mat[2] * dir[1] - mat[1] * dir[2];
		mat[5] = mat[0] * dir[2] - mat[2] * dir[0];
		mat[6] = mat[1] * dir[0] - mat[0] * dir[1];
		im = 1.0 / std::sqrt(mat[4] * mat[4] + mat[5] * mat[5] + mat[6] * mat[6]);
		mat[4] *= im;
		mat[5] *= im;
		mat[6] *= im;
		// view vector
		mat[8] = dir[0];
		mat[9] = dir[1];
		mat[10] = dir[2];
		im = 1.0 / std::sqrt(mat[8] * mat[8] + mat[9] * mat[9] + mat[10] * mat[10]);
		mat[8] *= im;
		mat[9] *= im;
		mat[10] *= im;

		mat[3] = -(mat[0] * eye[0] + mat[1] * eye[1] + mat[2] * eye[2]);
		mat[7] = -(mat[4] * eye[0] + mat[5] * eye[1] + mat[6] * eye[2]);
		mat[11] = -(mat[8] * eye[0] + mat[9] * eye[1] + mat[10] * eye[2]);

		mat[12] = 0.0;
		mat[13] = 0.0;
		mat[14] = 0.0;
		mat[15] = 1.0;

		return mat;
	}

	inline mat3x3 orthogonalize(const mat3x3 & mat)
	{
		vec3 iu = vec3(mat[0], mat[1], mat[2]);
		vec3 iv = vec3(mat[3], mat[4], mat[5]);
		vec3 iw = vec3(mat[6], mat[7], mat[8]);
		const float s = (length(iu) + length(iv) + length(iw)) / 3.0f;
		vec3 uu = iu;                                              uu = normalize(iu);
		vec3 vv = iv; vv -= dot(iv, uu)*uu;                        vv = normalize(vv);
		vec3 ww = iw; ww -= dot(iw, uu)*uu; ww -= dot(ww, vv)*vv;  ww = normalize(ww);
		uu *= s; vv *= s; ww *= s;
		return mat3x3(uu.x, uu.y, uu.z, vv.x, vv.y, vv.z, ww.x, ww.y, ww.z );
	}
	inline mat4x4 orthogonalize(const mat4x4 & mat )
	{
		vec3 iu = vec3(mat[0], mat[1], mat[2]);
		vec3 iv = vec3(mat[4], mat[5], mat[6]);
		vec3 iw = vec3(mat[8], mat[9], mat[10]);
		const float s = (length(iu) + length(iv) + length(iw)) / 3.0f;
		vec3 uu = iu;                                              uu = normalize(iu);
		vec3 vv = iv; vv -= dot(iv, uu)*uu;                        vv = normalize(vv);
		vec3 ww = iw; ww -= dot(iw, uu)*uu; ww -= dot(ww, vv)*vv;  ww = normalize(ww);
		uu *= s; vv *= s; ww *= s;
		return mat4x4(uu.x, uu.y, uu.z, mat[3], vv.x, vv.y, vv.z, mat[7], ww.x, ww.y, ww.z, mat[11], 0.0f, 0.0f, 0.0f, 1.0f);
	}
	inline mat4x4d orthogonalize(const mat4x4d & mat)
	{
		vec3d iu = vec3d(mat[0], mat[1], mat[2]);
		vec3d iv = vec3d(mat[4], mat[5], mat[6]);
		vec3d iw = vec3d(mat[8], mat[9], mat[10]);
		const double s = (length(iu) + length(iv) + length(iw)) / 3.0;
		vec3d uu = iu;                                              uu = normalize(iu);
		vec3d vv = iv; vv -= dot(iv, uu)*uu;                        vv = normalize(vv);
		vec3d ww = iw; ww -= dot(iw, uu)*uu; ww -= dot(ww, vv)*vv;  ww = normalize(ww);
		uu *= s; vv *= s; ww *= s;
		return mat4x4d(uu.x, uu.y, uu.z, mat[3], vv.x, vv.y, vv.z, mat[7], ww.x, ww.y, ww.z, mat[11], 0.0, 0.0, 0.0, 1.0);
	}



	


    inline bound3 compute(const vec3 * const p, const int num)
    {
        bound3 res = bound3(p[0].x, p[0].x, p[0].y, p[0].y, p[0].z, p[0].z);
        for (int k = 1; k<num; k++)
        {
            res.mMinX = (p[k].x<res.mMinX) ? p[k].x : res.mMinX;
            res.mMaxX = (p[k].x>res.mMaxX) ? p[k].x : res.mMaxX;
            res.mMinY = (p[k].y<res.mMinY) ? p[k].y : res.mMinY;
            res.mMaxY = (p[k].y>res.mMaxY) ? p[k].y : res.mMaxY;
            res.mMinZ = (p[k].z<res.mMinZ) ? p[k].z : res.mMinZ;
            res.mMaxZ = (p[k].z>res.mMaxZ) ? p[k].z : res.mMaxZ;
        }
        return res;
    }
	inline bound3d compute(const vec3d * const p, const int num)
	{
		bound3d res = bound3d(p[0].x, p[0].x, p[0].y, p[0].y, p[0].z, p[0].z);
		for (int k = 1; k<num; k++)
		{
			res.mMinX = (p[k].x<res.mMinX) ? p[k].x : res.mMinX;
			res.mMaxX = (p[k].x>res.mMaxX) ? p[k].x : res.mMaxX;
			res.mMinY = (p[k].y<res.mMinY) ? p[k].y : res.mMinY;
			res.mMaxY = (p[k].y>res.mMaxY) ? p[k].y : res.mMaxY;
			res.mMinZ = (p[k].z<res.mMinZ) ? p[k].z : res.mMinZ;
			res.mMaxZ = (p[k].z>res.mMaxZ) ? p[k].z : res.mMaxZ;
		}
		return res;
	}




    //--------------------------------------------------------------------------------
    // frustum3 (6 mPlanes[anes defining a convex volume)
    //--------------------------------------------------------------------------------

    struct frustum3
    {
        vec4   mPlanes[6];
        vec3   mPoints[8];
        mat4x4 mMatrix;

        frustum3() {}

        explicit frustum3(mat4x4 const & m)
        {
            mMatrix = m;

            mPlanes[0].x = mMatrix[12] - mMatrix[0];
            mPlanes[0].y = mMatrix[13] - mMatrix[1];
            mPlanes[0].z = mMatrix[14] - mMatrix[2];
            mPlanes[0].w = mMatrix[15] - mMatrix[3];
            mPlanes[1].x = mMatrix[12] + mMatrix[0];
            mPlanes[1].y = mMatrix[13] + mMatrix[1];
            mPlanes[1].z = mMatrix[14] + mMatrix[2];
            mPlanes[1].w = mMatrix[15] + mMatrix[3];
            mPlanes[2].x = mMatrix[12] + mMatrix[4];
            mPlanes[2].y = mMatrix[13] + mMatrix[5];
            mPlanes[2].z = mMatrix[14] + mMatrix[6];
            mPlanes[2].w = mMatrix[15] + mMatrix[7];
            mPlanes[3].x = mMatrix[12] - mMatrix[4];
            mPlanes[3].y = mMatrix[13] - mMatrix[5];
            mPlanes[3].z = mMatrix[14] - mMatrix[6];
            mPlanes[3].w = mMatrix[15] - mMatrix[7];
            mPlanes[4].x = mMatrix[12] - mMatrix[8];
            mPlanes[4].y = mMatrix[13] - mMatrix[9];
            mPlanes[4].z = mMatrix[14] - mMatrix[10];
            mPlanes[4].w = mMatrix[15] - mMatrix[11];
            mPlanes[5].x = mMatrix[12] + mMatrix[8];
            mPlanes[5].y = mMatrix[13] + mMatrix[9];
            mPlanes[5].z = mMatrix[14] + mMatrix[10];
            mPlanes[5].w = mMatrix[15] + mMatrix[11];

            for (int i = 0; i<6; i++)
            {
                mPlanes[i] *= inverseLength(mPlanes[i].xyz());
            }

            mPoints[0] = intersectPlanes(mPlanes[1], mPlanes[2], mPlanes[4]); // same as bellow, just that *zar/near
            mPoints[1] = intersectPlanes(mPlanes[0], mPlanes[2], mPlanes[4]);
            mPoints[2] = intersectPlanes(mPlanes[0], mPlanes[3], mPlanes[4]);
            mPoints[3] = intersectPlanes(mPlanes[1], mPlanes[3], mPlanes[4]);
            mPoints[4] = intersectPlanes(mPlanes[1], mPlanes[2], mPlanes[5]); //  left, bottom, near = -right, -top, near
            mPoints[5] = intersectPlanes(mPlanes[0], mPlanes[2], mPlanes[5]); // right, bottom, near =  right, -top, near
            mPoints[6] = intersectPlanes(mPlanes[0], mPlanes[3], mPlanes[5]); // right,    top, near
            mPoints[7] = intersectPlanes(mPlanes[1], mPlanes[3], mPlanes[5]); //  left,    top, near = -right, top, near
        }

		explicit frustum3(mat4x4 const & m, const vec4 *planes, const vec3 *points)
		{
			mMatrix = m;
			mPlanes[0] = planes[0];
			mPlanes[1] = planes[1];
			mPlanes[2] = planes[2];
			mPlanes[3] = planes[3];
			mPlanes[4] = planes[4];
			mPlanes[5] = planes[5];
			mPoints[0] = points[0];
			mPoints[1] = points[1];
			mPoints[2] = points[2];
			mPoints[3] = points[3];
			mPoints[4] = points[4];
			mPoints[5] = points[5];
			mPoints[6] = points[6];
			mPoints[7] = points[7];
		}
    };

    inline vec3 getNearPoint(frustum3 const &fru, const vec2 & uv)
    {
        return mix(mix(fru.mPoints[4], fru.mPoints[5], uv.x),
            mix(fru.mPoints[7], fru.mPoints[6], uv.x), uv.y);
    }

    inline frustum3 setFrustum(float left, float right, float bottom, float top, float znear, float zfar)
    {
        const float x = (2.0f * znear) / (right - left);
        const float y = (2.0f * znear) / (top - bottom);
        const float a = (right + left) / (right - left);
        const float b = (top + bottom) / (top - bottom);
        const float c = -(zfar + znear) / (zfar - znear);
        const float d = -(2.0f * zfar * znear) / (zfar - znear);

        return frustum3(mat4x4(x, 0.0f, a, 0.0f,
            0.0f, y, b, 0.0f,
            0.0f, 0.0f, c, d,
            0.0f, 0.0f, -1.0f, 0.0f));
    }

    inline frustum3 setFrustumPerspective(float fovy, float aspect, float znear, float zfar)
    {
        const float ymax = znear * tanf(fovy * 3.141592653589f / 180.0f);
        const float ymin = -ymax;
        const float xmin = ymin * aspect;
        const float xmax = ymax * aspect;

        return setFrustum(xmin, xmax, ymin, ymax, znear, zfar);
    }

    inline frustum3 setFrustumProjection(const vec4 & fov, float znear, float zfar)
    {
        const float ymax = znear * fov.x;
        const float ymin = -znear * fov.y;
        const float xmin = -znear * fov.z;
        const float xmax = znear * fov.w;

        return setFrustum(xmin, xmax, ymin, ymax, znear, zfar);
    }


    // 0: outside  1: inside/intersect
    inline int boxInFrustum(frustum3 const &fru, bound3 const & box)
    {
        float band = 0.0f;

        // check box outside/inside of frustum
        for (int i = 0; i<6; i++)
        {
            int out = 0;
            out += ((dot(fru.mPlanes[i], vec4(box.mMinX, box.mMinY, box.mMinZ, 1.0f)) < -band) ? 1 : 0);
            out += ((dot(fru.mPlanes[i], vec4(box.mMaxX, box.mMinY, box.mMinZ, 1.0f)) < -band) ? 1 : 0);
            out += ((dot(fru.mPlanes[i], vec4(box.mMinX, box.mMaxY, box.mMinZ, 1.0f)) < -band) ? 1 : 0);
            out += ((dot(fru.mPlanes[i], vec4(box.mMaxX, box.mMaxY, box.mMinZ, 1.0f)) < -band) ? 1 : 0);
            out += ((dot(fru.mPlanes[i], vec4(box.mMinX, box.mMinY, box.mMaxZ, 1.0f)) < -band) ? 1 : 0);
            out += ((dot(fru.mPlanes[i], vec4(box.mMaxX, box.mMinY, box.mMaxZ, 1.0f)) < -band) ? 1 : 0);
            out += ((dot(fru.mPlanes[i], vec4(box.mMinX, box.mMaxY, box.mMaxZ, 1.0f)) < -band) ? 1 : 0);
            out += ((dot(fru.mPlanes[i], vec4(box.mMaxX, box.mMaxY, box.mMaxZ, 1.0f)) < -band) ? 1 : 0);
            if (out == 8) return 0;
        }

        // check frustum outside/inside box
        int out;
        out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].x>(box.mMaxX + band)) ? 1 : 0); if (out == 8) return 0;
        out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].x<(box.mMinX - band)) ? 1 : 0); if (out == 8) return 0;
        out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].y>(box.mMaxY + band)) ? 1 : 0); if (out == 8) return 0;
        out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].y<(box.mMinY - band)) ? 1 : 0); if (out == 8) return 0;
        out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].z>(box.mMaxZ + band)) ? 1 : 0); if (out == 8) return 0;
        out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].z<(box.mMinZ - band)) ? 1 : 0); if (out == 8) return 0;

        return 1;
    }

    //===========================================================================================================

    // make a plane that goes through pointa a, b, c
    inline vec4d makePlane(vec3d const & a, vec3d const & b, vec3d const & c)
    {
        //    const vec3 n = normalize( cross( c-a, b-a ) );
        const vec3d n = normalize(cross(b - a, c - a));
        return vec4d(n, -dot(a, n));
    }

    inline vec3d intersectPlanes(vec4d const & p1, vec4d const & p2, vec4d const & p3)
    {
        const double den = dot(p1.xyz(), cross(p2.xyz(), p3.xyz()));

        if (den == 0.0)
            return vec3d(0.0);

        vec3d res = p1.w * cross(p2.xyz(), p3.xyz()) +
            p2.w * cross(p3.xyz(), p1.xyz()) +
            p3.w * cross(p1.xyz(), p2.xyz());

        return res * (-1.0 / den);
    }






	inline quatd fromRotation(const vec3d & axis, double angle)
	{
		const double si = std::sin(angle * 0.5);
		const double co = std::cos(angle * 0.5);
		return quatd(si * axis.x, si * axis.y, si * axis.z, co);
	}

    inline quatd fromMatrix( const mat3x3d & mat )
    {
		quatd q;
		double trace = mat[0] + mat[4] + mat[8];
		if (trace > 0)
		{
			double s = 0.5 / std::sqrt(trace + 1.0);
			q.x = (mat[7] - mat[5]) * s;
			q.y = (mat[2] - mat[6]) * s;
			q.z = (mat[3] - mat[1]) * s;
			q.w = 0.25 / s;
		}
		else
		{
			if (mat[0] > mat[4] && mat[0] > mat[8])
			{
				double s = 2.0 * std::sqrt(1.0 + mat[0] - mat[4] - mat[8]);
				q.x = 0.25 * s;
				q.y = (mat[1] + mat[3]) / s;
				q.z = (mat[2] + mat[6]) / s;
				q.w = (mat[7] - mat[5]) / s;
			}
			else if (mat[4] > mat[8])
			{
				double s = 2.0 * std::sqrt(1.0 + mat[4] - mat[0] - mat[8]);
				q.x = (mat[1] + mat[3]) / s;
				q.y = 0.25 * s;
				q.z = (mat[5] + mat[7]) / s;
				q.w = (mat[2] - mat[6]) / s;
			}
			else
			{
				double s = 2.0 * std::sqrt(1.0 + mat[8] - mat[0] - mat[4]);
				q.x = (mat[2] + mat[6]) / s;
				q.y = (mat[5] + mat[7]) / s;
				q.z = 0.25 * s;
				q.w = (mat[3] - mat[1]) / s;
			}
		}
		return q;
    }

	inline mat3x3d extractRotation3(const mat4x4d & m)
	{
		return mat3x3d(m.m[0], m.m[1], m.m[2], m.m[4], m.m[5], m.m[6], m.m[8], m.m[9], m.m[10]);
	}
	inline mat4x4d extractRotation(mat4x4d const & m)
	{
		return mat4x4d(m.m[0], m.m[4], m.m[8], 0.0, m.m[1], m.m[5], m.m[9], 0.0, m.m[2], m.m[6], m.m[10], 0.0, 0.0, 0.0, 0.0, 1.0);
	}
	inline vec3d extractTranslation(mat4x4d const & m)
	{
		return vec3d(m.m[3], m.m[7], m.m[11]);
	}

	inline vec3d extractScale(mat4x4d const & m)
	{
		const vec3d v1a = vec3d(1.0, 0.0, 0.0);
		const vec3d v2a = vec3d(0.0, 1.0, 0.0);
		const vec3d v3a = vec3d(0.0, 0.0, 1.0);
		const vec3d v1b = (m*vec4d(v1a, 0.0)).xyz();
		const vec3d v2b = (m*vec4d(v2a, 0.0)).xyz();
		const vec3d v3b = (m*vec4d(v3a, 0.0)).xyz();

		return vec3d(length(v1b), length(v2b), length(v3b));
	}

	inline double extractAverageScale(mat4x4d const & m)
	{
		return length((m* vec4d(0.57735026919, 0.57735026919, 0.57735026919, 0.0)).xyz());
	}


	inline trans3d fromMatrix(const mat4x4d & mat)
	{
		const vec3d  t = extractTranslation(mat);
		const double s = extractAverageScale(mat);
		const mat4x4d m2 = setScale4(1.0 / s) * mat;// *setTranslation(-t);
		return trans3d( fromMatrix(extractRotation3(m2)), s, t);
	}
	inline mat4x4d toMatrix(const trans3d & t)
	{
		//return mat4x4d(setRotation4(t.mRotation)*setScale4(t.mScale)*setTranslation(t.mTranslation));
		return mat4x4d(setTranslation(t.mTranslation)*setRotation4(t.mRotation)*setScale4(t.mScale)  );
	}

	inline quatd vectorsToQuaternion(const vec3d & a, const vec3d & b)
	{
		const double dotP = dot(a, b);
		if (dotP < -0.999999)
		{
			const vec3d xUnit = vec3d(1.0, 0.0, 0.0);
			const vec3d yUnit = vec3d(0.0, 1.0, 0.0);
			const double fPI = 3.14159265359;
			vec3d tmpVector = cross(xUnit, a);
			if (length(tmpVector) < 0.000001) tmpVector = cross(yUnit, a);
			tmpVector = normalize(tmpVector);
			return fromRotation(tmpVector, fPI);
		}
		else if (dotP > 0.999999)
		{
			return quatd::identity();
		}
		else
		{
			vec3d crossP = cross(a, b);

			vec4d output = vec4d(crossP, 1.0 + dotP);
			double l = length(output);
			if (l > 0.00000001)
				return quatd(output.x / l, output.y / l, output.z / l, output.w / l);
			else
				return quatd(0.0, 0.0, 0.0, 0.0);
		}
	}
	
	inline quatd slerpQuaternions(const quatd & a, const quatd & b, float t)
	{
		double cosom = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

		double bx = b.x, by = b.y, bz = b.z, bw = b.w;

		if (cosom < 0.0)
		{
			cosom = -cosom;
			bx = -bx;
			by = -by;
			bz = -bz;
			bw = -bw;
		}

		double scale0, scale1;
		if ((1.0 - cosom) > 0.000001)
		{
			// slerp
			double omega = std::acos(cosom);
			double sinom = std::sin(omega);
			scale0 = std::sin((1.0 - t) * omega) / sinom;
			scale1 = std::sin(t * omega) / sinom;
		}
		else
		{
			// lerp
			scale0 = 1.0 - t;
			scale1 = t;
		}
		return quatd(scale0*a.x + scale1 * bx, scale0 * a.y + scale1 * by, scale0 * a.z + scale1 * bz, scale0 * a.w + scale1 * bw);
	}

    inline mat4x4d invertFast(mat4x4d const & m)
    {
        mat4x4d inv = mat4x4d( 
			 m.m[5] * m.m[10] * m.m[15] - m.m[5] * m.m[11] * m.m[14] - m.m[9] * m.m[6] * m.m[15] + m.m[9] * m.m[7] * m.m[14] + m.m[13] * m.m[6] * m.m[11] - m.m[13] * m.m[7] * m.m[10],
            -m.m[1] * m.m[10] * m.m[15] + m.m[1] * m.m[11] * m.m[14] + m.m[9] * m.m[2] * m.m[15] - m.m[9] * m.m[3] * m.m[14] - m.m[13] * m.m[2] * m.m[11] + m.m[13] * m.m[3] * m.m[10],
             m.m[1] * m.m[ 6] * m.m[15] - m.m[1] * m.m[ 7] * m.m[14] - m.m[5] * m.m[2] * m.m[15] + m.m[5] * m.m[3] * m.m[14] + m.m[13] * m.m[2] * m.m[ 7] - m.m[13] * m.m[3] * m.m[ 6],
            -m.m[1] * m.m[ 6] * m.m[11] + m.m[1] * m.m[ 7] * m.m[10] + m.m[5] * m.m[2] * m.m[11] - m.m[5] * m.m[3] * m.m[10] - m.m[ 9] * m.m[2] * m.m[ 7] + m.m[ 9] * m.m[3] * m.m[ 6],
            -m.m[4] * m.m[10] * m.m[15] + m.m[4] * m.m[11] * m.m[14] + m.m[8] * m.m[6] * m.m[15] - m.m[8] * m.m[7] * m.m[14] - m.m[12] * m.m[6] * m.m[11] + m.m[12] * m.m[7] * m.m[10],
             m.m[0] * m.m[10] * m.m[15] - m.m[0] * m.m[11] * m.m[14] - m.m[8] * m.m[2] * m.m[15] + m.m[8] * m.m[3] * m.m[14] + m.m[12] * m.m[2] * m.m[11] - m.m[12] * m.m[3] * m.m[10],
            -m.m[0] * m.m[ 6] * m.m[15] + m.m[0] * m.m[ 7] * m.m[14] + m.m[4] * m.m[2] * m.m[15] - m.m[4] * m.m[3] * m.m[14] - m.m[12] * m.m[2] * m.m[ 7] + m.m[12] * m.m[3] * m.m[ 6],
             m.m[0] * m.m[ 6] * m.m[11] - m.m[0] * m.m[ 7] * m.m[10] - m.m[4] * m.m[2] * m.m[11] + m.m[4] * m.m[3] * m.m[10] + m.m[ 8] * m.m[2] * m.m[ 7] - m.m[ 8] * m.m[3] * m.m[ 6],
             m.m[4] * m.m[ 9] * m.m[15] - m.m[4] * m.m[11] * m.m[13] - m.m[8] * m.m[5] * m.m[15] + m.m[8] * m.m[7] * m.m[13] + m.m[12] * m.m[5] * m.m[11] - m.m[12] * m.m[7] * m.m[ 9],
            -m.m[0] * m.m[ 9] * m.m[15] + m.m[0] * m.m[11] * m.m[13] + m.m[8] * m.m[1] * m.m[15] - m.m[8] * m.m[3] * m.m[13] - m.m[12] * m.m[1] * m.m[11] + m.m[12] * m.m[3] * m.m[ 9],
             m.m[0] * m.m[ 5] * m.m[15] - m.m[0] * m.m[ 7] * m.m[13] - m.m[4] * m.m[1] * m.m[15] + m.m[4] * m.m[3] * m.m[13] + m.m[12] * m.m[1] * m.m[ 7] - m.m[12] * m.m[3] * m.m[ 5],
            -m.m[0] * m.m[ 5] * m.m[11] + m.m[0] * m.m[ 7] * m.m[ 9] + m.m[4] * m.m[1] * m.m[11] - m.m[4] * m.m[3] * m.m[ 9] - m.m[ 8] * m.m[1] * m.m[ 7] + m.m[ 8] * m.m[3] * m.m[ 5],
            -m.m[4] * m.m[ 9] * m.m[14] + m.m[4] * m.m[10] * m.m[13] + m.m[8] * m.m[5] * m.m[14] - m.m[8] * m.m[6] * m.m[13] - m.m[12] * m.m[5] * m.m[10] + m.m[12] * m.m[6] * m.m[ 9],
             m.m[0] * m.m[ 9] * m.m[14] - m.m[0] * m.m[10] * m.m[13] - m.m[8] * m.m[1] * m.m[14] + m.m[8] * m.m[2] * m.m[13] + m.m[12] * m.m[1] * m.m[10] - m.m[12] * m.m[2] * m.m[ 9],
            -m.m[0] * m.m[ 5] * m.m[14] + m.m[0] * m.m[ 6] * m.m[13] + m.m[4] * m.m[1] * m.m[14] - m.m[4] * m.m[2] * m.m[13] - m.m[12] * m.m[1] * m.m[ 6] + m.m[12] * m.m[2] * m.m[ 5],
             m.m[0] * m.m[ 5] * m.m[10] - m.m[0] * m.m[ 6] * m.m[ 9] - m.m[4] * m.m[1] * m.m[10] + m.m[4] * m.m[2] * m.m[ 9] + m.m[ 8] * m.m[1] * m.m[ 6] - m.m[ 8] * m.m[2] * m.m[ 5]);

        double det = m.m[0] * inv.m[0] + m.m[1] * inv.m[4] + m.m[2] * inv.m[8] + m.m[3] * inv.m[12];
        det = 1.0 / det;
        for (int i = 0; i < 16; i++) inv.m[i] = inv.m[i] * det;

        return inv;
    }

    inline mat4x4d invert(mat4x4d const & src, int *status = 0)
    {
        int   i, j, k, swap;
        double t, temp[4][4];


        for (i = 0; i<4; i++)
            for (j = 0; j<4; j++)
                temp[i][j] = src[i * 4 + j];

        double inv[16];
        for (i = 0; i<16; i++) inv[i] = 0.0;
        inv[0] = 1.0;
        inv[5] = 1.0;
        inv[10] = 1.0;
        inv[15] = 1.0;

        for (i = 0; i<4; i++)
        {
            // Look for largest element in column
            swap = i;
            for (j = i + 1; j < 4; j++)
                if (fabs(temp[j][i]) > fabs(temp[i][i]))
                    swap = j;

            if (swap != i)
            {
                // Swap rows.
                for (k = 0; k<4; k++)
                {
                    t = temp[i][k];
                    temp[i][k] = temp[swap][k];
                    temp[swap][k] = t;

                    t = inv[i * 4 + k];
                    inv[i * 4 + k] = inv[swap * 4 + k];
                    inv[swap * 4 + k] = t;
                }
            }

            // pivot==0 -> singular matrix!
            if (temp[i][i] == 0)
            {
                if (status) status[0] = 0;
                return mat4x4d(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
            }

            t = temp[i][i];
            t = 1.0 / t;
            for (k = 0; k<4; k++)
            {
                temp[i][k] *= t;
                inv[i * 4 + k] *= t;
            }

            for (j = 0; j<4; j++)
            {
                if (j != i)
                {
                    t = temp[j][i];
                    for (k = 0; k<4; k++)
                    {
                        temp[j][k] -= temp[i][k] * t;
                        inv[j * 4 + k] -= inv[i * 4 + k] * t;
                    }
                }
            }
        }

        if (status) status[0] = 1;

        return mat4x4d(inv);

    }

    inline vec3d extractRotationEuler(const mat4x4d & m)
    {
        if (m.m[0] == 1.0)
        {
			return vec3d(std::atan2(m.m[2], m.m[11]), 0.0, 0.0);
        }
        else if (m.m[0] == -1.0)
        {
			return vec3d(std::atan2(m.m[2], m.m[11]), 0.0, 0.0);
        }
		return vec3d( std::atan2(-m.m[9], m.m[10]), std::atan2(m.m[8], std::sqrt(m.m[9] * m.m[9] + m.m[10] * m.m[10])), std::atan2(m.m[4], m.m[0]));
    }

    inline vec2d getNearFar_FromPerspectiveMatrix(const mat4x4d & m)
    {
        const double c = m.m[10];
        const double d = m.m[11];
        return vec2d(d / (c - 1.0), d / (c + 1.0));
    }
    // Zeye = a / (Zbuffer[0..1] + b);
    inline vec2d getZBufferToZetaEye_FromPerspectiveMatrix(const mat4x4d & m)
    {
        return vec2d(m.m[11] / 2.0, (m.m[10] - 1.0) / 2.0);
    }
    // Zeye = a / (Zclip[-1..1] + b);
    inline vec2d getZClipToZetaEye_FromPerspectiveMatrix(const mat4x4d & m)
    {
        return vec2d(0.0, 0.0);//vec2( -m.m[11], m.m[10] );
    }




	//--------------------------------------------------------------------------------
	// frustum3d (6 mPlanes[anes defining a convex volume)
	//--------------------------------------------------------------------------------

	struct frustum3d
	{
		vec4d   mPlanes[6];
		vec3d   mPoints[8];
		mat4x4d mMatrix;

		frustum3d() {}

		explicit frustum3d(mat4x4d const & m)
		{
			mMatrix = m;

			mPlanes[0].x = mMatrix[12] - mMatrix[0];
			mPlanes[0].y = mMatrix[13] - mMatrix[1];
			mPlanes[0].z = mMatrix[14] - mMatrix[2];
			mPlanes[0].w = mMatrix[15] - mMatrix[3];
			mPlanes[1].x = mMatrix[12] + mMatrix[0];
			mPlanes[1].y = mMatrix[13] + mMatrix[1];
			mPlanes[1].z = mMatrix[14] + mMatrix[2];
			mPlanes[1].w = mMatrix[15] + mMatrix[3];
			mPlanes[2].x = mMatrix[12] + mMatrix[4];
			mPlanes[2].y = mMatrix[13] + mMatrix[5];
			mPlanes[2].z = mMatrix[14] + mMatrix[6];
			mPlanes[2].w = mMatrix[15] + mMatrix[7];
			mPlanes[3].x = mMatrix[12] - mMatrix[4];
			mPlanes[3].y = mMatrix[13] - mMatrix[5];
			mPlanes[3].z = mMatrix[14] - mMatrix[6];
			mPlanes[3].w = mMatrix[15] - mMatrix[7];
			mPlanes[4].x = mMatrix[12] - mMatrix[8];
			mPlanes[4].y = mMatrix[13] - mMatrix[9];
			mPlanes[4].z = mMatrix[14] - mMatrix[10];
			mPlanes[4].w = mMatrix[15] - mMatrix[11];
			mPlanes[5].x = mMatrix[12] + mMatrix[8];
			mPlanes[5].y = mMatrix[13] + mMatrix[9];
			mPlanes[5].z = mMatrix[14] + mMatrix[10];
			mPlanes[5].w = mMatrix[15] + mMatrix[11];

			for (int i = 0; i<6; i++)
			{
				mPlanes[i] *= inverseLength(mPlanes[i].xyz());
			}

			mPoints[0] = intersectPlanes(mPlanes[1], mPlanes[2], mPlanes[4]); // same as bellow, just that *zar/near
			mPoints[1] = intersectPlanes(mPlanes[0], mPlanes[2], mPlanes[4]);
			mPoints[2] = intersectPlanes(mPlanes[0], mPlanes[3], mPlanes[4]);
			mPoints[3] = intersectPlanes(mPlanes[1], mPlanes[3], mPlanes[4]);
			mPoints[4] = intersectPlanes(mPlanes[1], mPlanes[2], mPlanes[5]); //  left, bottom, near = -right, -top, near
			mPoints[5] = intersectPlanes(mPlanes[0], mPlanes[2], mPlanes[5]); // right, bottom, near =  right, -top, near
			mPoints[6] = intersectPlanes(mPlanes[0], mPlanes[3], mPlanes[5]); // right,    top, near
			mPoints[7] = intersectPlanes(mPlanes[1], mPlanes[3], mPlanes[5]); //  left,    top, near = -right, top, near
		}

		explicit frustum3d(mat4x4d const & m, const vec4d *planes, const vec3d *points)
		{
			mMatrix = m;
			mPlanes[0] = planes[0];
			mPlanes[1] = planes[1];
			mPlanes[2] = planes[2];
			mPlanes[3] = planes[3];
			mPlanes[4] = planes[4];
			mPlanes[5] = planes[5];
			mPoints[0] = points[0];
			mPoints[1] = points[1];
			mPoints[2] = points[2];
			mPoints[3] = points[3];
			mPoints[4] = points[4];
			mPoints[5] = points[5];
			mPoints[6] = points[6];
			mPoints[7] = points[7];
		}

	};

	inline vec3d getNearPoint(frustum3d const &fru, const vec2d & uv)
	{
		return mix(mix(fru.mPoints[4], fru.mPoints[5], uv.x), mix(fru.mPoints[7], fru.mPoints[6], uv.x), uv.y);
	}

	inline frustum3d setFrustum(double left, double right, double bottom, double top, double znear, double zfar)
	{
		const double x = (2.0 * znear) / (right - left);
		const double y = (2.0 * znear) / (top - bottom);
		const double a = (right + left) / (right - left);
		const double b = (top + bottom) / (top - bottom);
		const double c = -(zfar + znear) / (zfar - znear);
		const double d = -(2.0 * zfar * znear) / (zfar - znear);
		return frustum3d(mat4x4d(x, 0.0f, a, 0.0f, 0.0f, y, b, 0.0f, 0.0f, 0.0f, c, d, 0.0f, 0.0f, -1.0f, 0.0f));
	}

	inline frustum3d setFrustumPerspective(double fovy, double aspect, double znear, double zfar)
	{
		const double ymax = znear * std::tan(fovy * 3.14159265358f / 180.0);
		const double ymin = -ymax;
		const double xmin = ymin * aspect;
		const double xmax = ymax * aspect;
		return setFrustum(xmin, xmax, ymin, ymax, znear, zfar);
	}

	inline frustum3d setFrustumProjection(const vec4d & fov, double znear, double zfar)
	{
		const double ymax = znear * fov.x;
		const double ymin = -znear * fov.y;
		const double xmin = -znear * fov.z;
		const double xmax = znear * fov.w;

		return setFrustum(xmin, xmax, ymin, ymax, znear, zfar);
	}

	// 0: outside  1: inside/intersect
	inline int boxInFrustum(frustum3d const &fru, bound3d const & box)
	{
		double band = 0.0;

		// check box outside/inside of frustum
		for (int i = 0; i<6; i++)
		{
			int out = 0;
			out += ((dot(fru.mPlanes[i], vec4d(box.mMinX, box.mMinY, box.mMinZ, 1.0)) < -band) ? 1 : 0);
			out += ((dot(fru.mPlanes[i], vec4d(box.mMaxX, box.mMinY, box.mMinZ, 1.0)) < -band) ? 1 : 0);
			out += ((dot(fru.mPlanes[i], vec4d(box.mMinX, box.mMaxY, box.mMinZ, 1.0)) < -band) ? 1 : 0);
			out += ((dot(fru.mPlanes[i], vec4d(box.mMaxX, box.mMaxY, box.mMinZ, 1.0)) < -band) ? 1 : 0);
			out += ((dot(fru.mPlanes[i], vec4d(box.mMinX, box.mMinY, box.mMaxZ, 1.0)) < -band) ? 1 : 0);
			out += ((dot(fru.mPlanes[i], vec4d(box.mMaxX, box.mMinY, box.mMaxZ, 1.0)) < -band) ? 1 : 0);
			out += ((dot(fru.mPlanes[i], vec4d(box.mMinX, box.mMaxY, box.mMaxZ, 1.0)) < -band) ? 1 : 0);
			out += ((dot(fru.mPlanes[i], vec4d(box.mMaxX, box.mMaxY, box.mMaxZ, 1.0)) < -band) ? 1 : 0);
			if (out == 8) return 0;
		}

		// check frustum outside/inside box
		int out;
		out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].x>(box.mMaxX + band)) ? 1 : 0); if (out == 8) return 0;
		out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].x<(box.mMinX - band)) ? 1 : 0); if (out == 8) return 0;
		out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].y>(box.mMaxY + band)) ? 1 : 0); if (out == 8) return 0;
		out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].y<(box.mMinY - band)) ? 1 : 0); if (out == 8) return 0;
		out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].z>(box.mMaxZ + band)) ? 1 : 0); if (out == 8) return 0;
		out = 0; for (int i = 0; i<8; i++) out += ((fru.mPoints[i].z<(box.mMinZ - band)) ? 1 : 0); if (out == 8) return 0;

		return 1;
	}


	//=========================================================================================================================================
	// You should rarely use these. If you do, make sure you are doing it for a good reason, not just because you need to make the code compile
	//=========================================================================================================================================

	inline vec2     i2f( const ivec2 & v ) { return vec2(float(v.x), float(v.y)); }
	inline vec3     i2f( const ivec3 & v ) { return vec3(float(v.x), float(v.y), float(v.z)); }
	inline vec4     i2f( const ivec4 & v ) { return vec4(float(v.x), float(v.y), float(v.z), float(v.w)); }

	inline ivec2    f2i( const vec2 & v ) { return ivec2(int(v.x), int(v.y)); }
	inline ivec3    f2i( const vec3 & v ) { return ivec3(int(v.x), int(v.y), int(v.z)); }
	inline ivec4    f2i( const vec4 & v ) { return ivec4(int(v.x), int(v.y), int(v.z), int(v.w)); }

    inline vec2d    f2d( const vec2 & v ) { return vec2d( double(v.x), double(v.y) ); }
    inline vec3d    f2d( const vec3 & v ) { return vec3d( double(v.x), double(v.y), double(v.z) ); }
    inline vec4d    f2d( const vec4 & v ) { return vec4d( double(v.x), double(v.y), double(v.z), double(v.w) ); }
    inline mat4x4d  f2d( const mat4x4 & m ) { return mat4x4d( double(m[ 0]), double(m[ 1]), double(m[ 2]), double(m[ 3]), double(m[ 4]), double(m[ 5]), double(m[ 6]), double(m[ 7]), double(m[ 8]), double(m[ 9]), double(m[10]), double(m[11]), double(m[12]), double(m[13]), double(m[14]), double(m[15]) ); }
	inline bound2d  f2d( const bound2 & b ) { return bound2d(double(b.mMinX), double(b.mMaxX), double(b.mMinY), double(b.mMaxY)); }
	inline bound3d  f2d( const bound3 & b ) { return bound3d(double(b.mMinX), double(b.mMaxX), double(b.mMinY), double(b.mMaxY), double(b.mMinZ), double(b.mMaxZ)); }

	inline vec2     d2f( const vec2d & v ) { return vec2( float(v.x), float(v.y) ); }
    inline vec3     d2f( const vec3d & v ) { return vec3( float(v.x), float(v.y), float(v.z) ); }
    inline vec4     d2f( const vec4d & v ) { return vec4( float(v.x), float(v.y), float(v.z), float(v.w) ); }
    inline mat4x4   d2f( const mat4x4d & m ) { return mat4x4( float(m[ 0]), float(m[ 1]), float(m[ 2]), float(m[ 3]), float(m[ 4]), float(m[ 5]), float(m[ 6]), float(m[ 7]), float(m[ 8]), float(m[ 9]), float(m[10]), float(m[11]), float(m[12]), float(m[13]), float(m[14]), float(m[15]) ); }
	inline bound2   d2f( const bound2d & b ) { return bound2(float(b.mMinX), float(b.mMaxX), float(b.mMinY), float(b.mMaxY)); }
	inline bound3   d2f( const bound3d & b ) { return bound3(float(b.mMinX), float(b.mMaxX), float(b.mMinY), float(b.mMaxY), float(b.mMinZ), float(b.mMaxZ)); }
	inline frustum3 d2f( const frustum3d & f) { vec4 planes[6] = { d2f(f.mPlanes[0]), d2f(f.mPlanes[1]),d2f(f.mPlanes[2]),d2f(f.mPlanes[3]),d2f(f.mPlanes[4]),d2f(f.mPlanes[5]) }; vec3 points[8] = { d2f(f.mPoints[0]), d2f(f.mPoints[1]), d2f(f.mPoints[2]), d2f(f.mPoints[3]), d2f(f.mPoints[4]), d2f(f.mPoints[5]), d2f(f.mPoints[6]), d2f(f.mPoints[7]) }; return frustum3( d2f(f.mMatrix), planes, points ); }

}
