#include <malloc.h>
#include <string.h>
#include "piPool.h"
#include "../libSystem/piTypes.h"

namespace piLibs {

piPool::piPool()
{
    mBuffer = nullptr;
    mMax = 0;
    mNum = 0;
    mObjectsize = 0;
}

piPool::~piPool()
{
}

bool piPool::Init(  unsigned int max, unsigned int objectsize )
{
	mObjectsize = objectsize;
    mMax = max;
    mNum = 0;
    mBuffer = (unsigned char*)malloc( max*(objectsize+1) );
    if( mBuffer==nullptr )
        return false;

    this->Reset();

    return true;
}

void piPool::End(void)
{
    if( mBuffer ) free( mBuffer );
    mBuffer = 0;
	mMax = 0;
	mNum = 0;
	mObjectsize = 0;
}

void piPool::Reset(void)
{
    // mark all as unused
    const int num = mNum;
    for (int i = 0; i<num; i++)
    {
        unsigned char * used = mBuffer + i*(mObjectsize+1);
        *used = false;
    }
}

unsigned int piPool::GetLength(void) const
{
    return mNum;
}

void *piPool::Get(const unsigned int n) const
{
	return (void*)(mBuffer+n*(mObjectsize+1)+1);
}

uint64_t piPool::GetUInt64(int id) const { return *((uint64_t*)(mBuffer + id*(mObjectsize + 1) + 1)); }
int64_t  piPool::GetSInt64(int id) const { return *(( int64_t*)(mBuffer + id*(mObjectsize + 1) + 1)); }
uint32_t piPool::GetUInt32(int id) const { return *((uint32_t*)(mBuffer + id*(mObjectsize + 1) + 1)); }
int32_t  piPool::GetSInt32(int id) const { return *(( int32_t*)(mBuffer + id*(mObjectsize + 1) + 1)); }
uint16_t piPool::GetUInt16(int id) const { return *((uint16_t*)(mBuffer + id*(mObjectsize + 1) + 1)); }
int16_t  piPool::GetSInt16(int id) const { return *(( int16_t*)(mBuffer + id*(mObjectsize + 1) + 1)); }
uint8_t  piPool::GetUInt8( int id) const { return *(( uint8_t*)(mBuffer + id*(mObjectsize + 1) + 1)); }
int8_t   piPool::GetSInt8( int id) const { return *((  int8_t*)(mBuffer + id*(mObjectsize + 1) + 1)); }
void   * piPool::GetPtr(   int id) const { return *((  void **)(mBuffer + id*(mObjectsize + 1) + 1)); }


void *piPool::Alloc(bool * isNew, int *id)
{
    // first, try to find an unused one
    const int num = mNum;
    for (int i = 0; i<num; i++)
    {
        unsigned char * used = mBuffer + i*(mObjectsize + 1);
        if( *used == false)
        {
            *isNew = false;
            *used = true; // mark it as used
            if (id) *id = i;
            return (void*)(used+1);
        }
    }

    // allocate a new one

    // grow if needed
    {
        if ((mNum + 1)>mMax)
        {
            long newmax = 4 * mMax / 3; if (newmax<4) newmax = 4;
            mBuffer = (unsigned char*)realloc(mBuffer, newmax * (mObjectsize+1));
            if (!mBuffer)
                return nullptr;
            mMax = newmax;
            for( unsigned int i= mNum; i<mMax; i++ )
            {
                unsigned char * used = mBuffer + i*(mObjectsize + 1);
                *used = false;
            }
        }
    }

    // allocate
    unsigned char * used = mBuffer + mNum*(mObjectsize + 1);
    if (id) *id = mNum;
    mNum += 1;
    *used = true;
    *isNew = true;
    return (void*)(used + 1);
}


}