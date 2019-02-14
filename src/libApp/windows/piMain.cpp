#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

// needed for post VS2015 SP-3.
// see comment at bottom of c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include\delayimp.h
#define DELAYIMP_INSECURE_WRITABLE_HOOKS

#include <windows.h>
#include <shellapi.h>
#include <delayimp.h>

extern int    piMainFunc( const wchar_t *path, const wchar_t **args, int numArgs, void *instance );
extern void * piMainCrashHandlerFunc( void );
extern void * piMainMissingDLLHandlerFunc();

void *gCrashFunc = nullptr;
void *gDllMissingFunc = nullptr;

static LONG WINAPI iExceptionFilter( EXCEPTION_POINTERS* pExp )
{
    ((void(*)(void * currentThread, void * context))gCrashFunc)(GetCurrentThread(), pExp->ContextRecord);

    return EXCEPTION_EXECUTE_HANDLER;
}
static FARPROC WINAPI iDelayLoadHook(unsigned dliNotify, PDelayLoadInfo pdli)
{
	int shouldExit = 0;

	switch (dliNotify)
	{
	case dliFailLoadLib: { shouldExit = ((int(*)(int, LPCSTR))gDllMissingFunc)(0, pdli->szDll); break; }
	case dliFailGetProc: { shouldExit = ((int(*)(int, LPCSTR))gDllMissingFunc)(1, pdli->szDll); break; }
	default: return 0;
	};
	
	if (shouldExit==1) ExitProcess(0);

	return 0;
}

PfnDliHook   __pfnDliFailureHook2 = &iDelayLoadHook;

int WINAPI wWinMain( HINSTANCE instance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	gCrashFunc = piMainCrashHandlerFunc();
	gDllMissingFunc = piMainMissingDLLHandlerFunc();
	
    SetProcessDPIAware();

    // remove quotes from command line
    if( lpCmdLine )
    {
        if( lpCmdLine[0]==L'"' ) 
        {
            int i; for( i=0; lpCmdLine[i]; i++ ); lpCmdLine[i-1]=0; lpCmdLine++;
        }
    }

    int numArgs = 0;
    wchar_t **args = CommandLineToArgvW(GetCommandLineW(), &numArgs);

    wchar_t buffer[1024];
    GetCurrentDirectory(1024, buffer);

    // get executable file path
    GetModuleFileName( instance, buffer, 1024 );
    int ls=0; for( int i=0; buffer[i]; i++ ) if( buffer[i]==L'/' || buffer[i]==L'\\' ) ls=i; buffer[ls] = 0;

    SetCurrentDirectory(buffer);

    int res = 0;
    if (gCrashFunc == nullptr)
    {
        res = piMainFunc(buffer, (const wchar_t**)args, numArgs, instance);
    }
    else
    {
        __try
        {
            res = piMainFunc(buffer, (const wchar_t**)args, numArgs, instance);
        }
        __except( iExceptionFilter(GetExceptionInformation()) )
        {
            return 0;
        }
    }

    LocalFree(args);

    return res;
}

