#pragma once

#include "../piImage.h"

namespace piLibs {

//long BMP_Carga8( char *nombre, unsigned char *buffer, long xres, long yres );

    bool PNG_Save( const piImage *bmp, const wchar_t *name );
    int  PNG_Load(       piImage *bmp, const wchar_t *name );
    int  PNG_LoadMem(    piImage *bmp, const unsigned char *mem, int size );

} // namespace piLibs