#include <stdio.h>
#include "../piImage.h"

namespace piLibs {

/*
long BMP_Carga8( char *nombre, unsigned char *buffer, long xres, long yres )
{
    FILE    *fp;

    fp = fopen( nombre, "rb" );
    if( !fp )
        {
        return( 0 );
        }

    fseek( fp, 54+1024, SEEK_SET );

    buffer += xres*(yres-1);
    while( yres-- )
        {
        fread( buffer, 1, xres, fp );
        buffer -= xres;
        }

    fclose( fp );
    
    return( 1 );
}*/
int BMP_Load( piImage *bmp, const wchar_t *name )
{
    FILE            *fp;
//    long            res = 0;
//	TGAHEADER       tga;


    fp = _wfopen( name, L"rb" );
    if( !fp )
        return( 0 );
/*
    if( !fread( &tga, 18, 1, fp) )
        {
        fclose( fp );
        return( 0 );
        }

#ifdef BIGENDIAN
tga.xres = ((tga.xres&255)<<8) | (tga.xres>>8);
tga.yres = ((tga.yres&255)<<8) | (tga.yres>>8);
#endif

    if( tga.xres<2 || tga.yres<2 )
		{
		fclose( fp );
        return( 0 );
		}

    if( (tga.bpp!=24) && (tga.bpp!=32) && (tga.bpp!=16) && (tga.bpp!=8))
		{
		fclose( fp );
        return( 0 );
		}

    if( tga.IDFieldLength )
        for( i=0; i<tga.IDFieldLength; i++ )
            fread( &byte, 1, 1, fp);


    switch( tga.ImageType )
        {
		// uncommpressed rgb
        case 2:

			if( tga.bpp==24 )
				format = IMAGE_FORMAT_I_RGB;
			else if( tga.bpp==32 )
				format = IMAGE_FORMAT_I_RGBA;
			else
				break;
			
			if( !IMAGE_Make( bmp, tga.xres, tga.yres, 1, format ) )
				break;
            if( !U_Load(bmp,fp) )
				break;
			if( !IMAGE_Flip(bmp) )
				break;
            res = 1;
            break;

		// compressed rgb
        case 10:                    
            if( tga.bpp==24 )
				format = IMAGE_FORMAT_I_RGB;
			else if( tga.bpp==32 )
				format = IMAGE_FORMAT_I_RGBA;
			else
				break;

			if( !IMAGE_Make( bmp, tga.xres, tga.yres, 1, format ) )
				break;
            if( !C_Load(bmp,fp) )
				break;
			if( !IMAGE_Flip(bmp) )
				break;
            res = 1;
            break;

		// uncompressed grey
        case 3:                                 
			if( !IMAGE_Make( bmp, tga.xres, tga.yres, 1, IMAGE_FORMAT_I_GREY ) )
				break;
            if( !U_Load(bmp,fp) )
				break;
			if( !IMAGE_Flip(bmp) )
				break;
            res = 1;
            break;

		// compressed grey
        case 11:                                 
			if( !IMAGE_Make( bmp, tga.xres, tga.yres, 1, IMAGE_FORMAT_I_GREY ) )
				break;
            if( !C_Load(bmp,fp) )
				break;
			if( !IMAGE_Flip(bmp) )
				break;
            res = 1;
            break;

        case 1:                                 // uncompressed pallete
            break;

        case 9:                                 // compressed pallete
            break;
        }

	if( !res )
		IMAGE_Free( bmp );

    fclose( fp );

    return( res );*/
    return( 0 );
}

bool BMP_Salva24( const wchar_t *nombre, unsigned char *buffer, int xres, int yres )
{
    if( xres<=0 || yres<=0 )
        return false;

    FILE *fo = _wfopen( nombre, L"wb" );
    if( !fo )
        return false;

  //  fwrite( head32, 1, 18, fo );

    for( int i=0; i<yres; i++ )
    {
        fseek( fo, 18 + 4*xres*(yres-i-1), SEEK_SET );
        fwrite( buffer, xres, 4, fo );
        buffer += xres;
    }

    fclose( fo );

    return true;
}


static unsigned char bmpheader[54] = {
// Header = 14 bytes
0x42, 0x4D,              //  0: signature = BM
0x00, 0x00, 0x00, 0x00,  //  2: [size]
0x00, 0x00,              //  6: reserved
0x00, 0x00,              //  8: reserved 
0x36, 0x00, 0x00, 0x00,  // 10: offset to pixels = 54 = sizeof(Header) + sizeof(Info)

// Info = 40 bytes
0x28, 0x00, 0x00, 0x00,  // 14: header size = 40
0x00, 0x00, 0x00, 0x00,  // 18: [xres]
0x00, 0x00, 0x00, 0x00,  // 22: [yres]
0x01, 0x00,              // 26: bit planes = 1
0x18, 0x00,              // 28: bits per pixel = 24
0x00, 0x00, 0x00, 0x00,  // 30: compression:  0=none, 1=8bit RLE, 2=4bit RLE, 3=RGB with mask
0x00, 0x00, 0x00, 0x00,  // 34: [image size]
0xC3, 0x0E, 0x00, 0x00,  // 38: Pixels per meter X (3779)
0xC3, 0x0E, 0x00, 0x00,  // 42: Pixels per meter Y 
0x00, 0x00, 0x00, 0x00,  // 46: number of colors (pallette)
0x00, 0x00, 0x00, 0x00   // 50: important colors (pallette)
};

bool BMP_Salva32To24( const wchar_t *nombre, unsigned char *buffer, int xres, int yres )
{
    if( xres<=0 || yres<=0 )
        return false;

    FILE *fo = _wfopen( nombre, L"wb" );
    if( !fo )
        return false;

    *((int*)(bmpheader+ 2)) = xres*yres*3 + 54;
    *((int*)(bmpheader+18)) = xres;
    *((int*)(bmpheader+22)) = yres;
    *((int*)(bmpheader+34)) = xres*yres*3;

    fseek( fo, 0, SEEK_SET );
    fwrite( bmpheader, 1, 54, fo );

    for( int i=0; i<(xres*yres); i++ )
    {
        fwrite( buffer, 1, 3, fo );
        buffer += 4;
    }

    fclose( fo );

    return true;
}

bool BMP_Save( const piImage *bmp, const wchar_t *name )
{
    const int xres = bmp->GetXRes();
    const int yres = bmp->GetYRes();
    void *data = bmp->GetData();

    if( bmp->GetFormat()==piImage::FORMAT_I_RGB )
        return BMP_Salva24( name, (unsigned char*)data, xres, yres );

    if (bmp->GetFormat() == piImage::FORMAT_I_RGBA)
        return BMP_Salva32To24( name, (unsigned char*)data, xres, yres );
/*       
    if( bmp->format==IMAGE_FORMAT_I_GREY )
        return BMP_Salva8( name, (unsigned char*)bmp->data, bmp->xres, bmp->yres );
*/
	return false;
}

}