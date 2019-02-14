#pragma once

#include "../libSystem/piTypes.h"

namespace piLibs {

class piArray
{
public:
    piArray();
    ~piArray();

    int          Init( unsigned int max, unsigned int objectsize, bool doZero = true);
    void         End(void);
    unsigned int GetLength(void) const;
    unsigned int GetMaxLength(void) const;
    bool         IsInitialized( void ) const;

    void   Reset(void);
    bool   SetLength( unsigned int num, bool doexpand = false);
    bool   SetMaxLength(unsigned int num);
    void  *GetAddress(const  unsigned int n) const;

    void  *Alloc( unsigned int num, bool doexpand = false);
    void  *Append( const void *obj, bool doexpand = false);
	void  *Append(const void *obj, int num, bool doexpand = false);
    void  *Insert( const void *obj, unsigned int pos, bool doexpand = false);
    bool   Set( const void *obj, unsigned int pos);
    void   RemoveAndShift(unsigned int pos);

    bool   AppendUInt8(uint8_t  v, bool doExpand = false);
    bool   AppendSInt8(int8_t  v, bool doExpand = false);
    bool   AppendUInt16(uint16_t v, bool doExpand = false);
    bool   AppendSInt16(int16_t v, bool doExpand = false);
    bool   AppendUInt32(uint32_t v, bool doExpand = false);
    bool   AppendSInt32(int32_t v, bool doExpand = false);
    bool   AppendUInt64(uint64_t v, bool doExpand = false);
    bool   AppendSInt64(int64_t v, bool doExpand = false);
    bool   AppendFloat(float  v, bool doExpand = false);
    bool   AppendDouble(double v, bool doExpand = false);
    bool   AppendPtr( void * v, bool doExpand=false);

    void   SetPtr( unsigned int id, const void *val);

    uint64_t GetUInt64(int id) const;
    int64_t  GetSInt64(int id) const;
    uint32_t GetUInt32(int id) const;
    int32_t  GetSInt32(int id) const;
    uint16_t GetUInt16(int id) const;
    int16_t  GetSInt16(int id) const;
    uint8_t  GetUInt8(int id) const;
    int8_t   GetSInt8(int id) const;
    void    *GetPtr(int id) const;

private:
    unsigned char *mBuffer;
    unsigned int  mMax;
    unsigned int  mNum;
    unsigned int  mObjectsize;
	bool          mDoZero;
};

} // namespace piLibs
