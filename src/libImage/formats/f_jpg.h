#pragma once

#include "../piImage.h"

namespace piLibs {

int JPG_Load( piImage *image, const wchar_t *name );
int JPG_LoadMem( piImage *image, const unsigned char *mem, int size );

} // namespace piLibs