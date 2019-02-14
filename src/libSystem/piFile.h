#pragma once

#include "piTypes.h"

namespace piLibs {

class piFile
{
public:
    piFile();
    ~piFile();

    static bool  DirectoryCreate(const wchar_t *name, bool failOnExists);
    static bool  DirectoryExists(const wchar_t *dirName_in);
    static bool  Exists(const wchar_t *name);
    static bool  HaveWriteAccess( const wchar_t *name );
    static bool  Copy(const wchar_t *dst, const wchar_t *src, bool failIfexists);
	static uint64_t GetLength(const wchar_t *filename);

    typedef enum
    {
        CURRENT = 0,
        END = 1,
        SET = 2
    }SeekMode;

    bool         Open(const wchar_t *name, const wchar_t *mode);
    bool         Seek(uint64_t pos, SeekMode mode);
    uint64_t     Tell(void);
    void         Close( void );
    uint64_t     GetLength( void );
    
    //----------------------

    char *       ReadString(char *buffer, int num);
    void         Prints(const wchar_t *str);
    void         Printf(const wchar_t *format, ...);

    //-----------------------

    bool         Read(void *dst, uint64_t amount);
    uint8_t      ReadUInt8( void );
    uint16_t     ReadUInt16( void );
    uint32_t     ReadUInt32( void );
    uint64_t     ReadUInt64( void );
    float        ReadFloat( void );
    void         ReadFloatarray(float *dst, int num, int size, uint64_t amount);
    void         ReadFloatarray2(float *dst, uint64_t amount);
    void         ReadDoublearray2(double *dst, uint64_t amount);
    void         ReadUInt64array(uint64_t *dst, uint64_t amount);
    void         ReadUInt32array(uint32_t *dst, uint64_t amount);
    void         ReadUInt32array2(uint32_t *dst, uint64_t amount, int size, int stride);
    void	     ReadUInt16array(uint16_t *dst, uint64_t amount);
    void	     ReadUInt8array(uint8_t *dst, uint64_t amount);

	size_t       Write(const void *dst, uint64_t amount);
    void		 WriteUInt8(uint8_t x);
    void		 WriteUInt16(uint16_t x);
    void		 WriteUInt32(uint32_t x);
    void		 WriteUInt64(uint64_t x);
    void		 WriteFloat(float x);
    void		 WriteUInt8array(uint8_t *dst, uint64_t amount);
    void		 WriteUInt16array(uint16_t *dst, uint64_t amount);
    void		 WriteUInt32array(uint32_t *dst, uint64_t amount);
    void		 WriteUInt64array(uint64_t *dst, uint64_t amount);
    void		 WriteFloatarray2(float *ori, uint64_t amout);
    void		 WriteDoublearray2(double *ori, uint64_t amout);

private:
    void *mInternal;

};

} // namespace piLibs