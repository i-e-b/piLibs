//#define USETRICAT

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../piMesh.h"

#include "../../libSystem/piFile.h"
#include "../../libSystem/piStr.h"
#include "../../libDataUtils/piArray.h"
#include "../../libDataUtils/piTArray.h"
#include "../../libMath/piVecTypes.h"

namespace piLibs {


static int readline( char *str, int max, piFile *fp )
{
    size_t l;

	if( !fp->ReadString(str,max) )
        return( 0 );

    l = strlen(str)-1;
    while( str[l]==10 || str[l]==13 )
        str[l] = 0;

    return( 1 );
}

//---------------------------------------------

static int splitInWords( char *str, char **ptrs, const char *sep, int num )
{
    char *tmp = 0;

	int i;
	for(i=0; i<num; i++ )
	{
		ptrs[i] = pistrtok( i==0?str:0, sep, &tmp);
		if( ptrs[i]==0 )
			break;
	}
	return i;
}

bool piMeshObj_Read( piMesh *me, const wchar_t *name, bool calcNormals )
{
    char    str[1024];
	char	*ptrs[256];
    piTArray<vec3>        vertices;
	piTArray<vec3>        vertex_color;
	piTArray<piMeshFace>  faces;

    piFile fp; 
	if (!fp.Open(name, L"rt"))
		return false;

    if (!vertices.Init( 512 * 1024, false))
    {
        fp.Close();
		return false;
	}

	if (!vertex_color.Init(512 * 1024, false))
	{
		fp.Close();
		return false;
	}

    if (!faces.Init(512 * 1024, false))
    {
        fp.Close();
		return false;
	}

    // get all the vertices
    for(;;)
    {
        if( !readline( str, 1023, &fp ) )
            break;

        int n = splitInWords( str, ptrs, ", \t", 256 );
    
        if( n>0 )
        {
            if( ptrs[0][0]=='v' && ptrs[0][1]=='\0' )
            {
				vec3 vert;
                vert.x = (float)atof( ptrs[1] );
                vert.y = (float)atof( ptrs[2] );
                vert.z = (float)atof( ptrs[3] );
                vertices.Append(&vert, true);
				if (n == 7)
				{
					vert.x = (float)atof(ptrs[4]);
					vert.y = (float)atof(ptrs[5]);
					vert.z = (float)atof(ptrs[6]);
					vertex_color.Append(&vert, true);
				}
            }            
        }
    }

	const int numVertices = vertices.GetLength();
	const int numVertexColors = vertex_color.GetLength();
    
	// check that we have as many vertex colors as we have vertices
	if ((numVertexColors > 0) && (numVertexColors != numVertices))
	{
		fp.Close();
		vertex_color.End();
		vertices.End();
		faces.End();
		return false;
	}

    // get all the faces
    fp.Seek( 0, piFile::SET );

    //int group    = -1;
    //int newgrouprequest = 0;
    //int matid = -1;
    faces.SetLength( 0 );

    for(;;)
    {
	    piMeshFace   face;

        if( !readline( str, 1023, &fp ) )
            break;

        int n = splitInWords( str, ptrs, ", \t", 256 );
        if( n>0 )
        {
            if( ptrs[0][0]=='v' && ptrs[0][1]=='\0' )
            {
            }
            //else if( ptrs[0][0]=='g' && ptrs[0][1]=='\0' )
           // {
            //    newgrouprequest=1;
            //}
            //else if( strcmp(ptrs[0],"usemtl")==0 )
           // {
           //     newgrouprequest=1;
           // }
            else if( ptrs[0][0]=='f' && ptrs[0][1]=='\0' && n>=(3+1) )
            {
                if( n==(1+3) )
                {
                    face.mNum = 3;
                    face.mIndex[0] = atoi(ptrs[1])-1;
                    face.mIndex[1] = atoi(ptrs[2])-1;
                    face.mIndex[2] = atoi(ptrs[3])-1;
                    //face.mat = matid;
                    faces.Append(&face, true);
                }
                else if( n==(1+4) )
                {
                    face.mNum = 4;
                    face.mIndex[0] = atoi(ptrs[1])-1;
                    face.mIndex[1] = atoi(ptrs[2])-1;
                    face.mIndex[2] = atoi(ptrs[3])-1;
                    face.mIndex[3] = atoi(ptrs[4])-1;
                    //face.mat = matid;
                    faces.Append( &face, true);
                }
                else
                {
                    // TODO: tesselate N-polygons into triangle!
                    const int num = n-1;
					if( num<256 )
					{	
						unsigned int indices[256];
						for( int i=0; i<num; i++ )
							indices[i] = atoi(ptrs[1+i])-1;

						for( int i=0; i<num-2; i++ )
						{
                            face.mNum = 3;
							face.mIndex[0] = indices[0];
							face.mIndex[1] = indices[i+1];
							face.mIndex[2] = indices[i+2];
							//face.mat = matid;
                            faces.Append( &face, true);
						}
					}
                }
            }     
        }
    }

	piMeshVertexFormat vf;
	vf.mDivisor = 0;
	vf.mNumElems = 0;
	vf.mStride = 0;
	int vid = -1, cid = -1, nid = -1;

	{
		vid = vf.mNumElems;
		vf.mElems[vf.mNumElems] = { 3, piRMVEDT_Float, false };
		vf.mStride += 3 * sizeof(float);
		vf.mNumElems += 1;
	}
	if (vertex_color.GetLength() > 0)
	{
		cid = vf.mNumElems;
		vf.mElems[vf.mNumElems] = { 3, piRMVEDT_Float, false };
		vf.mStride += 3 * sizeof(float);
		vf.mNumElems += 1;
	}
	if (calcNormals)
	{
		nid = vf.mNumElems;
		vf.mElems[vf.mNumElems] = { 3, piRMVEDT_Float, false };
		vf.mStride += 3 * sizeof(float);
		vf.mNumElems += 1;
	}

    if (!me->Init( 1, numVertices, &vf, piRMVEDT_Polys, 1, faces.GetLength()))
    {
        fp.Close();
		vertex_color.End();
		vertices.End();
		faces.End();
		return false;
    }

    // copy vertices
	{
		const float *vptr = (float*)vertices.GetAddress(0);
		for ( int i = 0; i < numVertices; i++)
		{
			float *v = (float*)me->GetVertexData(0, i, vid);
			v[0] = vptr[0];
			v[1] = vptr[1];
			v[2] = vptr[2];
			vptr += 3;
		}
	}
	// copy vertex colors
	{
		const float *vptr = (float*)vertex_color.GetAddress(0);
		for ( int i = 0; i < numVertexColors; i++)
		{
			float *v = (float*)me->GetVertexData(0, i, cid);
			v[0] = vptr[0];
			v[1] = vptr[1];
			v[2] = vptr[2];
			vptr += 3;
		}
	}

    // copy faces
    memcpy(me->mFaceData.mIndexArray[0].mBuffer, faces.GetAddress(0), faces.GetLength()*sizeof(piMeshFace));

    fp.Close();

	vertex_color.End();
    vertices.End();
    faces.End();
    //-------------------

    if( calcNormals )
    {
        me->Normalize( 0, vid, nid );
    }

    return true;
}

}

