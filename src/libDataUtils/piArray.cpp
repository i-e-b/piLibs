#include <malloc.h>
#include <string.h>
#include "piArray.h"
#include "../libSystem/piTypes.h"

namespace piLibs {

piArray::piArray()
{
    mBuffer = nullptr;
    mMax = 0;
    mNum = 0;
    mObjectsize = 0;
}

piArray::~piArray()
{
}

bool piArray::IsInitialized(void) const
{
    return (mObjectsize>0);
}

int piArray::Init(  unsigned int max, unsigned int objectsize, bool doZero )
{
	mObjectsize = objectsize;
    mMax = max;
    mNum = 0;
	mDoZero = doZero;
    mBuffer = (unsigned char*)malloc( max*objectsize );

    if( !mBuffer )
        return( 0 );

	if(mDoZero )
		memset( mBuffer, 0, max*objectsize );

    return( 1 );
}

void piArray::End(void)
{
    if( mBuffer ) free( mBuffer );
    mBuffer = 0;
	mMax = 0;
	mNum = 0;
	mObjectsize = 0;
}

void piArray::Reset(void)
{
	if (mDoZero)
		memset( mBuffer, 0, mMax*mObjectsize );
    mNum = 0;
}

unsigned int piArray::GetLength(void) const
{
    return( mNum );
}

unsigned int piArray::GetMaxLength(void) const
{
    return mMax;
}

void *piArray::GetAddress(const  unsigned int n) const
{
	return( (void*)(mBuffer+n*mObjectsize) );
}

void  *piArray::Alloc(  unsigned int num, bool doexpand )
{
    if( (mNum+num)>mMax )
	{
		if( doexpand==false )
			return nullptr;

        long newmax = 4*mMax/3;
        if( newmax<4 ) newmax = 4;
        mBuffer = (unsigned char*)realloc( mBuffer, newmax*mObjectsize );
        if( !mBuffer )
            return nullptr;
        mMax = newmax;
		if (mDoZero)
			memset(mBuffer + mNum*mObjectsize, 0, (mMax - mNum)*mObjectsize);
	}

    unsigned char *ptr = mBuffer + mNum*mObjectsize;

    mNum += num;

    return( ptr );
}



void *piArray::Append(  const void *obj, bool doexpand )
{
    if( mNum>=mMax )
    {
		if( !doexpand )
			return nullptr;

        long newmax = 4*mMax/3;
        if( newmax<4 ) newmax = 4;
        mBuffer = (unsigned char*)realloc( mBuffer, newmax*mObjectsize );
        if( !mBuffer )
            return nullptr;
        mMax = newmax;
		if (mDoZero)
			memset(mBuffer + mNum*mObjectsize, 0, (mMax - mNum)*mObjectsize);
	}
    unsigned char *ptr = mBuffer + mNum*mObjectsize;
    memcpy( ptr, obj, mObjectsize );
    mNum ++;
    return( ptr );
}

void *piArray::Append(const void *obj, int num, bool doexpand)
{
	if ((num+mNum) >= mMax)
	{
		if (!doexpand)
			return nullptr;

		long newmax = 4 * (num + mNum) / 3;
		if (newmax<4) newmax = 4;
		mBuffer = (unsigned char*)realloc(mBuffer, newmax*mObjectsize);
		if (!mBuffer)
			return nullptr;
		mMax = newmax;
		if (mDoZero)
			memset(mBuffer + mNum*mObjectsize, 0, (mMax - mNum)*mObjectsize);
	}
	unsigned char *ptr = mBuffer + mNum*mObjectsize;
	memcpy(ptr, obj, mObjectsize*num);
	mNum+=num;
	return(ptr);
}

bool piArray::Set(  const void *obj, unsigned int pos )
{
	const unsigned int num = mNum;
	const unsigned int obs = mObjectsize;
	if( pos>=mMax )
        return false;
    unsigned char *ptr = mBuffer + pos*obs;
	if (obj)
		memcpy(ptr, obj, mObjectsize);
	else
		memset(ptr, 0, mObjectsize);
    return true;
}

void *piArray::Insert(  const void *obj, unsigned int pos, bool doexpand )
{
	const unsigned int num = mNum;
	const unsigned int obs = mObjectsize;

	if( mNum>=mMax )
    {

		if( !doexpand )
			return nullptr;

        long newmax = 4*mMax/3;
        if( newmax<4 ) newmax = 4;
        mBuffer = (unsigned char*)realloc( mBuffer, newmax*mObjectsize );
        if( !mBuffer )
            return nullptr;
        mMax = newmax;
		if (mDoZero)
			memset(mBuffer + mNum*mObjectsize, 0, (mMax - mNum)*mObjectsize);
	}

	for( unsigned int i=num; i>pos; i-- )
	{
		unsigned char *ori = mBuffer + (i-1)*obs;
		unsigned char *dst = mBuffer + (i+0)*obs;
		memcpy( dst, ori, obs );
	}

    unsigned char *ptr = mBuffer + pos*obs;
	if( obj )
		memcpy( ptr, obj, mObjectsize );
	else
		memset(ptr, 0, mObjectsize);
	mNum ++;
    return( ptr );

}

void piArray::RemoveAndShift(  unsigned int pos )
{
	const unsigned int num = mNum;
	const unsigned int obs = mObjectsize;

	const unsigned int numelems = num-1-pos;
	if( numelems>0 )
	{
        unsigned char *ptr = mBuffer + pos*obs;
        for( unsigned int j=0; j<numelems; j++ )
        {
            for( unsigned int i=0; i<obs; i++ ) 
                ptr[i] = ptr[obs+i];
            ptr += obs;
        }
	}

    mNum --;
	if (mDoZero)
	{
		memset(mBuffer+mNum*obs, 0, obs);
	}
}

bool piArray::SetLength(  unsigned int num, bool doexpand )
{
    if( num>mMax )
    {
        if( !doexpand ) return false;
        mBuffer = (unsigned char*)realloc(mBuffer, num*mObjectsize);
        if (!mBuffer)
            return false;
        mMax = num;
		if (mDoZero)
			memset(mBuffer + mNum*mObjectsize, 0, (mMax - mNum)*mObjectsize);
	}

	mNum = num;
    return true;
}

bool piArray::SetMaxLength(unsigned int num)
{
    mBuffer = (unsigned char*)realloc(mBuffer, num*mObjectsize);
    if (!mBuffer)
        return false;
    mMax = num;
	if (mDoZero && mMax>mNum)
		memset(mBuffer + mNum*mObjectsize, 0, (mMax - mNum)*mObjectsize);
	return true;
}



/*



int ARRAY_CopyContent( ARRAY *dst, ARRAY *ori )
{
    if( dst->max<ori->num )
        return( 0 );

	dst->num = ori->num;
	memcpy( dst->buffer, ori->buffer, ori->num*ori->objectsize );

    return( 1 );
}

int ARRAY_CopyRawContent( ARRAY *dst, ARRAY *ori, unsigned int amount )
{
	memcpy( dst->buffer, ori->buffer, amount );

    return( 1 );
}


int ARRAY_Copy( ARRAY *dst, ARRAY *ori )
{
	if( !ARRAY_Init( dst, ori->max, ori->objectsize ) )
		return( 0 );

	dst->num = ori->num;
	memcpy( dst->buffer, ori->buffer, ori->num*ori->objectsize );

	return( 1 );
}




void ARRAY_Remove( ARRAY *me, unsigned int id )
{

    const unsigned int num = num - 1;
    const unsigned int objSize = objectsize;
    unsigned char *ptr = (unsigned char*)ARRAY_GetPointer( me, num );
    for( unsigned int i=id; i<num; i++ )
        memcpy( ptr+i*objSize, ptr+(i+1)*objSize, objSize );

    memset( ptr+id*objSize, 0, objSize );

    num--;
}




int ARRAY_AppendIntPtr( ARRAY *me, pint v )
{
    if( !ARRAY_InsertAndExpand( me, &v ) )
        return( 0 );

    return( 1 );
}

int ARRAY_AppendPtr( ARRAY *me, const void *ptr )
{
    pint i = (pint)ptr;

    if( !ARRAY_InsertAndExpand( me, &i ) )
        return( 0 );

    return( 1 );
}

*/

void piArray::SetPtr(  unsigned int id, const void *val )
{
    ((void**)mBuffer)[id] = (void*)val;
}



//------

bool piArray::AppendUInt8(   uint8_t  v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendSInt8(    int8_t   v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendUInt16(  uint16_t v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendSInt16(   int16_t  v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendUInt32(  uint32_t v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendSInt32(   int32_t  v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendUInt64(  uint64_t v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendSInt64(   int64_t  v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendFloat(   float  v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendDouble(  double v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }
bool piArray::AppendPtr(     void * v, bool doExpand ) { return piArray::Append( &v, doExpand )!=NULL; }

uint64_t piArray::GetUInt64(int id) const { return ((uint64_t*)mBuffer)[id]; }
int64_t  piArray::GetSInt64(int id) const { return ((int64_t*)mBuffer)[id]; }
uint32_t piArray::GetUInt32(int id) const { return ((uint32_t*)mBuffer)[id]; }
int32_t  piArray::GetSInt32(int id) const { return ((int32_t*)mBuffer)[id]; }
uint16_t piArray::GetUInt16(int id) const { return ((uint16_t*)mBuffer)[id]; }
int16_t  piArray::GetSInt16(int id) const { return ((int16_t*)mBuffer)[id]; }
uint8_t  piArray::GetUInt8(int id) const { return ((uint8_t *)mBuffer)[id]; }
int8_t   piArray::GetSInt8(int id) const { return ((int8_t *)mBuffer)[id]; }
void   * piArray::GetPtr(int id) const { return ((void **)mBuffer)[id]; }

}