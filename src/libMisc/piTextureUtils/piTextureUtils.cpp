#include "piTextureUtils.h"

namespace piLibs {

void piTextureInfo_FromImage( piRenderer::TextureInfo *info, const piImage *img, bool compressed, bool bgra2rgba )
{
    const piImage::Type   itype = img->GetType();
    const piImage::Format format = img->GetFormat();
    
           if (itype == piImage::TYPE_1D)     info->mType = piRenderer::TextureType::T1D;
    else   if( itype==piImage::TYPE_2D )      info->mType = piRenderer::TextureType::T2D;
    else   if( itype==piImage::TYPE_3D )      info->mType = piRenderer::TextureType::T3D;
    else /*if( img->type==piImage::TYPE_CUBE )*/ info->mType = piRenderer::TextureType::TCUBE;
    

         if( format== piImage::FORMAT_I_INDEXED) info->mFormat = piFORMAT_C1I8;
    else if( format==piImage::FORMAT_I_GREY    ) info->mFormat = piFORMAT_C1I8;
    else if( format==piImage::FORMAT_I_15BIT   ) info->mFormat = piFORMAT_UNKOWN;
    else if( format==piImage::FORMAT_I_16BIT   ) info->mFormat = piFORMAT_UNKOWN;
    else if( format==piImage::FORMAT_I_RGB     ) info->mFormat = (bgra2rgba) ? piFORMAT_C3I8_RGB : piFORMAT_C3I8_BGR;
    else if( format==piImage::FORMAT_I_RG      ) info->mFormat = piFORMAT_C2I8;
    else if( format==piImage::FORMAT_I_RGBA    ) info->mFormat = (bgra2rgba) ? piFORMAT_C4I8_RGBA : piFORMAT_C4I8_BGRA;
    else if( format==piImage::FORMAT_F_GREY    ) info->mFormat = piFORMAT_C1F16;
    else if( format==piImage::FORMAT_F_RG      ) info->mFormat = piFORMAT_C2F16;
    else if( format==piImage::FORMAT_F_RGB     ) info->mFormat = piFORMAT_C3F16_RGB;
    else if( format==piImage::FORMAT_F_RGBA    ) info->mFormat = piFORMAT_C4F16_RGBA;

    info->mXres = img->GetXRes();
    info->mYres = img->GetYRes();
    info->mZres = img->GetZRes();
    info->mCompressed = compressed;
	info->mMultisample = 1;
}

bool piTextureInfo_AreEqual( const piRenderer::TextureInfo *a, const  piRenderer::TextureInfo *b )
{
    if( a->mType != b->mType ) return false;
    if( a->mFormat != b->mFormat ) return false;
    if( a->mCompressed != b->mCompressed ) return false;
    if( a->mXres != b->mXres ) return false;
    if( a->mYres != b->mYres ) return false;
    if( a->mZres != b->mZres ) return false;

    return true;
}


/*
piTexture piTextureInfo_CreateTextureFromImageFile( const wchar_t *name, const wchar_t *key, bool compressed, piTextureFilter filter, piTextureWrap wrap1, piTextureWrap wrap2, piRenderer *renderer )
{
    piImage image;
    if( !piImage::Load( &image, name ) )
        return 0;

    piTextureInfo info;
    piTextureInfo_FromImage( &info, &image, compressed );
    piTexture *tex = renderer->CreateTexture( 0, &info, filter, wrap1, wrap2, image.data );
	piImage::Free( &image );

    return tex;
}*/

}