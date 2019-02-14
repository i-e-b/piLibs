#include <malloc.h>
#include <string.h>

#include "../piImage.h"

namespace piLibs {

bool piImage_Flip( piImage *spr )
{
    const size_t xres = spr->GetXRes();
    const size_t yres = spr->GetYRes();
    const size_t bpp = spr->GetBpp();
    const size_t n = xres*bpp;
    
    unsigned char *aux = (unsigned char *)malloc( n );
    if( !aux )
        return false;

    unsigned char *b1 = (unsigned char *)spr->GetData();
    unsigned char *b2 = (unsigned char *)spr->GetData() + (yres - 1)*n;
    const size_t numl = yres>>1;
    for(size_t i=0; i<numl; i++ )
    {
        memcpy( aux, b1, n );
        memcpy( b1, b2, n );
        memcpy( b2, aux, n );
        b1 += n;
        b2 -= n;
    }

    free( aux );

    return true;
}

}