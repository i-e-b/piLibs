#ifdef WINDOWS
#include <windows.h>
#include <wincon.h>
#endif
#include <stdarg.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "piStdOutLogger.h"

namespace piLibs {

piStdOutLogger::piStdOutLogger():piLogger()
{
}
piStdOutLogger::~piStdOutLogger()
{
}


bool piStdOutLogger::Init( const wchar_t *path, const piLogStartInfo *info )
{
/*
#ifdef WINDOWS
     // This block is need for non console but window appliations
	AttachConsole(-1); // attach to parent's console
	freopen("CON", "w", stdout);// reopen the std I/O streams to redirect I/O to the new console
	freopen("CON", "w", stderr);
	freopen("CON", "r", stdin);
#endif
*/
	wprintf( L"===================================================\n");
	wprintf( L"date      : %s\n", info->date);
	wprintf( L"\n");
	wprintf( L"Memory    : %d / %d Megabytes \n", info->free_memory_MB, info->total_memory_MB);
	wprintf( L"CPU       : %s\n", info->processor);
	wprintf( L"Units     : %d\n", info->number_cpus);
	wprintf( L"Speed     : %d Mhz\n", info->mhz);
	wprintf( L"OS        : %s\n", info->os);
	wprintf( L"GPU       : %s, %s\n", info->gpuVendor, info->gpuModel);
	wprintf( L"VRam      : %d Megabytes \n", info->total_videomemory_MB);
	wprintf( L"Screen    : %d x %d\n", info->mScreenResolution[0], info->mScreenResolution[1]);
	wprintf( L"Monitors  : %d\n", info->mNumMonitors);
	wprintf( L"Multitouch: %d\n", info->mIntegratedMultitouch);
	wprintf( L"===================================================\n");

	return true;
}

void piStdOutLogger::End( void )
{
}

void piStdOutLogger::Printf( int messageId, int threadId, const wchar_t *file, const wchar_t *func, int line, int type, const wchar_t *str )
{
	switch (type)
	{
	case 1:
		wprintf( L"[%d]  %s::%s (%d) : %s\n", threadId, file, func, line, str);
		break;
	case 2:
		wprintf( L"[%d]  %s::%s (%d) : %s\n", threadId, file, func, line, str);
		break;
	case 3:
		wprintf( L"[%d]  %s::%s (%d) : %s\n", threadId, file, func, line, str);
		break;

	case 4:
		wprintf( L"%s\n", str);
		break;

	case 5:
		wprintf(L"%s\n", str);
		break;
	}

}


} // namespace piLibs