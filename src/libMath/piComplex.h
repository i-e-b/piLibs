#pragma once

#include <cmath>

namespace piLibs {


template <typename  TYPE>
struct complex
{
    TYPE x, y;

	complex() {}

	explicit complex( TYPE a )
    {
        x = a;
        y = TYPE(0.0);
    }

	explicit complex( TYPE a, TYPE b )
    {
        x = a;
        y = b;
    }

	explicit complex( TYPE const * const v )
    {
        x = v[0];
        y = v[1];
    }

	complex & operator =( complex  const & v ) { x = v.x;  y = v.y;  return *this; }
	complex & operator+=( TYPE     const & s ) { x += s;             return *this; }
	complex & operator+=( complex  const & v ) { x += v.x; y += v.y; return *this; }
	complex & operator-=( TYPE     const & s ) { x -= s;             return *this; }
	complex & operator-=( complex  const & v ) { x -= v.x; y -= v.y; return *this; }

	complex & operator*=( TYPE     const & s ) { x *= s;   y *= s;   return *this; }
	complex & operator*=( complex  const & b ) { TYPE ax = x; TYPE ay = y; x = ax*b.x - ay*b.y; y = ax*b.y + ay*b.x; return *this; }
	complex & operator/=( TYPE     const & s ) { x /= s;   y /= s;   return *this; }
	complex & operator/=( complex  const & b ) {  TYPE ax = x; TYPE ay = y; TYPE d = TYPE(1.0)/(b.x*b.x + b.y*b.y); x = (ax*b.x + ay*b.y)*d; y = (-ax*b.y + ay*b.x)*d; return *this; }
};

template <typename TYPE>
inline complex<TYPE> operator+( complex<TYPE>  const & v, TYPE const & s ) { return complex<TYPE>( v.x + s, v.y ); }
template <typename  TYPE>
inline complex<TYPE> operator+( TYPE const & s, complex<TYPE> const & v ) { return complex<TYPE>( s + v.x, v.y ); }
template <typename  TYPE>
inline complex<TYPE> operator+( complex<TYPE> const & a, complex<TYPE>  const & b ) { return complex<TYPE>( a.x + b.x, a.y + b.y ); }
template <typename  TYPE>
inline complex<TYPE> operator-( complex<TYPE> const & v, TYPE const & s ) { return complex<TYPE>( v.x - s, v.y ); }
template <typename  TYPE>
inline complex<TYPE> operator-( TYPE const & s, complex<TYPE>  const & v ) { return complex<TYPE>( s - v.x, v.y ); }
template <typename  TYPE>
inline complex<TYPE> operator-( complex<TYPE> const & a, complex<TYPE> const & b ) { return complex<TYPE>( a.x - b.x, a.y - b.y ); }
template <typename  TYPE>
inline complex<TYPE> operator*( complex<TYPE> const & v, TYPE const & s ) { return complex<TYPE>( v.x * s, v.y * s ); }
template <typename  TYPE>
inline complex<TYPE> operator*( TYPE const & s, complex<TYPE> const & v ) { return complex<TYPE>( s * v.x, s * v.y ); }
template <typename  TYPE>
inline complex<TYPE> operator*( complex<TYPE> const & a, complex<TYPE> const & b ) { return complex<TYPE>( a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x ); }
template <typename  TYPE>
inline complex<TYPE> operator/( complex<TYPE> const & v, TYPE const & s ) { return complex<TYPE>( v.x / s, v.y / s ); }
template <typename  TYPE>
inline complex<TYPE> operator/( TYPE const & s, complex<TYPE> const & b ) { TYPE d = TYPE(1.0)/(b.x*b.x + b.y*b.y); return complex<TYPE>( (s*b.x)*d, (-s*b.y)*d ); }
template <typename  TYPE>
inline complex<TYPE> operator/( complex<TYPE> const & a, complex<TYPE> const & b ) { TYPE d = TYPE(1.0)/(b.x*b.x + b.y*b.y); return complex<TYPE>( (a.x*b.x + a.y*b.y)*d, (-a.x*b.y + a.y*b.x)*d ); }


template <typename  TYPE>
inline complex<TYPE> conjugate( const complex<TYPE> & z )
{
    return complex<TYPE>(z.x,-z.y);
}

template <typename  TYPE>
inline complex<TYPE> squared( const complex<TYPE> & z )
{
    return complex<TYPE>( z.x*z.x - z.y*z.y, 2.0f*z.x*z.y );
}

template <typename  TYPE>
inline complex<TYPE> cubed( const complex<TYPE> & z )
{
    const TYPE a = z.x*z.x - z.y*z.y;
    const TYPE b = 2.0f*z.x*z.y;
    return complex<TYPE>( a*z.x - b*z.y, a*z.y + b*z.x );
}

template <typename  TYPE>
inline TYPE modulo2( complex<TYPE> const & z )
{
    return z.x*z.x + z.y*z.y;
}


//-------------

template <typename  TYPE>
inline complex<TYPE> floor( complex<TYPE> const & v )
{
    return complex<TYPE>( std::floor(v.x), std::floor(v.y) );
}


template <typename  TYPE>
inline complex<TYPE> abs( complex<TYPE> const & v )
{
    return complex<TYPE>( std::fabs(v.x), std::fabs(v.y) );
}

template <typename  TYPE>
inline TYPE modulo( complex<TYPE> const & z )
{
    return std::sqrt( z.x*z.x + z.y*z.y );
}

template <typename  TYPE>
inline complex<TYPE> sqrt( const complex<TYPE> & z )
{
    complex<TYPE> res;

    if( z.x==0.0f )
    {
        res.x = std::sqrt( std::fabs(z.y)*.5f );
        if( z.x>0.0f )
            res.y = z.y*0.5f/res.x;
        else
            res.y = 0.0f;
    }
    else if( z.x>0.0f )
    {
        const TYPE m = std::sqrt(z.x*z.x + z.y*z.y);
        res.x = std::sqrt( (res.x+m)*.5f );
        res.y = z.y*.5f/res.x;
    }
    else
    {
        const TYPE m = std::sqrt(z.x*z.x + z.y*z.y);
        res.y = std::sqrt( (-z.x+m)*.5f );
        if( z.y<0.0f )
            res.y = -res.y;
        res.x = z.y*0.5f/res.y;
    }
    return res;
}



template <typename  TYPE>
inline void toPolar( const complex<TYPE> & z, TYPE *r, TYPE *a )
{
    *a = std::atan2( z.y, z.x );
    *r = std::sqrt( z.x*z.x + z.y*z.y );
}

template <typename  TYPE>
inline TYPE arg( const complex<TYPE> & z )
{
    return std::atan2( z.y, z.x );
}

template <typename  TYPE>
inline complex<TYPE> ipower( const complex<TYPE> & z, int power )
{
         if( power==0 ) return complex<TYPE>(1.0f,0.0f);
    else if( power==1 ) return z;
    else if( power==2 ) return squared(z);
    else if( power==3 ) return cubed(z);
    else if( power==4 ) return squared(squared(z));
    else if( power==6 ) return squared(cubed(z));
    else if( power==8 ) return squared(squared(squared(z)));
    else if( power==9 ) return cubed(cubed(z));
    else if( power==27 ) return cubed(cubed(cubed(z)));

    complex<TYPE> res = z;
    for( int i=1; i<power; i++ ) res = res * z;
    return res;
}

template <typename  TYPE>
inline complex<TYPE> log( const complex<TYPE> & z )
{
    return complex<TYPE>( 0.5f*std::log(modulo2(z)), arg( z ) );
}
template <typename  TYPE>
__inline complex<TYPE> exp( const complex<TYPE> & z )
{
    const TYPE mo = std::exp( z.x );
    return complex<TYPE>( mo*std::cos( z.y ), mo*std::sin( z.y ) );
}
template <typename  TYPE>
__inline complex<TYPE> expj( const complex<TYPE> z )
{
    const TYPE mo = std::exp(-z.y);
	return complex<TYPE>( mo*std::cos(z.x), mo*std::sin(z.x) );
}

template <typename  TYPE>
__inline complex<TYPE> sin( const complex<TYPE> & z )
{
    return complex<TYPE>( std::sin(z.x)*std::cosh(z.y), std::cos(z.x)*std::sinh(z.y) );
}

template <typename  TYPE>
__inline complex<TYPE> cos( const complex<TYPE> & z )
{
 //   return complex<TYPE>( std::cos(z.x)*std::cosh(z.y), -std::sin(z.x)*std::sinh(z.y) );
    float pe = std::exp(  z.y );
    float ne = std::exp( -z.y );
	return complex<TYPE>( 0.5*std::cos( z.x )*(ne+pe),  
                          0.5*std::sin( z.x )*(ne-pe) );


}

template <typename  TYPE>
__inline complex<TYPE> mulj( const complex<TYPE> & z )
{
    return complex<TYPE>( -z.y, z.x );
}

typedef complex<float> complexf;
typedef complex<double> complexd;

} // namespace piLibs