#pragma once

#include "../libSystem/piTypes.h"

namespace piLibs {

class piUOIntIntMap
{
public:
    piUOIntIntMap();
    ~piUOIntIntMap();

    bool Init(unsigned int max);
    void End(void);

    uint32_t FindFirst(const uint32_t first) const;
    uint32_t FindSecond(const uint32_t second) const;
    bool     Find(const uint32_t first, const uint32_t second) const;

    bool Add(const uint32_t first, const uint32_t second, const bool doexpand);

private:
    uint32_t     *mBuffer;
    unsigned int  mMax;
    unsigned int  mNum;
};


} // namespace piLibs