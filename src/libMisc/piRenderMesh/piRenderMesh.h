#pragma once

// falta que se pueda hacer LOD con numero de polys pintados
// falta que se pueda hacer sortable IA...

#include "../../libLog/piLog.h"
#include "../../libRender/piRenderer.h"
#include "../../libMesh/piMesh.h"

namespace piLibs {


#define IQRENDERMESH_MAXELEMS    8
#define IQRENDERMESH_MAXSTREAMS  8
#define IQRENDERMESH_MAXELEMENTARRAYS 48

typedef struct
{
    void                       *mBuffer;
    piRArrayLayout              mLayout;
    piBuffer                    mVBO;
    unsigned int	            mLength;
}piRenderMeshVertexStream;

typedef struct
{
    unsigned int	          mNumStreams;
    piRenderMeshVertexStream  mStream[IQRENDERMESH_MAXSTREAMS];
}piRenderMeshVertexData;

typedef struct
{
//    unsigned int *mTmpRadix;
//    unsigned int *mSortedBuffer;
    unsigned int    mNum;
    unsigned int   *mBuffer;
    piBuffer        mIBO;
	struct
	{
		int mNum;
		piVertexArray   mVAO[32];
	}mVertexArray;
}piRenderMeshElementArray;




class piRenderMesh
{
public:
    piRenderMesh();
    ~piRenderMesh();

    bool InitFromMesh( piRenderer *renderer, const piMesh *mesh, piRenderer::PrimitiveType patchNum );
	bool InitFromMeshWithShader(piRenderer *renderer, const piMesh *mesh, piRenderer::PrimitiveType patchNum,
		int numShader, const void **shaders, const int *shaderSizes, piLog *log);

    void End( piRenderer *renderer );

    void Render( piRenderer *renderer, int elementArrayID, int vertexArrayID, int numInstances ) const;

    const bound3 & GetBBox( void ) const;

    const int GetNumVertices( void ) const;
    const piBuffer GetVertexBuffer( int stream ) const;

private:
	bool iInitBuffers(piRenderer *renderer, const piMesh *mesh, piRenderer::PrimitiveType patchNum);

private:
    bound3                  mBBox;
    piRenderMeshVertexData  mVertexData;
	struct
	{
		piRenderer::PrimitiveType   mType;
		unsigned int    mNumElementArrays;
		piRenderMeshElementArray mElementArray[IQRENDERMESH_MAXELEMENTARRAYS];
	}mIndexData;
};


} // namespace piLibs