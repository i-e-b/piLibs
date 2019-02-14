#include <malloc.h>
#include <stdio.h>

#define GLCOREARB_PROTOTYPES
#include "glcorearb.h"

#include "piGL4X_Renderer.h"
#include "piGL4X_Ext.h"
#include "piGL4X_RenderContext.h"
#include "../../libSystem/piStr.h"

//#pragma comment(lib, "opengl32.lib")

namespace piLibs {

typedef struct
{
    unsigned int mProgID;
}piIShader;

typedef struct
{
    unsigned int    mObjectID;
    GLuint64        mHandle;
    bool            mIsResident;
	bool            mIOwnIt;
	piRenderer::TextureInfo     mInfo;
	piRenderer::TextureFilter   mFilter;
	piRenderer::TextureWrap     mWrap;
}piITexture;

typedef struct
{
    unsigned int   mObjectID;
	piRenderer::IndexArrayFormat mIndexArrayType;
}piIVertexArray;

typedef struct
{
    unsigned int mObjectID;
    unsigned int mSize;
	piRenderer::BufferUse  mUse;
}piIBuffer;

typedef struct
{
    unsigned int mObjectID;
}piISampler;

typedef struct
{
    unsigned int mObjectID;
    unsigned int mSamples;
    unsigned int mXres;
    unsigned int mYres;
}piIRTarget;

static int unidades[32] = { GL_TEXTURE0,  GL_TEXTURE1,  GL_TEXTURE2,  GL_TEXTURE3,
    	    	     	    GL_TEXTURE4,  GL_TEXTURE5,  GL_TEXTURE6,  GL_TEXTURE7,
    	    	     	    GL_TEXTURE8,  GL_TEXTURE9,  GL_TEXTURE10, GL_TEXTURE11,
    	    	    	    GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15,
    	    	    	    GL_TEXTURE16, GL_TEXTURE17, GL_TEXTURE18, GL_TEXTURE19,
    	    	    	    GL_TEXTURE20, GL_TEXTURE21, GL_TEXTURE22, GL_TEXTURE23,
    	    	    	    GL_TEXTURE24, GL_TEXTURE25, GL_TEXTURE26, GL_TEXTURE27,
    	    	    	    GL_TEXTURE28, GL_TEXTURE29, GL_TEXTURE30, GL_TEXTURE31 };


static int format2gl( int format, int *bpp, int *mode, int *moInternal, int *mode3, int compressed )
{
    switch( format )
	{
    case piFORMAT_C1I8:        *bpp =  1; *mode = GL_RED;              *moInternal = GL_R8;                   *mode3 = GL_UNSIGNED_BYTE;  if (compressed) *moInternal = GL_COMPRESSED_RED; break;
    case piFORMAT_C2I8:        *bpp =  2; *mode = GL_RG; 	           *moInternal = GL_RG8;                  *mode3 = GL_UNSIGNED_BYTE;  if (compressed) *moInternal = GL_COMPRESSED_RGB; break;
    case piFORMAT_C3I8_RGB:    *bpp =  3; *mode = GL_RGB; 	           *moInternal = GL_RGB8;                 *mode3 = GL_UNSIGNED_BYTE;  if (compressed) *moInternal = GL_COMPRESSED_RGB; break;
    case piFORMAT_C3I8_BGR:    *bpp =  3; *mode = GL_BGR; 	           *moInternal = GL_RGB8;                 *mode3 = GL_UNSIGNED_BYTE;  if (compressed) *moInternal = GL_COMPRESSED_RGB; break;
    case piFORMAT_C4I8_BGRA:   *bpp =  4; *mode = GL_BGRA; 	           *moInternal = GL_RGBA8;                *mode3 = GL_UNSIGNED_BYTE;  if (compressed) *moInternal = GL_COMPRESSED_RGBA; break;
    case piFORMAT_C4I8_RGBA:   *bpp =  4; *mode = GL_RGBA; 	           *moInternal = GL_RGBA8;                *mode3 = GL_UNSIGNED_BYTE;  if (compressed) *moInternal = GL_COMPRESSED_RGBA; break;
    case piFORMAT_C4I8_RGBA_ENDIAN: *bpp =  4; *mode = GL_RGBA; 	   *moInternal = GL_RGBA8;                *mode3 = GL_UNSIGNED_INT_8_8_8_8;  if (compressed) *moInternal = GL_COMPRESSED_RGBA; break;
    case piFORMAT_D24:         *bpp =  4; *mode = GL_DEPTH_COMPONENT;  *moInternal = GL_DEPTH_COMPONENT24;    *mode3 = GL_UNSIGNED_BYTE;  break;
	case piFORMAT_D32:         *bpp =  4; *mode = GL_DEPTH_COMPONENT;  *moInternal = GL_DEPTH_COMPONENT32;    *mode3 = GL_UNSIGNED_BYTE;  break;
	case piFORMAT_D32F:        *bpp =  4; *mode = GL_DEPTH_COMPONENT;  *moInternal = GL_DEPTH_COMPONENT32F;   *mode3 = GL_FLOAT;          break;
    case piFORMAT_C1F16:       *bpp =  2; *mode = GL_RED;              *moInternal = GL_R16F;                 *mode3 = GL_FLOAT;          break;
    case piFORMAT_C2F16:       *bpp =  4; *mode = GL_RG;               *moInternal = GL_RG16F;                *mode3 = GL_FLOAT;          break;
    case piFORMAT_C3F16_RGB:   *bpp =  6; *mode = GL_RGB;              *moInternal = GL_RGB16F;               *mode3 = GL_FLOAT;          break;
    case piFORMAT_C4F16_RGBA:  *bpp =  8; *mode = GL_RGBA;             *moInternal = GL_RGBA16F;              *mode3 = GL_FLOAT;          break;
    case piFORMAT_C3F16_BGR:   *bpp =  6; *mode = GL_BGR;              *moInternal = GL_RGB16F;               *mode3 = GL_FLOAT;          break;
    case piFORMAT_C4F16_BGRA:  *bpp =  8; *mode = GL_BGRA;             *moInternal = GL_RGBA16F;              *mode3 = GL_FLOAT;          break;
    case piFORMAT_C1F32:       *bpp =  4; *mode = GL_RED;              *moInternal = GL_R32F;                 *mode3 = GL_FLOAT;          break;
    case piFORMAT_C4F32_RGBA:  *bpp = 16; *mode = GL_RGBA;             *moInternal = GL_RGBA32F;              *mode3 = GL_FLOAT;          break;
    case piFORMAT_C1I8I:       *bpp =  1; *mode = GL_RED_INTEGER;      *moInternal = GL_R8UI;                 *mode3 = GL_UNSIGNED_BYTE;  break;
    case piFORMAT_C1I16I:      *bpp =  2; *mode = GL_RED_INTEGER;      *moInternal = GL_R16UI;                *mode3 = GL_UNSIGNED_SHORT; break;
    case piFORMAT_C1I32I:      *bpp =  4; *mode = GL_RED_INTEGER;      *moInternal = GL_R32UI;                *mode3 = GL_UNSIGNED_INT;   break;
        
    case piFORMAT_C4I1010102_BGRA: *bpp = 4; *mode = GL_BGRA; 	       *moInternal = GL_RGB10_A2;             *mode3 = GL_UNSIGNED_BYTE; break;
    case piFORMAT_C4I1010102_RGBA: *bpp = 4; *mode = GL_RGBA; 	       *moInternal = GL_RGB10_A2;             *mode3 = GL_UNSIGNED_BYTE; break;
    case piFORMAT_C3I111110_BGRA:  *bpp = 4; *mode = GL_BGRA; 	       *moInternal = GL_R11F_G11F_B10F;       *mode3 = GL_UNSIGNED_BYTE; break;
    case piFORMAT_C3I111110_RGBA:  *bpp = 4; *mode = GL_RGBA; 	       *moInternal = GL_R11F_G11F_B10F;       *mode3 = GL_UNSIGNED_BYTE; break;

    default: return( 0 );
	}
    return( 1 );
}

static uint64_t piTexture_GetMem( const piITexture *me )
{
    int mode, fInternal, mode3, bpp;
    if( !format2gl( me->mInfo.mFormat, &bpp, &mode, &fInternal, &mode3, me->mInfo.mCompressed ) ) return 0;
    return me->mInfo.mXres * me->mInfo.mYres * me->mInfo.mZres * bpp; 
}

//static const unsigned int filter2gl[] = { GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR };
static const unsigned int wrap2gl[]   = { GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE, GL_REPEAT, GL_MIRROR_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT };
static const unsigned int glType[]    = { GL_UNSIGNED_BYTE, GL_FLOAT, GL_INT, GL_DOUBLE, GL_HALF_FLOAT };
static const unsigned int glSizeof[]  = { 1, 4, 4, 8, 2};

//---------------------------------------------

piRendererGL4X::piRendererGL4X():piRenderer()
{
}

piRendererGL4X::~piRendererGL4X()
{
}

static const float verts2f[] = { -1.0f,  1.0f,
                                 -1.0f, -1.0f,
                                  1.0f,  1.0f,
						          1.0f, -1.0f };

static const float verts3f[] = {

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f };


static const float verts3f3f[] = {

-1.0f, -1.0f, -1.0f,  -1.0f, 0.0f, 0.0f,
-1.0f, -1.0f,  1.0f,  -1.0f, 0.0f, 0.0f,
-1.0f,  1.0f, -1.0f,  -1.0f, 0.0f, 0.0f,
-1.0f,  1.0f,  1.0f,  -1.0f, 0.0f, 0.0f,

 1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.0f,
 1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.0f,
 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,
 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 0.0f,

 1.0f, 1.0f,  1.0f,    0.0f, 1.0f, 0.0f,
 1.0f, 1.0f, -1.0f,    0.0f, 1.0f, 0.0f,
-1.0f, 1.0f,  1.0f,    0.0f, 1.0f, 0.0f,
-1.0f, 1.0f, -1.0f,    0.0f, 1.0f, 0.0f,

 1.0f, -1.0f, -1.0f,   0.0f, -1.0f, 0.0f,
 1.0f, -1.0f,  1.0f,   0.0f, -1.0f, 0.0f,
-1.0f, -1.0f, -1.0f,   0.0f, -1.0f, 0.0f,
-1.0f, -1.0f,  1.0f,   0.0f, -1.0f, 0.0f,

-1.0f,  1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
-1.0f, -1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
 1.0f,  1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
 1.0f, -1.0f, 1.0f,    0.0f, 0.0f, 1.0f,

-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, -1.0f,
-1.0f,  1.0f, -1.0f,   0.0f, 0.0f, -1.0f,
 1.0f, -1.0f, -1.0f,   0.0f, 0.0f, -1.0f,
 1.0f,  1.0f, -1.0f,   0.0f, 0.0f, -1.0f };


void CALLBACK piRendererGL4X::DebugLog( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *vme )
{
	piRendererGL4X *me = (piRendererGL4X*)vme;

	if( !me->mReporter ) return;

	const char *sources = "Unknown";
	if( source==GL_DEBUG_SOURCE_API_ARB             ) sources = "API";
	if( source==GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB   ) sources = "OS";
	if( source==GL_DEBUG_SOURCE_SHADER_COMPILER_ARB ) sources = "Shader Compiler";
	if( source==GL_DEBUG_SOURCE_THIRD_PARTY_ARB     ) sources = "Third Party";
	if( source==GL_DEBUG_SOURCE_APPLICATION_ARB     ) sources = "Application";

	const char *types = "Unknown";
	if( type==GL_DEBUG_TYPE_ERROR_ARB               ) types = "Error";
	if( type==GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB ) types = "Deprecated Behavior";
	if( type==GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB  ) types = "Undefined Behavior";
	if( type==GL_DEBUG_TYPE_PORTABILITY_ARB         ) types = "Portability";
	if( type==GL_DEBUG_TYPE_PERFORMANCE_ARB         ) types = "Performance";

	int  severitiID = 0;
	const char *severities = "Unknown";
	if( severity==GL_DEBUG_SEVERITY_HIGH_ARB   ) { severitiID = 2; severities = "High"; }
	if( severity==GL_DEBUG_SEVERITY_MEDIUM_ARB ) { severitiID = 1; severities = "Medium"; }
	if( severity==GL_DEBUG_SEVERITY_LOW_ARB    ) { severitiID = 0; severities = "Low"; }

	if( severity!=GL_DEBUG_SEVERITY_HIGH_ARB ) return;

	char tmp[2048];
    pisprintf( tmp, sizeof(tmp), "Renderer Error, source = \"%s\", type = \"%s\", severity = \"%s\", description = \"%s\"", sources, types, severities, message );


	me->mReporter->Error( tmp, severitiID );
}

void piRendererGL4X::PrintInfo( int showExtensions ) //0=none, 1=inline, 2=mulitline
{
	if( !mReporter ) return;

	char *str = (char*)malloc( 65536 );
    if( !str ) return;

    int nume = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &nume);

    sprintf( str, "OpenGL %s\nGLSL %s\n%s by %s\n%d extensions\n", (const char*)glGetString( GL_VERSION ), (const char*)glGetString( GL_SHADING_LANGUAGE_VERSION ), 
                                                                   (const char*)glGetString( GL_RENDERER ), (const char*)glGetString( GL_VENDOR ), nume );
    if( showExtensions==1 )
    {
        for( int i=0; i<nume; i++ )
        {
            strcat( str, (char const*)oglGetStringi(GL_EXTENSIONS, i) );
            strcat( str, " " );
        }
    }
    else if( showExtensions==2 )
    {
        for( int i=0; i<nume; i++ )
        {
            strcat( str, (char const*)oglGetStringi(GL_EXTENSIONS, i) );
            strcat( str, "\n" );
        }
    }
    mReporter->Info( str );
    free( str );
}

bool piRendererGL4X::Initialize(int id, const void **hwnd, int num, bool disableVSync, bool disableErrors, piRenderReporter *reporter, void *device)
{
    mID = id;
    mBindedTarget = nullptr;
	mBoundVertexArray = nullptr;
	mReporter = reporter;

	mRC = new piGL4X_RenderContext();
    if( !mRC )
        return false;

    if (!mRC->Create(hwnd, num, disableVSync, true, true, disableErrors))
    {
        mRC->Delete();
        return false;
	}

    mRC->Enable();

    mExt = piGL4X_Ext_Init(reporter);
    if( !mExt )
        return false;

	// find useful features
	int nume = 0; glGetIntegerv(GL_NUM_EXTENSIONS, &nume);
	mFeatureVertexViewport = false;
	mFeatureViewportArray  = false;
	for (int i = 0; i<nume; i++)
	{
	    if( strcmp( (const char*)oglGetStringi(GL_EXTENSIONS, i), "GL_ARB_viewport_array"             ) == 0) mFeatureViewportArray  = true;
		if( strcmp( (const char*)oglGetStringi(GL_EXTENSIONS, i), "GL_ARB_shader_viewport_layer_array") == 0) mFeatureVertexViewport = true;
	}


    int maxZMultisample, maxCMultisample, maxGSInvocations, maxTextureUnits, maxVerticesPerPatch, maxViewportDimensions;
    glGetIntegerv( GL_MAX_DEPTH_TEXTURE_SAMPLES, &maxZMultisample );
    glGetIntegerv( GL_MAX_COLOR_TEXTURE_SAMPLES, &maxCMultisample );
    glGetIntegerv( GL_MAX_GEOMETRY_SHADER_INVOCATIONS, &maxGSInvocations );
    glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureUnits );
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxVerticesPerPatch );
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &maxViewportDimensions);


    if( reporter )
    {
    char str[256];
    sprintf( str, "Num Texture Units: %d", maxTextureUnits ); reporter->Info( str );
    sprintf( str, "Max Vertex per Patch: %d", maxVerticesPerPatch); reporter->Info(str);
    sprintf( str, "Max GS invocations: %d", maxGSInvocations); reporter->Info(str);
	sprintf(str, "Max viewport dimensions: %d", maxViewportDimensions); reporter->Info(str);
    }

    //--- texture management ---

    mMemCurrent = 0;
    mMemPeak = 0;
    mNumCurrent = 0;
    mNumPeak = 0;
 

	//////////////

    mVBO[0] = this->CreateBuffer(verts2f,   sizeof(verts2f),   BufferType::Static, BufferUse::Vertex);
    mVBO[1] = this->CreateBuffer(verts3f3f, sizeof(verts3f3f), BufferType::Static, BufferUse::Vertex);
    mVBO[2] = this->CreateBuffer(verts3f,   sizeof(verts3f),   BufferType::Static, BufferUse::Vertex);

    const piRArrayLayout lay0 = { 2 * sizeof(float), 1, 0, { { 2, piRArrayType_Float, false } } };
    const piRArrayLayout lay1 = { 6 * sizeof(float), 2, 0, { { 3, piRArrayType_Float, false }, { 3, piRArrayType_Float, false } } };
    const piRArrayLayout lay2 = { 3 * sizeof(float), 1, 0, { { 3, piRArrayType_Float, false } } };
    const piRArrayLayout lay3 = { 2 * sizeof(float), 1, 0, { { 2, piRArrayType_Float, false } } };
    const piRArrayLayout lay4 = { 4 * sizeof(float), 2, 0, { { 2, piRArrayType_Float, false }, { 2, piRArrayType_Float, false } } };

    mVA[0] = this->CreateVertexArray(1, mVBO[0], &lay0, nullptr, nullptr, nullptr, IndexArrayFormat::UINT_32);
    mVA[1] = this->CreateVertexArray(1, mVBO[1], &lay1, nullptr, nullptr, nullptr, IndexArrayFormat::UINT_32);
    mVA[2] = this->CreateVertexArray(1, mVBO[2], &lay2, nullptr, nullptr, nullptr, IndexArrayFormat::UINT_32);

	// set log
	if( reporter )
	{
		oglDebugMessageCallback( DebugLog, this );
        oglDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE,GL_DONT_CARE, 0, 0, GL_TRUE );
        glEnable( GL_DEBUG_OUTPUT );
        glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
	}

    glDisable(GL_DITHER);
	glDepthFunc(GL_LEQUAL);
    glHint( GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST );
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	PrintInfo(1);

    return true;
}

void *piRendererGL4X::GetContext(void)
{
	return (void*)mRC;
}

bool piRendererGL4X::SupportsFeature(RendererFeature feature)
{
	if (feature == RendererFeature::VIEWPORT_ARRAY)  return mFeatureViewportArray;
	if (feature == RendererFeature::VERTEX_VIEWPORT) return mFeatureVertexViewport;
	return false;
}

piRenderer::API piRendererGL4X::GetAPI(void)
{
	return API::GL;
}

void piRendererGL4X::SetActiveWindow( int id )
{
	mRC->SetActiveWindow( id );
}

void piRendererGL4X::Enable(void)
{
    mRC->Enable();
}
void piRendererGL4X::Disable(void)
{
    mRC->Disable(false);
}


void piRendererGL4X::Report( void )
{
	if( !mReporter ) return;

	mReporter->Begin( mMemCurrent, mMemPeak, mNumCurrent, mNumPeak );
	/*
    if( mMngTexNumCurrent!=0 )
    {
        TextureSlot *slots = (TextureSlot*)mMngTexSlots;
        for( int i=0; i<mMngTexNumCurrent; i++ )
        {
            mReporter->Texture( slots[i].mKey,
                               piTexture_GetMem( slots[i].mTexture ) >> 10L,
                               slots[i].mTexture->mInfo.mFormat, 
                               slots[i].mTexture->mInfo.mCompressed, 
                               slots[i].mTexture->mInfo.mXres, 
                               slots[i].mTexture->mInfo.mYres, 
                               slots[i].mTexture->mInfo.mZres );
        }
    }*/
    mReporter->End();
}


void piRendererGL4X::Deinitialize( void )
{
    //--- texture management ---

    this->DestroyVertexArray(mVA[0]);
    this->DestroyVertexArray(mVA[1]);
    this->DestroyVertexArray(mVA[2]);
    this->DestroyBuffer(mVBO[0]);
    this->DestroyBuffer(mVBO[1]);
    this->DestroyBuffer(mVBO[2]);

    piGL4X_Ext_Free( (NGLEXTINFO*)mExt );

	mRC->Disable( false );
    mRC->Destroy();
    mRC->Delete();
	delete mRC;
}

void piRendererGL4X::SwapBuffers( void )
{
    //glFlush();
	mRC->SwapBuffers();
}

static int check_framebuffer( NGLEXTINFO *mExt )
{                                                           
    GLenum status;                                            
    status = oglCheckFramebufferStatus(GL_FRAMEBUFFER); 
    switch( status ) 
        {
        case GL_FRAMEBUFFER_COMPLETE:                       
            break;                                                
        case GL_FRAMEBUFFER_UNSUPPORTED:                    
            break;                                                
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            return 0;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            return 0;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            return 0;
        default:                                                
            return 0;
        }
    if( status!=GL_FRAMEBUFFER_COMPLETE )
        return 0;
    return 1;
}


void piRendererGL4X::SetShadingSamples( int shadingSamples )
{
    piIRTarget *rt = (piIRTarget*)mBindedTarget;

    if( shadingSamples>1 && rt!=NULL )
    {
        glEnable( GL_SAMPLE_SHADING );
        oglMinSampleShading( (float)shadingSamples/(float)rt->mSamples );
    }
    else
    {
        glDisable( GL_SAMPLE_SHADING );
    }

}

piRTarget piRendererGL4X::CreateRenderTarget( piTexture vtex0, piTexture vtex1, piTexture vtex2, piTexture vtex3, piTexture zbuf )
{
	const piITexture *tex[4] = { (piITexture*)vtex0, (piITexture*)vtex1, (piITexture*)vtex2, (piITexture*)vtex3 };
    const piITexture *zbu = (piITexture*)zbuf;

    piIRTarget *me = (piIRTarget*)malloc( sizeof(piIRTarget) );
    if( !me ) 
        return nullptr;

    me->mObjectID = 0;

    bool hasLayers = false;

    bool found = false;
    for( int i=0; i<4; i++ )
    {
        if( !tex[i] ) continue;
        me->mSamples = tex[i]->mInfo.mMultisample;
        me->mXres = tex[i]->mInfo.mXres;
        me->mYres = tex[i]->mInfo.mYres;
        //hasLayers = (tex[i]->mInfo.mType == piTEXTURE_CUBE);
        //hasLayers = (tex[i]->mInfo.mType == piTEXTURE_2D_ARRAY);
        found = true;
        break;
    }
    if( !found )
    {
        if( zbu )
        {
        me->mSamples = zbu->mInfo.mMultisample;
        me->mXres = zbu->mInfo.mXres;
        me->mYres = zbu->mInfo.mYres;
        found = true;
        }
    }

    if (!found) return nullptr;


	oglCreateFramebuffers(1, (GLuint*)&me->mObjectID);


    if( zbu )
    {
        if (hasLayers )
            oglNamedFramebufferTextureLayer(me->mObjectID, GL_DEPTH_ATTACHMENT, zbu->mObjectID, 0, 0);
        else
            oglNamedFramebufferTexture(me->mObjectID, GL_DEPTH_ATTACHMENT, zbu->mObjectID, 0);
    }
    else
    {
        if (hasLayers)
            oglNamedFramebufferTextureLayer(me->mObjectID, GL_DEPTH_ATTACHMENT, 0, 0, 0);
        else
            oglNamedFramebufferTexture(me->mObjectID, GL_DEPTH_ATTACHMENT, 0, 0);
    }

    GLenum       mMRT[4];
    int          mNumMRT = 0;
	for( int i=0; i<4; i++ )
	{
		if( tex[i] )
		{
            if (hasLayers)
                oglNamedFramebufferTextureLayer(me->mObjectID, GL_COLOR_ATTACHMENT0 + i, tex[i]->mObjectID, 0, 0);
            else
                oglNamedFramebufferTexture(me->mObjectID, GL_COLOR_ATTACHMENT0 + i, tex[i]->mObjectID, 0);
            mMRT[i] = GL_COLOR_ATTACHMENT0 + i;
			mNumMRT++;
		}
		else
		{
            if (hasLayers)
                oglNamedFramebufferTextureLayer(me->mObjectID, GL_COLOR_ATTACHMENT0 + i, 0, 0, 0);
            else
                oglNamedFramebufferTexture(me->mObjectID, GL_COLOR_ATTACHMENT0 + i, 0, 0);
            mMRT[i] = 0;
		}
	}

	oglNamedFramebufferDrawBuffers(me->mObjectID, mNumMRT, mMRT);


    GLenum st = oglCheckNamedFramebufferStatus(me->mObjectID, GL_FRAMEBUFFER);
	if (st != GL_FRAMEBUFFER_COMPLETE)
        return nullptr;

    return me;
}

void piRendererGL4X::DestroyRenderTarget( piRTarget obj )
{
    piIRTarget *me = (piIRTarget*)obj;

    oglDeleteFramebuffers( 1, (GLuint*)&me->mObjectID );
}

void piRendererGL4X::RenderTargetSampleLocations(piRTarget vdst, const float *locations )
{
/*
    const piIRTarget *dst = (piIRTarget*)vdst;
    if( locations==nullptr )
    {
        oglNamedFramebufferParameteri(dst->mObjectID, GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_ARB, 0);
    }
    else
    {
        oglNamedFramebufferParameteri(dst->mObjectID, GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_ARB, 1);
        oglNamedFramebufferSampleLocationsfv(dst->mObjectID, 0, dst->mSamples, locations);
    }
*/
}

void piRendererGL4X::RenderTargetGetDefaultSampleLocation(piRTarget vdst, const int id, float *location)
{
    const piIRTarget *dst = (piIRTarget*)vdst;
    oglGetMultisamplefv( GL_SAMPLE_LOCATION_ARB, id, location);
}

void piRendererGL4X::BlitRenderTarget( piRTarget vdst, piRTarget vsrc, bool color, bool depth )
{
    const piIRTarget *src = (piIRTarget*)vsrc;
    const piIRTarget *dst = (piIRTarget*)vdst;

    int flag = 0;
    if( color ) flag += GL_COLOR_BUFFER_BIT;
    if( depth ) flag += GL_DEPTH_BUFFER_BIT;

	const GLenum mMRT[1] = { GL_COLOR_ATTACHMENT0 };
	oglNamedFramebufferDrawBuffers(dst->mObjectID, 1, mMRT);

	oglBlitNamedFramebuffer( src->mObjectID, dst->mObjectID,
	                         0, 0, dst->mXres, dst->mYres,
                             0, 0, dst->mXres, dst->mYres,
                             flag, GL_NEAREST );
}


bool piRendererGL4X::SetRenderTarget( piRTarget obj )
{
    if( obj==NULL )
    {
        mBindedTarget = NULL;
		oglBindFramebuffer( GL_FRAMEBUFFER, 0 );
		const GLenum zeros[4] = { 0, 0, 0, 0 };// { GL_NONE, GL_NONE, GL_NONE, GL_NONE };// segun la especificacion... 
		oglDrawBuffers(4, zeros);
	    glDrawBuffer(GL_BACK);
		//glReadBuffer(GL_BACK);
        //glDisable(GL_MULTISAMPLE);
    }
    else
    {
		piIRTarget *me = (piIRTarget*)obj;
		mBindedTarget = obj;
		oglBindFramebuffer( GL_FRAMEBUFFER, me->mObjectID );
        //glEnable(GL_FRAMEBUFFER_SRGB);
        if( me->mSamples>1 )
        {
            glEnable(GL_MULTISAMPLE); 
        }
        else
        {
            glDisable(GL_MULTISAMPLE);
        }
	}

    return true;
}



void piRendererGL4X::SetViewport( int id, const int *vp )
{
    //glViewport( vp[0], vp[1], vp[2], vp[3] );
    oglViewportIndexedf(id, float(vp[0]), float(vp[1]), float(vp[2]), float(vp[3]) );
}

void piRendererGL4X::SetViewports(int num, const float *viewports) // x,y,w,h,zmin,zmax // 0.0, 0.0, 800.0, 600.0, 0.0, 1.0
{
	float vp[4 * 16];
	for (int i = 0; i < num; i++)
	{
		vp[4 * i + 0] = viewports[6 * i + 0];
		vp[4 * i + 1] = viewports[6 * i + 1];
		vp[4 * i + 2] = viewports[6 * i + 2];
		vp[4 * i + 3] = viewports[6 * i + 3];
	}
	//oglViewportArrayv(0, num, vp);
}

void piRendererGL4X::GetViewports(int *num, float *viewports) // x,y,w,h,zmin,zmax
{
}


//===========================================================================================================================================
static int ilog2i(int x)
{
    if (x >= 32768) return 16;
    if (x >= 16384) return 15;
    if (x >= 8192) return 14;
    if (x >= 4096) return 13;
    if (x >= 2048) return 12;
    if (x >= 1024) return 11;
    if (x >= 512) return 10;
    if (x >= 256) return 9;
    if (x >= 128) return 8;
    if (x >= 64) return 7;
    if (x >= 32) return 6;
    if (x >= 16) return 5;
    if (x >= 8) return 4;
    if (x >= 4) return 3;
    if (x >= 2) return 2;
    if (x >= 1) return 1;
    return 0;
}



piTexture piRendererGL4X::CreateTextureFromID(unsigned int id, TextureFilter filter )
{
	piITexture *me = (piITexture*)malloc(sizeof(piITexture));
	if (!me)
		return nullptr;

	me->mObjectID = id;
	//me->mInfo = *info;
	me->mFilter = filter;
	//me->mWrap = rwrap;
	me->mIOwnIt = false;
	me->mHandle = 0;
	me->mIsResident = false;

	mNumCurrent++;

    return me;
}

piTexture piRendererGL4X::CreateTexture( const wchar_t *key, const TextureInfo *info, TextureFilter filter, TextureWrap wrap1, float aniso, void *buffer )
{
	int moFormat, moInternal, moType, bpp;

	if (!format2gl(info->mFormat, &bpp, &moFormat, &moInternal, &moType, info->mCompressed))
		return nullptr;

	piITexture *me = (piITexture*)malloc(sizeof(piITexture));
	if (!me)
		return nullptr;

	me->mHandle = 0;
	me->mIsResident = false;
	me->mIOwnIt = true;
	me->mInfo = *info;
	me->mFilter = filter;
	me->mWrap = wrap1;

	const int wrap = wrap2gl[static_cast<int>(wrap1)];

	if (info->mType == piRenderer::TextureType::T2D)
	{
		if (info->mMultisample>1)
		{
			oglCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &me->mObjectID);
			oglTextureStorage2DMultisample(me->mObjectID, info->mMultisample, moInternal, info->mXres, info->mYres, GL_FALSE);
		}
		else
		{
			oglCreateTextures(GL_TEXTURE_2D, 1, &me->mObjectID);
			switch (filter)
			{
			case piRenderer::TextureFilter::NONE:
				if (moInternal == GL_DEPTH_COMPONENT24)
				{
					oglTextureStorage2D(me->mObjectID, 1, GL_DEPTH_COMPONENT24, info->mXres, info->mYres);
					oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_NONE);
				}
				else
				{
					oglTextureStorage2D(me->mObjectID, 1, moInternal, info->mXres, info->mYres);
					if (buffer)
					{
						const int rowsize = info->mXres*bpp;
						if ((rowsize & 3) == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 4); else glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
						oglTextureSubImage2D(me->mObjectID, 0, 0, 0, info->mXres, info->mYres, moFormat, moType, buffer);
					}
				}
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, wrap);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, wrap);
				break;

			case piRenderer::TextureFilter::LINEAR:
				if (moInternal == GL_DEPTH_COMPONENT24)
				{
					oglTextureStorage2D(me->mObjectID, 1, GL_DEPTH_COMPONENT24, info->mXres, info->mYres);
					oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_NONE);
				}
				else
				{
					oglTextureStorage2D(me->mObjectID, 1, moInternal, info->mXres, info->mYres);
					if (buffer)
					{
						const int rowsize = info->mXres*bpp;
						if ((rowsize & 3) == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 4); else glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
						oglTextureSubImage2D(me->mObjectID, 0, 0, 0, info->mXres, info->mYres, moFormat, moType, buffer);
					}
				}
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, wrap);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, wrap);
				{
					//const GLint swizzleMask[] = {GL_ALPHA, GL_RED, GL_GREEN, GL_BLUE};
					//oglTextureParameteriv(me->mObjectID, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
				}
				break;

			case piRenderer::TextureFilter::PCF:
				if (moInternal == GL_DEPTH_COMPONENT24)
				{
					oglTextureStorage2D(me->mObjectID, 1, GL_DEPTH_COMPONENT24, info->mXres, info->mYres);
					oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
					oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
				}
				else
				{
					return nullptr;
					//oglTextureStorage2D(me->mObjectID, 1, moInternal, info->mXres, info->mYres);
					//if (buffer) oglTextureSubImage2D(me->mObjectID, 0, 0, 0, info->mXres, info->mYres, mode, mode3, buffer);
				}
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, wrap);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, wrap);
				break;

			case piRenderer::TextureFilter::MIPMAP:
			{
				const int numMipmaps = ilog2i(info->mXres);
				oglTextureStorage2D(me->mObjectID, numMipmaps, moInternal, info->mXres, info->mYres);
				if (buffer)
				{
					const int rowsize = info->mXres*bpp;
					if ((rowsize & 3) == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 4); else glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
					oglTextureSubImage2D(me->mObjectID, 0, 0, 0, info->mXres, info->mYres, moFormat, moType, buffer);
				}
				oglGenerateTextureMipmap(me->mObjectID);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, numMipmaps);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, wrap);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, wrap);
				if (aniso>1.0001f)
					oglTextureParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, aniso);
				break;
			}
			case piRenderer::TextureFilter::NONE_MIPMAP:
			{
				const int numMipmaps = ilog2i(info->mXres);
				oglTextureStorage2D(me->mObjectID, numMipmaps, moInternal, info->mXres, info->mYres);
				if (buffer)
				{
					const int rowsize = info->mXres*bpp;
					if ((rowsize & 3) == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 4); else glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
					oglTextureSubImage2D(me->mObjectID, 0, 0, 0, info->mXres, info->mYres, moFormat, moType, buffer);
				}
				oglGenerateTextureMipmap(me->mObjectID);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, numMipmaps);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, wrap);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, wrap);
				if (aniso>1.0001f)
					oglTextureParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, aniso);
				break;
			}
			}
		}
	}
	else if (info->mType == piRenderer::TextureType::T3D)
	{
		oglCreateTextures(GL_TEXTURE_3D, 1, &me->mObjectID);
		if (filter != piRenderer::TextureFilter::MIPMAP)
		{
			oglTextureStorage3D(me->mObjectID, 1, moInternal, info->mXres, info->mYres, info->mZres);
			if (buffer) oglTextureSubImage3D(me->mObjectID, 0, 0, 0, 0, info->mXres, info->mYres, info->mZres, moFormat, moType, buffer);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, 0);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else
		{
			const int numMipmaps = ilog2i(info->mXres);
			oglTextureStorage3D(me->mObjectID, numMipmaps, moInternal, info->mXres, info->mYres, info->mZres);
			if (buffer) oglTextureSubImage3D(me->mObjectID, 0, 0, 0, 0, info->mXres, info->mYres, info->mZres, moFormat, moType, buffer);
			oglGenerateTextureMipmap(me->mObjectID);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, numMipmaps);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_R, wrap);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, wrap);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, wrap);
		if (aniso>1.0001f)
			oglTextureParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, aniso);
	}
	else if (info->mType == piRenderer::TextureType::TCUBE)
	{
		if (filter == piRenderer::TextureFilter::MIPMAP)
		{
			const int numMipmaps = ilog2i(info->mXres);
			oglCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &me->mObjectID);
			oglTextureStorage2D(me->mObjectID, 1, moInternal, info->mXres, info->mYres);
			if (buffer)
			{
				oglTextureSubImage3D(me->mObjectID, 0, 0, 0, 0, info->mXres, info->mYres, 6, moFormat, moType, buffer);
				oglGenerateTextureMipmap(me->mObjectID);
			}
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, numMipmaps);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			oglCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &me->mObjectID);
			oglTextureStorage2D(me->mObjectID, 1, moInternal, info->mXres, info->mYres);
			if (buffer) oglTextureSubImage3D(me->mObjectID, 0, 0, 0, 0, info->mXres, info->mYres, 6, moFormat, moType, buffer);
		}
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_CUBE_MAP_SEAMLESS, GL_TRUE);
		oglTextureParameterf(me->mObjectID, GL_TEXTURE_MIN_LOD, -1000.f);
		oglTextureParameterf(me->mObjectID, GL_TEXTURE_MAX_LOD, 1000.f);
		oglTextureParameterf(me->mObjectID, GL_TEXTURE_LOD_BIAS, 0.0f);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		oglTextureParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, aniso);
	}
	else if (info->mType == piRenderer::TextureType::TCUBE_ARRAY)
	{
		if (filter == piRenderer::TextureFilter::MIPMAP)
		{
			const int numMipmaps = ilog2i(info->mXres);
			oglCreateTextures(GL_TEXTURE_CUBE_MAP_ARRAY, 1, &me->mObjectID);
			oglTextureStorage3D(me->mObjectID, numMipmaps, moInternal, info->mXres, info->mYres, 6);
			if (buffer)
			{
				oglTextureSubImage3D(me->mObjectID, 0, 0, 0, 0, info->mXres, info->mYres, 6, moFormat, moType, buffer);
				oglGenerateTextureMipmap(me->mObjectID);
			}
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, numMipmaps);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			oglCreateTextures(GL_TEXTURE_CUBE_MAP_ARRAY, 1, &me->mObjectID);
			oglTextureStorage3D(me->mObjectID, 1, moInternal, info->mXres, info->mYres, 6);
			if (buffer)
				oglTextureSubImage3D(me->mObjectID, 0, 0, 0, 0, info->mXres, info->mYres, 6, moFormat, moType, buffer);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, 0);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_CUBE_MAP_SEAMLESS, GL_TRUE);
		oglTextureParameterf(me->mObjectID, GL_TEXTURE_MIN_LOD, -1000.f);
		oglTextureParameterf(me->mObjectID, GL_TEXTURE_MAX_LOD, 1000.f);
		oglTextureParameterf(me->mObjectID, GL_TEXTURE_LOD_BIAS, 0.0f);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		oglTextureParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, aniso);
	}
	else if (info->mType == piRenderer::TextureType::T2D_ARRAY)
	{

		if (info->mMultisample>1)
		{
			oglCreateTextures(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 1, &me->mObjectID);
			oglTextureStorage3DMultisample(me->mObjectID, info->mMultisample, moInternal, info->mXres, info->mYres, info->mZres, GL_FALSE);
		}
		else
		{
			oglCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &me->mObjectID);
			oglTextureStorage3D(me->mObjectID, 1, moInternal, info->mXres, info->mYres, info->mZres);
			if (buffer) oglTextureSubImage3D(me->mObjectID, 0, 0, 0, 0, info->mXres, info->mYres, info->mZres, moFormat, moType, buffer);

			if (filter == piRenderer::TextureFilter::PCF)
			{
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			else if (filter == piRenderer::TextureFilter::NONE)
			{
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}
			else
			{
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_BASE_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAX_LEVEL, 0);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				oglTextureParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_R, wrap);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_S, wrap);
			oglTextureParameteri(me->mObjectID, GL_TEXTURE_WRAP_T, wrap);
		}

	}

	me->mHandle = oglGetTextureHandle(me->mObjectID);

    mMemCurrent += piTexture_GetMem( me );
    mNumCurrent += 1;
    if( mNumCurrent>mNumPeak ) mNumPeak = mNumCurrent;
    if( mMemCurrent>mMemPeak ) mMemPeak = mMemCurrent;

    return me;
}


void piRendererGL4X::ComputeMipmaps( piTexture vme )
{
    piITexture *me = (piITexture*)vme;		
    if( me->mFilter!= piRenderer::TextureFilter::MIPMAP ) return;

    oglGenerateTextureMipmap(me->mObjectID);
}


void piRendererGL4X::DestroyTexture( piTexture vme )
{
	piITexture *me = (piITexture*)vme;
	
	if( me->mIOwnIt)
	{
		glDeleteTextures(1, &me->mObjectID);
		mMemCurrent -= piTexture_GetMem(me);
	}
	mNumCurrent--;

	free(me);
}


void piRendererGL4X::AttachTextures( int num, 
                                     piTexture vt0, piTexture vt1, piTexture vt2, piTexture vt3, piTexture vt4, piTexture vt5, piTexture vt6, piTexture vt7,
                                     piTexture vt8, piTexture vt9, piTexture vt10, piTexture vt11, piTexture vt12, piTexture vt13, piTexture vt14, piTexture vt15 )
{
    piITexture *t[16] = { (piITexture*)vt0, (piITexture*)vt1, (piITexture*)vt2, (piITexture*)vt3, (piITexture*)vt4, (piITexture*)vt5, (piITexture*)vt6, (piITexture*)vt7,
                          (piITexture*)vt8, (piITexture*)vt9, (piITexture*)vt10, (piITexture*)vt11, (piITexture*)vt12, (piITexture*)vt13, (piITexture*)vt14, (piITexture*)vt15 };

	GLuint texIDs[16];
    for (int i = 0; i<num; i++)
        texIDs[i] = (t[i]) ? t[i]->mObjectID : 0;
    
    oglBindTextures( 0, num, texIDs );
}



void piRendererGL4X::DettachTextures( void )
{
#if 0
    GLuint texIDs[6] = { 0, 0, 0, 0, 0, 0 };
    oglBindTextures( 0, 6, texIDs );
#endif
}

void piRendererGL4X::AttachImage(int unit, piTexture texture, int level, bool layered, int layer, piTextureFormat format)
{
    int mode, moInternal, mode3, bpp;

    if (!format2gl(format, &bpp, &mode, &moInternal, &mode3, false))
        return;

    oglBindImageTexture(unit, ((piITexture*)texture)->mObjectID, level, layered, layer, GL_READ_WRITE, moInternal);
}

void piRendererGL4X::ClearTexture( piTexture vme, int level, const void *data )
{
    piITexture *me = (piITexture*)vme;		

    int mode, mode2, mode3, bpp;
    if( !format2gl( me->mInfo.mFormat, &bpp, &mode, &mode2, &mode3, me->mInfo.mCompressed ) )
        return;

    oglActiveTexture( unidades[0] );
    if( me->mInfo.mType==piRenderer::TextureType::T2D )
    {
		oglClearTexImage( me->mObjectID, level, mode, mode3, data );
    }
    else if( me->mInfo.mType== piRenderer::TextureType::T2D_ARRAY )
    {
        oglClearTexSubImage( me->mObjectID, level, 0, 0, 0, me->mInfo.mXres, me->mInfo.mYres, me->mInfo.mZres, mode, mode3, data );
    }
}

void piRendererGL4X::UpdateTexture( piTexture vme, int x0, int y0, int z0, int xres, int yres, int zres, const void *buffer )
{
    piITexture *me = (piITexture*)vme;		

    int fFormat, fInternal, fType, bpp;
    if( !format2gl( me->mInfo.mFormat, &bpp, &fFormat, &fInternal, &fType, me->mInfo.mCompressed ) )
        return;

    if( me->mInfo.mType== piRenderer::TextureType::T2D )
    {
	    oglTextureSubImage2D( me->mObjectID, 0, x0, y0, xres, yres, fFormat, fType, buffer);
	    if (me->mFilter == piRenderer::TextureFilter::MIPMAP)
		    oglGenerateTextureMipmap(me->mObjectID);
    }
    else if( me->mInfo.mType== piRenderer::TextureType::T2D_ARRAY )
    {
	    oglTextureSubImage3D( me->mObjectID, 0, x0, y0, z0, xres, yres, zres, fFormat, fType, buffer);
    }
}

void piRendererGL4X::MakeResident( piTexture vme )
{
    piITexture *me = (piITexture*)vme;		
    if( me->mIsResident ) return;
    oglMakeTextureHandleResident( me->mHandle );
    me->mIsResident = true;
}
void piRendererGL4X::MakeNonResident( piTexture vme )
{
    piITexture *me = (piITexture*)vme;		
    if( !me->mIsResident ) return;
    oglMakeTextureHandleNonResident( me->mHandle );
    me->mIsResident = false;
}
uint64_t piRendererGL4X::GetTextureHandle( piTexture vme )
{
    piITexture *me = (piITexture*)vme;		
    return me->mHandle;
}


//==================================================


piSampler piRendererGL4X::CreateSampler(TextureFilter filter, TextureWrap wrap, float maxAnisotrop)
{
    piISampler *me = (piISampler*)malloc( sizeof(piISampler) );
    if( !me ) 
        return nullptr;

    oglGenSamplers( 1, &me->mObjectID );
    //oglCreateSamplers( 1, &me->mObjectID );

    int glwrap = wrap2gl[ static_cast<int>(wrap) ];

    if (filter == piRenderer::TextureFilter::NONE)
    {
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MIN_LOD, -1000.f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MAX_LOD, 1000.f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_LOD_BIAS, 0.0f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, maxAnisotrop);
    }
    else if (filter == piRenderer::TextureFilter::LINEAR)
    {
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        oglTextureParameteri(me->mObjectID, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MIN_LOD, -1000.f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MAX_LOD, 1000.f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_LOD_BIAS, 0.0f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, maxAnisotrop);
    }
    else if (filter == piRenderer::TextureFilter::MIPMAP)
    {
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MIN_LOD, -1000.f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MAX_LOD, 1000.f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_LOD_BIAS, 0.0f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, maxAnisotrop);
    }
    else // if (filter == piRenderer::TextureFilter::PCF)
    {
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        oglSamplerParameteri(me->mObjectID, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MIN_LOD, -1000.f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MAX_LOD, 1000.f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_LOD_BIAS, 0.0f);
        oglSamplerParameterf(me->mObjectID, GL_TEXTURE_MAX_ANISOTROPY, maxAnisotrop);
    }

	oglSamplerParameteri( me->mObjectID, GL_TEXTURE_WRAP_R, glwrap );
	oglSamplerParameteri( me->mObjectID, GL_TEXTURE_WRAP_S, glwrap );
	oglSamplerParameteri( me->mObjectID, GL_TEXTURE_WRAP_T, glwrap );

    return me;
}

void piRendererGL4X::DestroySampler( piSampler obj )
{
    piISampler *me = (piISampler*)obj;
    oglDeleteSamplers( 1, &me->mObjectID );
}


void piRendererGL4X::AttachSamplers(int num, piSampler vt0, piSampler vt1, piSampler vt2, piSampler vt3, piSampler vt4, piSampler vt5, piSampler vt6, piSampler vt7)
{
    piISampler *t[8] = { (piISampler*)vt0, (piISampler*)vt1, (piISampler*)vt2, (piISampler*)vt3, (piISampler*)vt4, (piISampler*)vt5, (piISampler*)vt6, (piISampler*)vt7 };

    GLuint texIDs[8];
    for( int i=0; i<num; i++ )
    {
        texIDs[i] = ( t[i] ) ? t[i]->mObjectID : 0;
    }
    oglBindSamplers( 0, num, texIDs );
}

void piRendererGL4X::DettachSamplers( void )
{
    GLuint texIDs[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    oglBindSamplers( 0, 8, texIDs );
}

//===========================================================================================================================================
static const char *versionStr = "#version 440 core\n";
 
static bool createOptionsString(char *buffer, const int bufferLength, const piShaderOptions *options )
{
    const int num = options->mNum;
    if (num>64) return false;
    
    int ptr = 0;
    for (int i = 0; i<num; i++)
    {
        int offset = pisprintf(buffer + ptr, bufferLength - ptr, "#define %s %d\n", options->mOption[i].mName, options->mOption[i].mValue);
        ptr += offset;
    }
    buffer[ptr] = 0;

    return true;
}

piShader piRendererGL4X::CreateShader( const piShaderOptions *options, const char *vs, const char *cs, const char *es, const char *gs, const char *fs, char *error)
{
    piIShader *me = (piIShader*)malloc( sizeof(piIShader) );
    if( !me ) 
        return nullptr;

	//glEnable( GL_DEPTH_TEST );

    const char *vtext = vs;
    const char *ctext = cs;
    const char *etext = es;
    const char *gtext = gs;
    const char *ftext = fs;

    me->mProgID = oglCreateProgram();

    const int mVertShaderID = vs?oglCreateShader( GL_VERTEX_SHADER ):-1;
	const int mCtrlShaderID = cs?oglCreateShader( GL_TESS_CONTROL_SHADER ):-1;
	const int mEvalShaderID = es?oglCreateShader( GL_TESS_EVALUATION_SHADER ):-1;
	const int mGeomShaderID = gs?oglCreateShader( GL_GEOMETRY_SHADER ):-1;
    const int mFragShaderID = fs?oglCreateShader( GL_FRAGMENT_SHADER ):-1;

    char optionsStr[80*64] = { 0 };
    if (options != nullptr) 
    {
        if( !createOptionsString(optionsStr, 80*64, options) )
            return nullptr;
    }

    const GLchar *vstrings[3] = { versionStr, optionsStr, vtext };
    const GLchar *cstrings[3] = { versionStr, optionsStr, ctext };
    const GLchar *estrings[3] = { versionStr, optionsStr, etext };
    const GLchar *gstrings[3] = { versionStr, optionsStr, gtext };
    const GLchar *fstrings[3] = { versionStr, optionsStr, ftext };

    if( vs ) oglShaderSource(mVertShaderID, 3, vstrings, 0);
    if( cs ) oglShaderSource(mCtrlShaderID, 3, cstrings, 0);
    if( es ) oglShaderSource(mEvalShaderID, 3, estrings, 0);
    if( gs ) oglShaderSource(mGeomShaderID, 3, gstrings, 0);
    if( fs ) oglShaderSource(mFragShaderID, 3, fstrings, 0);


	int result = 0;

	//--------
	if( vs )
	{
		oglCompileShader( mVertShaderID );
		oglGetShaderiv( mVertShaderID, GL_COMPILE_STATUS, &result );
		if( !result )
        {
		    if( error ) { error[0]='V'; error[1]='S'; error[2]=':'; oglGetShaderInfoLog( mVertShaderID, 1024, NULL, (char *)(error+3) ); }
            return nullptr;
        }
	}
    //--------
	if( cs )
	{
		oglCompileShader( mCtrlShaderID );
		oglGetShaderiv( mCtrlShaderID, GL_COMPILE_STATUS, &result );
		if( !result )
        {
		    if( error ) { error[0]='C'; error[1]='S'; error[2]=':'; oglGetShaderInfoLog( mCtrlShaderID, 1024, NULL, (char *)(error+3) ); }
            return nullptr;
        }
	}
    //--------
	if( es )
	{
		oglCompileShader( mEvalShaderID );
		oglGetShaderiv( mEvalShaderID, GL_COMPILE_STATUS, &result );
		if( !result )
        {
		    if( error ) { error[0]='E'; error[1]='S'; error[2]=':'; oglGetShaderInfoLog( mEvalShaderID, 1024, NULL, (char *)(error+3) ); }
            return nullptr;
        }
	}
    //--------
	if( gs )
	{
		oglCompileShader( mGeomShaderID );
		oglGetShaderiv( mGeomShaderID, GL_COMPILE_STATUS, &result );
		if( !result )
        {
		    if( error ) { error[0]='G'; error[1]='S'; error[2]=':'; oglGetShaderInfoLog( mGeomShaderID, 1024, NULL, (char *)(error+3) ); }
            return nullptr;
        }
	}
    //--------
	if( fs )
	{
		oglCompileShader( mFragShaderID );
		oglGetShaderiv( mFragShaderID, GL_COMPILE_STATUS, &result );
		if( !result )
        {
		    if( error ) { error[0]='F'; error[1]='S'; error[2]=':'; oglGetShaderInfoLog( mFragShaderID, 1024, NULL, (char *)(error+3) ); }
            return nullptr;
        }
	}
    //--------
    if( vs ) oglAttachShader( me->mProgID, mVertShaderID );
    if( cs ) oglAttachShader( me->mProgID, mCtrlShaderID );
    if( es ) oglAttachShader( me->mProgID, mEvalShaderID );
    if( gs ) oglAttachShader( me->mProgID, mGeomShaderID );
    if( fs ) oglAttachShader( me->mProgID, mFragShaderID );

	//--------

    oglLinkProgram( me->mProgID );
    oglGetProgramiv( me->mProgID, GL_LINK_STATUS, &result );
    if( !result )
    {
	    if( error ) { error[0]='L'; error[1]='I'; error[2]=':'; oglGetProgramInfoLog( me->mProgID, 1024, NULL, (char *)(error+3) ); }
        return nullptr;
    }

    if( vs ) oglDeleteShader( mVertShaderID );
    if( cs ) oglDeleteShader( mCtrlShaderID );
    if( es ) oglDeleteShader( mEvalShaderID );
    if( gs ) oglDeleteShader( mGeomShaderID );
    if( fs ) oglDeleteShader( mFragShaderID );

    return (piShader)me;
}

piShader piRendererGL4X::CreateShaderBinary(const piShaderOptions *options, const uint8_t *vs, const int vs_len, const uint8_t *cs, const int cs_len, const uint8_t *es, const int es_len, const uint8_t *gs, const int gs_len, const uint8_t *fs, const int fs_len, char *error)
{
	return nullptr;
}

piShader piRendererGL4X::CreateCompute(const piShaderOptions *options, const char *cs, char *error)
{
    if (!cs)
        return nullptr;

    piIShader *me = (piIShader*)malloc(sizeof(piIShader));
    if (!me)
        return nullptr;

    const char *ctext = cs;

    char optionsStr[80 * 64] = { 0 };
    if (options != nullptr) createOptionsString(optionsStr, 80*64, options);

    me->mProgID = oglCreateProgram();
    
    const int mShaderID = oglCreateShader(GL_COMPUTE_SHADER);

    const GLchar *vstrings[3] = { versionStr, optionsStr, ctext };

    oglShaderSource(mShaderID, 3, vstrings, 0);


    int result = 0;

    //--------
    oglCompileShader(mShaderID);
    oglGetShaderiv(mShaderID, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        if (error) { error[0] = 'C'; error[1] = 'S'; error[2] = ':'; oglGetShaderInfoLog(mShaderID, 1024, NULL, (char *)(error + 3)); }
        return(0);
    }

    //--------
    oglAttachShader(me->mProgID, mShaderID);

    //--------

    oglLinkProgram(me->mProgID);
    oglGetProgramiv(me->mProgID, GL_LINK_STATUS, &result);
    if (!result)
    {
        if (error) { error[0] = 'L'; error[1] = 'I'; error[2] = ':'; oglGetProgramInfoLog(me->mProgID, 1024, NULL, (char *)(error + 3)); }
        return(0);
    }

    oglDeleteShader(mShaderID);

    return (piShader)me;
}


void piRendererGL4X::DestroyShader( piShader vme )
{
    piIShader *me = (piIShader *)vme;
	oglDeleteProgram( me->mProgID );
	free(me);
}

void piRendererGL4X::AttachShader( piShader vme )
{
    piIShader *me = (piIShader *)vme;

    //if (me->mProgID==this->mB

	oglUseProgram( me->mProgID );
    //glEnable( GL_VERTEX_PROGRAM_POINT_SIZE );
}

void piRendererGL4X::DettachShader( void )
{
    //glDisable(GL_VERTEX_PROGRAM_POINT_SIZE); 
    oglUseProgram( 0 );
}

void piRendererGL4X::AttachShaderConstants(piBuffer obj, int unit)
{
    piIBuffer *me = (piIBuffer *)obj;
    oglBindBufferRange(GL_UNIFORM_BUFFER, unit, me->mObjectID, 0, me->mSize);
}

void piRendererGL4X::AttachShaderBuffer(piBuffer obj, int unit)
{
    piIBuffer *me = (piIBuffer *)obj;
    oglBindBufferBase(GL_SHADER_STORAGE_BUFFER, unit, me->mObjectID );
}

void piRendererGL4X::DettachShaderBuffer(int unit)
{
    oglBindBufferBase(GL_SHADER_STORAGE_BUFFER, unit, 0);
}

void piRendererGL4X::AttachAtomicsBuffer(piBuffer obj, int unit)
{
    piIBuffer *me = (piIBuffer *)obj;
    oglBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, unit, me->mObjectID);
}

void piRendererGL4X::DettachAtomicsBuffer(int unit)
{
    oglBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, unit, 0);
}

void piRendererGL4X::SetShaderConstant4F(const unsigned int pos, const float *value, int num)
{
	oglUniform4fv(pos,num,value);
}
void piRendererGL4X::SetShaderConstant3F(const unsigned int pos, const float *value, int num)
{
	oglUniform3fv(pos,num,value);
}
void piRendererGL4X::SetShaderConstant2F(const unsigned int pos, const float *value, int num)
{
	oglUniform2fv(pos,num,value);
}
void piRendererGL4X::SetShaderConstant1F(const unsigned int pos, const float *value, int num)
{
	oglUniform1fv(pos,num,value);
}
void piRendererGL4X::SetShaderConstant1I(const unsigned int pos, const int *value, int num)
{
	oglUniform1iv(pos,num,value);
}
void piRendererGL4X::SetShaderConstant1UI(const unsigned int pos, const unsigned int *value, int num)
{
	oglUniform1uiv(pos,num,value);
}
void piRendererGL4X::SetShaderConstant2UI(const unsigned int pos, const unsigned int *value, int num)
{
	oglUniform2uiv(pos,num,value);
}
void piRendererGL4X::SetShaderConstant3UI(const unsigned int pos, const unsigned int *value, int num)
{
	oglUniform3uiv(pos,num,value);
}
void piRendererGL4X::SetShaderConstant4UI(const unsigned int pos, const unsigned int *value, int num)
{
	oglUniform4uiv(pos,num,value);
}


void piRendererGL4X::SetShaderConstantMat4F(const unsigned int pos, const float *value, int num, bool transpose)
{
	oglUniformMatrix4fv(pos,num,transpose,value);
	//oglProgramUniformMatrix4fv( ((piIShader *)mBindedShader)->mProgID, pos, num, transpose, value ); // can do without binding!
}
void piRendererGL4X::SetShaderConstantSampler(const unsigned int pos, int unit)
{
	oglUniform1i(pos,unit);
}

static const int r2gl_blendMode[] = {
    GL_ONE,
    GL_SRC_ALPHA,
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA_SATURATE,
	GL_ZERO
};

static const int r2gl_blendEqua[] = {
    GL_FUNC_ADD, 
    GL_FUNC_SUBTRACT, 
    GL_FUNC_REVERSE_SUBTRACT, 
    GL_MIN, 
    GL_MAX
};

void piRendererGL4X::SetBlending( int buf, piBlendEquation equRGB, piBlendOperations srcRGB, piBlendOperations dstRGB,
                                           piBlendEquation equALP, piBlendOperations srcALP, piBlendOperations dstALP )
{
    oglBlendEquationSeparatei(buf, r2gl_blendEqua[equRGB], r2gl_blendEqua[equALP]);
    oglBlendFuncSeparatei(    buf, r2gl_blendMode[srcRGB], r2gl_blendMode[dstRGB],
                                   r2gl_blendMode[srcALP], r2gl_blendMode[dstALP]);
}

void piRendererGL4X::SetWriteMask( bool c0, bool c1, bool c2, bool c3, bool z )
{
    glDepthMask( z?GL_TRUE:GL_FALSE );
    oglColorMaski( 0, c0, c0, c0, c0 );
    oglColorMaski( 1, c0, c0, c0, c0 );
    oglColorMaski( 2, c0, c0, c0, c0 );
    oglColorMaski( 3, c0, c0, c0, c0 );
}

void piRendererGL4X::SetState( piState state, bool value )
{
	if( state==piSTATE_WIREFRAME )
	{
		if( value ) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		else        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
    else if( state==piSTATE_FRONT_FACE )
    {
        if( !value ) glFrontFace( GL_CW );
        else         glFrontFace( GL_CCW );
    }
    else if (state == piSTATE_DEPTH_TEST)
    {
        if (value) glEnable(GL_DEPTH_TEST);
        else       glDisable(GL_DEPTH_TEST);
    }
    else if( state== piSTATE_CULL_FACE )
	{
		if( value ) glEnable(GL_CULL_FACE);
		else        glDisable(GL_CULL_FACE);
	}
    else if( state == piSTATE_ALPHA_TO_COVERAGE )
    {
        if (value)  { glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);  glEnable(GL_SAMPLE_ALPHA_TO_ONE); glDisable(GL_SAMPLE_COVERAGE ); }
        else        { glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE); glDisable(GL_SAMPLE_ALPHA_TO_ONE);  glDisable(GL_SAMPLE_COVERAGE); }
    }
    else if( state == piSTATE_DEPTH_CLAMP )
	{
		if( value ) glEnable( GL_DEPTH_CLAMP);
		else        glDisable( GL_DEPTH_CLAMP);
	}
    else if( state == piSTATE_VIEWPORT_FLIPY )
	{
		if( value ) oglClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);
		else        oglClipControl(GL_LOWER_LEFT, GL_NEGATIVE_ONE_TO_ONE);
	}
    else if( state == piSTATE_BLEND )
    {
        if (value) glEnable(GL_BLEND);
        else       glDisable(GL_BLEND);
    }


}

typedef struct
{
	struct
	{
		bool wireFrame;
		bool depthClamp;
		bool cullFace;
	}mDesc;
	struct
	{
		GLenum polygonMode;
	}mGL;
}piIRasterState;

piRasterState piRendererGL4X::CreateRasterState(bool wireframe, bool cullFace, bool frontFace, bool depthClamp, bool multiSample)
{
	piIRasterState *me = (piIRasterState*)malloc(sizeof(piIRasterState));
	if (!me)
		return nullptr;
	
	me->mDesc.wireFrame = wireframe;
	me->mGL.polygonMode = (wireframe) ? GL_LINE : GL_FILL;
	me->mDesc.depthClamp = depthClamp;
	me->mDesc.cullFace = cullFace;

	/*
	me->mDesc.CullMode = (cullFace) ? (frontFace ? D3D11_CULL_FRONT : D3D11_CULL_BACK) : D3D11_CULL_NONE;
	me->mDesc.FrontCounterClockwise = false;
	me->mDesc.MultisampleEnable = multiSample;
	*/
	return me;
}

void piRendererGL4X::SetRasterState(const piRasterState vme)
{
	piIRasterState *me = (piIRasterState*)vme;
	glPolygonMode(GL_FRONT_AND_BACK, me->mGL.polygonMode);

	if (me->mDesc.depthClamp) glEnable(GL_DEPTH_CLAMP); else glDisable(GL_DEPTH_CLAMP);
	if (me->mDesc.cullFace)   glEnable(GL_CULL_FACE);   else glDisable(GL_CULL_FACE);
}

void piRendererGL4X::DestroyRasterState(piRasterState vme)
{
	piIRasterState *me = (piIRasterState*)vme;
	free(me);
}

//----------------------------------------------------
typedef struct
{
	struct
	{
		bool mAlphaToCoverage;
		bool mIndependentBlendEnable;
		struct
		{
			bool mBlendEnabled;
		}mRenderTarget[8];
	}mDesc;
}piIBlendState;

piBlendState piRendererGL4X::CreateBlendState(bool alphaToCoverage, bool enabled0)
{
	piIBlendState *me = (piIBlendState*)malloc(sizeof(piIBlendState));
	if (!me)
		return nullptr;

	me->mDesc.mAlphaToCoverage = alphaToCoverage;
	me->mDesc.mIndependentBlendEnable = false;
	me->mDesc.mRenderTarget[0].mBlendEnabled = enabled0;

	return me;
}

void piRendererGL4X::SetBlendState(const piRasterState vme)
{
	piIBlendState *me = (piIBlendState*)vme;

	if (me->mDesc.mAlphaToCoverage) 
	{ 
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);  
		glEnable(GL_SAMPLE_ALPHA_TO_ONE); 
		glDisable(GL_SAMPLE_COVERAGE); 
	}
	else 
	{ 
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE); 
		glDisable(GL_SAMPLE_ALPHA_TO_ONE);  
		glDisable(GL_SAMPLE_COVERAGE); 
	}
}

void piRendererGL4X::DestroyBlendState(piRasterState vme)
{
	piIBlendState *me = (piIBlendState*)vme;
	free(me);
}

//-------------------------
struct piIDepthState
{
	int dummy;
};
piDepthState piRendererGL4X::CreateDepthState(bool depthEnable, bool enabled0)
{
	piIDepthState *me = (piIDepthState*)malloc(sizeof(piIDepthState));
	if (!me)
		return nullptr;

	return me;
}

void piRendererGL4X::SetDepthState(const piRasterState vme)
{
	piIDepthState *me = (piIDepthState*)vme;
}

void piRendererGL4X::DestroyDepthState(piRasterState vme)
{
	piIDepthState *me = (piIDepthState*)vme;
	free(me);
}

//-------------------------
void piRendererGL4X::Clear( const float *color0, const float *color1, const float *color2, const float *color3, const bool depth0 )
{
    if( mBindedTarget == NULL )
    {
		int mode = 0;
		if( color0 ) { mode |= GL_COLOR_BUFFER_BIT;   glClearColor( color0[0], color0[1], color0[2], color0[3] ); }
		if( depth0 ) { mode |= GL_DEPTH_BUFFER_BIT;   glClearDepth( 1.0f ); } 
		glClear( mode );
    }
    else
    {
        float z = 1.0f;
	    if( color0 ) oglClearBufferfv( GL_COLOR, 0, color0 );
	    if( color1 ) oglClearBufferfv( GL_COLOR, 1, color1 );
	    if( color2 ) oglClearBufferfv( GL_COLOR, 2, color2 );
	    if( color3 ) oglClearBufferfv( GL_COLOR, 3, color3 );
	    if( depth0 ) oglClearBufferfv( GL_DEPTH, 0, &z );
    }
//    glClearBufferfi( GL_DEPTH_STENCIL, 0, z, s );
}

//-----------------------

piBuffer piRendererGL4X::CreateBuffer(const void *data, unsigned int amount, BufferType mode, BufferUse use)
{
    piIBuffer *me = (piIBuffer*)malloc(sizeof(piIBuffer));
    if (!me)
        return nullptr;

    oglCreateBuffers(1, &me->mObjectID);

    if (mode == BufferType::Dynamic)
    {
        oglNamedBufferStorage(me->mObjectID, amount, data, GL_DYNAMIC_STORAGE_BIT);
        //oglNamedBufferStorage(me->mObjectID, amount, data, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT );
        //me->mPtr = oglMapNamedBufferRange(me->mObjectID, 0, amount, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT );
        //if (me->mPtr == nullptr )
        //    return 0;
        //me->mSync = oglFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    }
    else
    {
        oglNamedBufferStorage(me->mObjectID, amount, data, 0);
        //me->mPtr = nullptr;
    }
    me->mSize = amount;
	me->mUse = use;

	mMemCurrent += amount;
	mNumCurrent += 1;
	if (mNumCurrent>mNumPeak) mNumPeak = mNumCurrent;
	if (mMemCurrent>mMemPeak) mMemPeak = mMemCurrent;

    return (piBuffer)me;
}

//glGenBuffers(1, &me->mObjectID);
//glBindBuffer(GL_SHADER_STORAGE_BUFFER, me->mObjectID);
//glBufferData(GL_SHADER_STORAGE_BUFFER, amount, nullptr, GL_DYNAMIC_COPY);


void piRendererGL4X::DestroyBuffer(piBuffer vme)
{
    piIBuffer *me = (piIBuffer*)vme;
    oglDeleteBuffers(1, &me->mObjectID );
	mMemCurrent -= me->mSize;
	mNumCurrent -= 1;
	free(me);
}

piBuffer piRendererGL4X::CreateStructuredBuffer(const void *data, unsigned int numElements, unsigned int elementSize, BufferType mode, BufferUse use)
{
	return CreateBuffer(data, numElements*elementSize, mode, use);
}

void piRendererGL4X::UpdateBuffer(piBuffer obj, const void *data, int offset, int len)
{
    piIBuffer *me = (piIBuffer *)obj;
    oglNamedBufferSubData(me->mObjectID, offset, len, data);
    /*
    while(1)
    {
        GLenum waitReturn = oglClientWaitSync(me->mSync, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
        if (waitReturn == GL_ALREADY_SIGNALED || waitReturn == GL_CONDITION_SATISFIED)
            break;
    }
    memcpy(me->mPtr, data, len);
*/
    //void *ptr = oglMapNamedBufferRange(me->mObjectID, 0, len, GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    //memcpy(ptr, data, len);
    //oglUnmapNamedBuffer( me->mObjectID );
}



piVertexArray piRendererGL4X::CreateVertexArray( int numStreams,
                                                 piBuffer vb0, const piRArrayLayout *streamLayout0, 
                                                 piBuffer vb1, const piRArrayLayout *streamLayout1,
                                                 piBuffer eb, const IndexArrayFormat ebFormat )
{
    piIVertexArray *me = (piIVertexArray*)malloc(sizeof(piIVertexArray));
    if( !me ) 
        return nullptr;

    oglCreateVertexArrays(1, &me->mObjectID);
    if (!me->mObjectID)
        return nullptr;

    unsigned int aid = 0;

	if (numStreams > 0)
	{
		for (int j = 0; j < numStreams; j++)
		{
			unsigned int sid = j;

			//me->mStreams[j] = (j == 0) *streamLayout0 : *streamLayout1;

			const piRArrayLayout * st = (j == 0) ? streamLayout0 : streamLayout1;
			piBuffer vb = (j == 0) ? vb0 : vb1;


			int offset = 0;
			const int num = st->mNumElements;
			for (int i = 0; i < num; i++)
			{
				oglEnableVertexArrayAttrib(me->mObjectID, aid);
				oglVertexArrayAttribFormat(me->mObjectID, aid, st->mEntry[i].mNumComponents, glType[st->mEntry[i].mType], st->mEntry[i].mNormalize, offset);
				oglVertexArrayAttribBinding(me->mObjectID, aid, sid);

				offset += st->mEntry[i].mNumComponents*glSizeof[st->mEntry[i].mType];
				aid++;
			}

			oglVertexArrayVertexBuffer(me->mObjectID, sid, ((piIBuffer*)vb)->mObjectID, 0, st->mStride);
			//oglVertexArrayBindingDivisor(me->mObjectID, bid, (streamLayout->mDivisor>0) ? streamLayout->mDivisor : 1 );
		}
	}
	else
	{
		//oglDisableVertexArrayAttrib(me->mObjectID, aid);
		//oglVertexArrayVertexBuffer(me->mObjectID, 0, 0, 0, 0);
	}

	if (eb != nullptr)
	{

		me->mIndexArrayType = ebFormat;
		oglVertexArrayElementBuffer(me->mObjectID, ((piIBuffer*)eb)->mObjectID);
	}

    return (piVertexArray)me;
}

void piRendererGL4X::DestroyVertexArray(piVertexArray vme)
{
    piIVertexArray *me = (piIVertexArray*)vme;
    oglDeleteVertexArrays(1, &me->mObjectID);
}

void piRendererGL4X::AttachVertexArray(piVertexArray vme)
{
    piIVertexArray *me = (piIVertexArray*)vme;
    oglBindVertexArray(me->mObjectID);
	mBoundVertexArray = vme;
}

void piRendererGL4X::DettachVertexArray( void )
{
    oglBindVertexArray( 0 );
}

piVertexArray piRendererGL4X::CreateVertexArray2(int numStreams, piBuffer vb0, const ArrayLayout2 *streamLayout0, piBuffer vb1, const ArrayLayout2 *streamLayout1, const void *shaderBinary, size_t shaderBinarySize, piBuffer ib, const IndexArrayFormat ebFormat)
{
	return nullptr;
}
void piRendererGL4X::AttachVertexArray2(piVertexArray vme)
{
}

void piRendererGL4X::DestroyVertexArray2(piVertexArray vme)
{
}

GLenum piRendererGL4X::iPrimtive_pi2gl(PrimitiveType pt)
{
	GLenum glpt = GL_TRIANGLES;
         if (pt == PrimitiveType::Triangle)        glpt = GL_TRIANGLES;
	else if (pt == PrimitiveType::Point)           glpt = GL_POINTS;
	else if (pt == PrimitiveType::TriangleStrip)   glpt = GL_TRIANGLE_STRIP;
	else if (pt == PrimitiveType::LineStrip)       glpt = GL_LINE_STRIP;
	else if (pt == PrimitiveType::TriPatch)      { glpt = GL_PATCHES; oglPatchParameteri(GL_PATCH_VERTICES, 3); }
	else if (pt == PrimitiveType::QuadPatch)     { glpt = GL_PATCHES; oglPatchParameteri(GL_PATCH_VERTICES, 4); }
	else if (pt == PrimitiveType::LinesAdj)        glpt = GL_LINES_ADJACENCY;
	else if (pt == PrimitiveType::LineStripAdj)    glpt = GL_LINE_STRIP_ADJACENCY;
	else if (pt == PrimitiveType::Patch16)       { glpt = GL_PATCHES; oglPatchParameteri(GL_PATCH_VERTICES, 16); }
	else if (pt == PrimitiveType::Patch32)       { glpt = GL_PATCHES; oglPatchParameteri(GL_PATCH_VERTICES, 32); }
	else if (pt == PrimitiveType::Lines)           glpt = GL_LINES;
	return glpt;
}
void piRendererGL4X::DrawPrimitiveIndexed(PrimitiveType pt, int num, int numInstances, int baseVertex, int baseInstance)
{
	GLenum glpt = iPrimtive_pi2gl(pt);
	piIVertexArray *va = (piIVertexArray*)mBoundVertexArray;
	oglDrawElementsInstancedBaseVertexBaseInstance( glpt, num, (va->mIndexArrayType==IndexArrayFormat::UINT_32) ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT,
                NULL,   // indices
                numInstances,      // prim count
                baseVertex,      // base vertex
                baseInstance);     // base instance
}

void piRendererGL4X::DrawPrimitiveNotIndexed(PrimitiveType pt, int first, int num, int numInstanced)
{
	GLenum glpt = iPrimtive_pi2gl(pt);
	oglDrawArraysInstanced(glpt, first, num, numInstanced);
}


void piRendererGL4X::DrawPrimitiveNotIndexedMultiple(PrimitiveType pt, const int *firsts, const int *counts, int num)
{
	GLenum glpt = iPrimtive_pi2gl(pt);
    oglMultiDrawArrays(glpt,firsts,counts,num);
}


void piRendererGL4X::DrawPrimitiveNotIndexedIndirect(PrimitiveType pt, piBuffer cmds, int num)
{
    piIBuffer *buf = (piIBuffer *)cmds;

    oglBindBuffer(GL_DRAW_INDIRECT_BUFFER, buf->mObjectID);

	GLenum glpt = iPrimtive_pi2gl(pt);

    oglMultiDrawArraysIndirect(glpt, 0, num, sizeof(piDrawArraysIndirectCommand));
    //oglBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
}

void piRendererGL4X::DettachIndirectBuffer(void)
{
	oglBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
}

void piRendererGL4X::DrawPrimitiveIndirect(PrimitiveType pt, piBuffer cmds, uint32_t offset, uint32_t num)
{
    piIBuffer *buf = (piIBuffer *)cmds;

    oglBindBuffer(GL_DRAW_INDIRECT_BUFFER, buf->mObjectID);

	GLenum glpt = iPrimtive_pi2gl(pt);

	piIVertexArray *va = (piIVertexArray*)mBoundVertexArray;
	oglMultiDrawElementsIndirect(glpt, (va->mIndexArrayType == IndexArrayFormat::UINT_32) ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT, reinterpret_cast<void*>(offset), num, sizeof(piDrawElementsIndirectCommand));
    //oglBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
}

void piRendererGL4X::DrawUnitQuad_XY( int numInstanced )
{
    this->AttachVertexArray( mVA[0] );
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, numInstanced);
    this->DettachVertexArray();
}

void piRendererGL4X::DrawUnitCube_XYZ_NOR(int numInstanced)
{
    this->AttachVertexArray(mVA[1]);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 4, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 8, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 12, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 16, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 20, 4, numInstanced);
    this->DettachVertexArray();
}

void piRendererGL4X::DrawUnitCube_XYZ(int numInstanced)
{
    this->AttachVertexArray(mVA[2]);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 4, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 8, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 12, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 16, 4, numInstanced);
    oglDrawArraysInstanced(GL_TRIANGLE_STRIP, 20, 4, numInstanced);
    this->DettachVertexArray();
}

void piRendererGL4X::ExecuteCompute(int tx, int ty, int tz, int gsx, int gsy, int gsz)
{
    int ngx = tx / gsx; if( (ngx*gsx) < tx ) ngx++;
    int ngy = ty / gsy; if( (ngy*gsy) < ty ) ngy++;
    int ngz = tz / gsz; if( (ngz*gsz) < tz ) ngz++;

    oglDispatchCompute( ngx, ngy, ngz );
}

void piRendererGL4X::SetLineWidth( float size )
{
    glLineWidth( size );
}

void piRendererGL4X::SetPointSize( bool mode, float size )
{
	if( mode )
	{
		glEnable( GL_PROGRAM_POINT_SIZE );
        glPointSize( size );
	}
	else
		glDisable( GL_PROGRAM_POINT_SIZE );

}

void piRendererGL4X::GetTextureRes( piTexture vme, int *res )
{
	piITexture *me = (piITexture*)vme;
	res[0] = me->mInfo.mXres;
	res[1] = me->mInfo.mYres;
	res[2] = me->mInfo.mZres;

}

void piRendererGL4X::GetTextureFormat( piTexture vme, piTextureFormat *format )
{
	piITexture *me = (piITexture*)vme;
    format[0] = me->mInfo.mFormat;
}


void piRendererGL4X::GetTextureInfo( piTexture vme, TextureInfo *info )
{
	piITexture *me = (piITexture*)vme;
    info[0] = me->mInfo;
    info->mDeleteMe = me->mObjectID;
}


void piRendererGL4X::GetTextureSampling(piTexture vme, TextureFilter *rfilter, TextureWrap *rwrap)
{
    piITexture *me = (piITexture*)vme;
    rfilter[0] = me->mFilter;
    rwrap[0] = me->mWrap;
}


void piRendererGL4X::GetTextureContent( piTexture vme, void *data, const piTextureFormat fmt )
{
	piITexture *me = (piITexture*)vme;
    int     	 mode, mode2, mode3, bpp;

    //if( !format2gl( me->mInfo.mFormat, &bpp, &mode, &mode2, &mode3, me->mInfo.mCompressed ) )
    if( !format2gl( fmt, &bpp, &mode, &mode2, &mode3, me->mInfo.mCompressed ) )
        return;

    //glPixelStorei(GL_UNPACK_SWAP_BYTES, true);

    oglGetTextureImage(me->mObjectID, 0, mode, mode3, me->mInfo.mXres*me->mInfo.mYres*me->mInfo.mZres * bpp, data);
}

void piRendererGL4X::GetTextureContent(piTexture vme, void *data, int x, int y, int z, int xres, int yres, int zres)
{
    piITexture *me = (piITexture*)vme;
    int     	 exteriorFormat, internalFormat, ftype, bpp;

    if (!format2gl(me->mInfo.mFormat, &bpp, &exteriorFormat, &internalFormat, &ftype, me->mInfo.mCompressed))
        return;

    oglGetTextureSubImage( me->mObjectID,
                           0, 
                           x, y, z, xres, yres, zres, 
                           exteriorFormat, ftype, 
                           xres*yres*zres*bpp, data );
}

//------------

/*
void piRendererGL4X::SetAttribute1F( int pos, const float data )
{
    oglVertexAttrib1f( pos, data );
}

void piRendererGL4X::SetAttribute2F( int pos, const float *data )
{
    oglVertexAttrib2fv( pos, data );
}

void piRendererGL4X::SetAttribute3F( int pos, const float *data )
{
    oglVertexAttrib3fv( pos, data );
}

void piRendererGL4X::SetAttribute4F( int pos, const float *data )
{
    oglVertexAttrib4fv( pos, data );
}
*/

void piRendererGL4X::PolygonOffset( bool mode, bool wireframe, float a, float b )
{
    if( mode )
    {
        glEnable( wireframe?GL_POLYGON_OFFSET_LINE:GL_POLYGON_OFFSET_FILL ); 
        glPolygonOffset( a, b );
    }
    else
    {
        glDisable( wireframe?GL_POLYGON_OFFSET_LINE:GL_POLYGON_OFFSET_FILL ); 
    }
}

void piRendererGL4X::RenderMemoryBarrier(BarrierType type)
{
    GLbitfield bf = 0;

    if(static_cast<int>(type) & static_cast<int>(BarrierType::SHADER_STORAGE) ) bf |= GL_SHADER_STORAGE_BARRIER_BIT;
    if(static_cast<int>(type) & static_cast<int>(BarrierType::UNIFORM)        ) bf |= GL_UNIFORM_BARRIER_BIT;
    if(static_cast<int>(type) & static_cast<int>(BarrierType::ATOMICS)        ) bf |= GL_ATOMIC_COUNTER_BARRIER_BIT;
    if(static_cast<int>(type) & static_cast<int>(BarrierType::IMAGE)          ) bf |= GL_SHADER_IMAGE_ACCESS_BARRIER_BIT;
    if(static_cast<int>(type) & static_cast<int>(BarrierType::COMMAND )       ) bf |= GL_COMMAND_BARRIER_BIT;
    if(static_cast<int>(type) & static_cast<int>(BarrierType::TEXTURE)        ) bf |= GL_TEXTURE_UPDATE_BARRIER_BIT;

	if(static_cast<int>(type) == static_cast<int>(BarrierType::ALL)) bf = GL_ALL_BARRIER_BITS;

    oglMemoryBarrier(bf);
}

}