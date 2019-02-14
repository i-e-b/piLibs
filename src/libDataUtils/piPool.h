#pragma once

#include "../libSystem/piTypes.h"

namespace piLibs {

class piPool
{
public:
    piPool();
    ~piPool();

    bool         Init( unsigned int max, unsigned int objectsize);
    void         End(void);
    unsigned int GetLength(void) const;
    void         Reset(void);
    void        *Alloc(bool * isNew, int *id);

    void        *Get(const unsigned int n) const;
    uint64_t     GetUInt64(int id) const;
    int64_t      GetSInt64(int id) const;
    uint32_t     GetUInt32(int id) const;
    int32_t      GetSInt32(int id) const;
    uint16_t     GetUInt16(int id) const;
    int16_t      GetSInt16(int id) const;
    uint8_t      GetUInt8(int id) const;
    int8_t       GetSInt8(int id) const;
    void        *GetPtr(int id) const;


private:
    unsigned char *mBuffer;
    unsigned int  mMax;
    unsigned int  mNum;
    unsigned int  mObjectsize;
};

} // namespace piLibs
