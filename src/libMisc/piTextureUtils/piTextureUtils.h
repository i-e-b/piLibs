#pragma once

#include "../../libRender/piRenderer.h"
#include "../../libImage/piImage.h"

namespace piLibs {

void piTextureInfo_FromImage( piRenderer::TextureInfo *info, const piImage *img, bool compressed, bool bgra2rgba );
bool piTextureInfo_AreEqual( const piRenderer::TextureInfo *a, const piRenderer::TextureInfo *b );
//piTexture piTextureInfo_CreateTextureFromImageFile( const wchar_t *name, const wchar_t *key, bool compressed, piTextureFilter filter, piTextureWrap wrap1, piTextureWrap wrap2 );

} // namespace piLibs