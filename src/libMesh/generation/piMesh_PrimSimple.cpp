#include <math.h>
#include "../piMesh.h"
#include "piMesh_Generate.h"
#include "piMesh_ModComplex.h"

namespace piLibs {

bool piMesh_GenerateTorus(piMesh *me, const piMeshVertexFormat *vertexFormat, int gy, int gx, float ry, float rx)
{
    if (!me->Init( 1, (gx + 1)*(gy + 1), vertexFormat, piRMVEDT_Polys, 1, gx*gy))
        return false;

    int k = 0;
    for (int j = 0; j <= gy; j++)
    for (int i = 0; i <= gx; i++)
    {
        const float x = -1.0f + 2.0f*(float)(i) / (float)gx;
        const float y = -1.0f + 2.0f*(float)(j) / (float)gy;

        const float a = 6.2831f*x;
        const float b = 6.2831f*y;

        float ww = ry + rx*sinf(a);

        float *v = (float*)me->GetVertexData( STID, k++, POSID);
        v[0] = rx*cosf(a);
        v[1] = ww*sinf(b);
        v[2] = ww*cosf(b);
    }


    piMeshFace *face = me->mFaceData.mIndexArray[0].mBuffer;
    for (int j = 0; j<gy; j++)
    for (int i = 0; i<gx; i++)
    {
        face->mNum = 4;
        face->mIndex[0] = (gx + 1)*((j + 1) % gy) + ((i + 0) % gx);
        face->mIndex[1] = (gx + 1)*((j + 1) % gy) + ((i + 1) % gx);
        face->mIndex[2] = (gx + 1)*((j + 0) % gy) + ((i + 1) % gx);
        face->mIndex[3] = (gx + 1)*((j + 0) % gy) + ((i + 0) % gx);
        face++;
    }


    return true;

}

bool piMesh_GeneratePlane( piMesh *me, const piMeshVertexFormat *vertexFormat, int gx, int gy )
{
    if( !me->Init(1, (gx+1)*(gy+1), vertexFormat, piRMVEDT_Polys, 1, gx*gy ) )
        return false;

    int k = 0;
    for( int j=0; j<=gy; j++ )
    for( int i=0; i<=gx; i++ )
    {
        const float x = -1.0f + 2.0f*(float)(i)/(float)gx;
        const float y = -1.0f + 2.0f*(float)(j)/(float)gy;

        float *v = (float*)me->GetVertexData(  STID, k++, POSID );
        v[0] = x;
        v[1] = 0.0f;
        v[2] = y;
    }

    piMeshFace *face = me->mFaceData.mIndexArray[0].mBuffer;
    for( int j=0; j<gy; j++ )
    for( int i=0; i<gx; i++ )
    {
        face->mNum = 4;
#if 0
        face->mIndex[0] = (gx+1)*(j+0) + (i+0);
        face->mIndex[1] = (gx+1)*(j+1) + (i+0);
        face->mIndex[2] = (gx+1)*(j+1) + (i+1);
        face->mIndex[3] = (gx+1)*(j+0) + (i+1);
#else
        face->mIndex[0] = (gx+1)*(j+1) + (i+0);
        face->mIndex[1] = (gx+1)*(j+1) + (i+1);
        face->mIndex[2] = (gx+1)*(j+0) + (i+1);
        face->mIndex[3] = (gx+1)*(j+0) + (i+0);
#endif
        face++;
    }

    return true;
}

//     2------ 3
//    /|      /|
//   6-------7 |
//   | |     | |
//   | 0-----|-1
//   |/      |/
//   4-------5

static char cvd[] = { 
    0, 1, 5, 4,
    2, 6, 7, 3,
    1, 3, 7, 5,
    0, 4, 6, 2, 
    4, 5, 7, 6,
    0, 2, 3, 1 };

bool piMesh_GenerateCube( piMesh *me, const piMeshVertexFormat *vertexFormat )                     
{
    if( !me->Init( 1, 8, vertexFormat, piRMVEDT_Polys, 1, 6 ) )
        return false;

    for( int i=0; i<8; i++ )
    {
        float *v = (float*)me->GetVertexData( STID, i, POSID );
        v[0] = -1.0f+2.0f*((i>>0)&1);
        v[1] = -1.0f+2.0f*((i>>1)&1);
        v[2] = -1.0f+2.0f*((i>>2)&1);
    }
    

    
    piMeshFace *face = me->mFaceData.mIndexArray[0].mBuffer;
    for( int i=0; i<6; i++ )
    {
        face->mNum = 4;
        face->mIndex[0] = cvd[4*i+0];
        face->mIndex[1] = cvd[4*i+1];
        face->mIndex[2] = cvd[4*i+2];
        face->mIndex[3] = cvd[4*i+3];
        face++;
    }


    return true;
}


bool piMesh_GenerateCubePlanes(piMesh *me, const piMeshVertexFormat *vertexFormat)
{
    if (!me->Init( 1, 24, vertexFormat, piRMVEDT_Polys, 1, 6))
        return false;

    
    for (int i = 0; i<24; i++)
    {
        int f = i >> 2;
        int j = i & 3;

        float *v = (float*)me->GetVertexData( STID, i, POSID);

        if( f==0 )
        {
            v[0] = -1.0f;
            v[2] = -1.0f + 2.0f*((j >> 0) & 1);
            v[1] = -1.0f + 2.0f*((j >> 1) & 1);
        }
        else if (f == 1)
        {
            v[0] = 1.0f;
            v[1] = -1.0f + 2.0f*((j >> 0) & 1);
            v[2] = -1.0f + 2.0f*((j >> 1) & 1);
        }
        else if (f == 2)
        {
            v[0] = -1.0f + 2.0f*((j >> 0) & 1);
            v[1] = -1.0f;
            v[2] = -1.0f + 2.0f*((j >> 1) & 1);
        }
        else if (f == 3)
        {
            v[2] = -1.0f + 2.0f*((j >> 0) & 1);
            v[1] =  1.0f;
            v[0] = -1.0f + 2.0f*((j >> 1) & 1);
        }
        else if (f == 4)
        {
            v[1] = -1.0f + 2.0f*((j >> 0) & 1);
            v[0] = -1.0f + 2.0f*((j >> 1) & 1);
            v[2] = -1.0f;
        }
        else
        {
            v[0] = -1.0f + 2.0f*((j >> 0) & 1);
            v[1] = -1.0f + 2.0f*((j >> 1) & 1);
            v[2] = 1.0f;
        }
    }



    piMeshFace *face = me->mFaceData.mIndexArray[0].mBuffer;
    for (int i = 0; i<6; i++)
    {
        face->mNum = 4;
        face->mIndex[0] = 4*i + 0;
        face->mIndex[1] = 4*i + 1;
        face->mIndex[2] = 4*i + 3;
        face->mIndex[3] = 4*i + 2;
        face++;
    }


    return true;
}

bool piMesh_PatchedSphere(piMesh *me, const piMeshVertexFormat *vertexFormat, int n)
{
	/*
    const int nv = (n-1)*(n-1)*6 + (n-1)*12 + 1*8;
    const int nf = n*n*6;
    if (!me->Init( 1, nv, vertexFormat, piRMVEDT_Polys, 1, nf))
        return false;

    for( int i=0; i<6; i++ )
    {


    }
	*/
	if (!piMesh_GenerateCube(me, vertexFormat))
		return false;

	if (!piMesh_Subdivide(me, n, 1))
		return false;

	for (unsigned int i = 0; i < me->mVertexData.mVertexArray[0].mNum; i++)
	{
		vec3* v = (vec3*)me->GetVertexData(0, i, 0);
		*v = normalize(*v);
	}

    return true;
}

bool piMesh_GenerateRevolution( piMesh *me, const piMeshVertexFormat *vertexFormat, const vec2 *cv, int numCVs, int numRevs )
{
	const int nv = numRevs*(numCVs - 2) + 2;
	const int nf = (numCVs - 3)*numRevs + 2*numRevs;
    
	if (!me->Init(1, nv, vertexFormat, piRMVEDT_Polys, 1, nf))
		return false;

	int vid = 0;
	int fid = 0;

	{
		vec3 *v = (vec3*)me->GetVertexData(STID, vid++, POSID);
		*v = vec3(0.0f, cv[0].y, 0.0f);
	}
	for( int j=1; j<(numCVs-1); j++ )
	for( int i=0; i<numRevs; i++ )
	{
		const float u = (float)i/(float)numRevs;
		const float a = 6.2831f*u;
		vec3 *v = (vec3*)me->GetVertexData(STID, vid++, POSID);
		*v = vec3(cv[j].x*sinf(a), cv[j].y, cv[j].x*cosf(a));
	}
	{
		vec3 *v = (vec3*)me->GetVertexData(STID, vid++, POSID);
		*v = vec3(0.0f, cv[numCVs-1].y, 0.0f);
	}

    for( int i=0; i<numRevs; i++ )
    {
		me->SetTriangle(0, fid++, 
			0, 
			1 + i, 
			1 + ((i + 1) % numRevs));
    }
	
    for( int j=0; j<(numCVs-3); j++ )
    for( int i=0; i<numRevs; i++ )
    {
		me->SetQuad(0, fid++, 
		1 + ((j  ))*numRevs +   i,
		1 + ((j+1))*numRevs +   i,
		1 + ((j+1))*numRevs + ((i+1)% numRevs),
		1 + ((j  ))*numRevs + ((i+1)% numRevs) );
	}
	
    for( int i=0; i<numRevs; i++ )
    {
		me->SetTriangle(0, fid++, 
		nv-1,
		nv-2 - i,
		nv-2 - ((i+1)% numRevs) );
	}

    return true;
}


}