#include <malloc.h>
#include <string.h>
#include "piUOIntIntMap.h"
#include "../libSystem/piTypes.h"

namespace piLibs {

piUOIntIntMap::piUOIntIntMap()
{
}

piUOIntIntMap::~piUOIntIntMap()
{
}

bool piUOIntIntMap::Init(unsigned int max)
{
    mMax = max;
    mNum = 0;
    mBuffer = (uint32_t*)malloc(max * 2 * sizeof(uint32_t));
    if (!mBuffer)
        return false;
    return true;
}

void piUOIntIntMap::End(void)
{
    free(mBuffer);
}

uint32_t piUOIntIntMap::FindFirst(const uint32_t first) const
{
    const int num = mNum;
    for (int i = 0; i<num; i++) if (mBuffer[2 * i + 0] == first) return mBuffer[2 * i + 1];
    return 0xffffffff;
}

uint32_t piUOIntIntMap::FindSecond(const uint32_t second) const
{
    const int num = mNum;
    for (int i = 0; i<num; i++) if (mBuffer[2 * i + 1] == second) return mBuffer[2 * i + 0];
    return 0xffffffff;
}

bool piUOIntIntMap::Find(const uint32_t first, const uint32_t second) const
{
    const int num = mNum;
    for (int i = 0; i<num; i++) if (mBuffer[2 * i + 0] == first && mBuffer[2 * i + 1] == second) return true;
    return false;
}

bool piUOIntIntMap::Add(const uint32_t first, const uint32_t second, const bool doexpand)
{
    if (Find(first, second)) return false;

    if ((mNum + 1)>mMax)
    {
        if (doexpand == false)
            return nullptr;

        long newmax = 4 * mMax / 3;
        if (newmax<4) newmax = 4;
        mBuffer = (uint32_t*)realloc(mBuffer, newmax * 2 * sizeof(uint32_t));
        if (!mBuffer)
            return false;
        mMax = newmax;
    }

    mBuffer[2 * mNum + 0] = first;
    mBuffer[2 * mNum + 1] = second;

    mNum = mNum + 1;

    return true;
}




} // namespace piLibs