#include <stdarg.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "piCustomLogger.h"

namespace piLibs {

piCustomLogger::piCustomLogger(void(*customLogCallback)(char*)):piLogger()
{
	mCustomLogCallback = customLogCallback;
}
piCustomLogger::~piCustomLogger()
{
}


bool piCustomLogger::Init( const wchar_t *path, const piLogStartInfo *info )
{
	iPrintS( L"===================================================\n");
	iPrintF( L"date      : %s\n", info->date);
	iPrintF( L"\n");
	iPrintF( L"Memory    : %d / %d Megabytes \n", info->free_memory_MB, info->total_memory_MB);
	iPrintF( L"CPU       : %s\n", info->processor);
	iPrintF( L"Units     : %d\n", info->number_cpus);
	iPrintF( L"Speed     : %d Mhz\n", info->mhz);
	iPrintF( L"OS        : %s\n", info->os);
	iPrintF( L"GPU       : %s, %s\n", info->gpuVendor, info->gpuModel);
	iPrintF( L"VRam      : %d Megabytes \n", info->total_videomemory_MB);
	iPrintF( L"Screen    : %d x %d\n", info->mScreenResolution[0], info->mScreenResolution[1]);
	iPrintF( L"Monitors  : %d\n", info->mNumMonitors);
	iPrintF( L"Multitouch: %d\n", info->mIntegratedMultitouch);
	iPrintS( L"===================================================\n");

	return true;
}

void piCustomLogger::End( void )
{
}

void piCustomLogger::Printf( int messageId, int threadId, const wchar_t *file, const wchar_t *func, int line, int type, const wchar_t *str )
{
	switch (type)
	{
	case 1:
		iPrintF( L"[%d]  %s::%s (%d) : %s", threadId, file, func, line, str);
		break;
	case 2:
		iPrintF( L"[%d]  %s::%s (%d) : %s", threadId, file, func, line, str);
		break;
	case 3:
		iPrintF( L"[%d]  %s::%s (%d) : %s", threadId, file, func, line, str);
		break;

	case 4:
		iPrintS( str);
		break;

	case 5:
		iPrintS( str);
		break;
	}

}


void piCustomLogger::iPrintF( const wchar_t *format, ...)
{
	wchar_t    tmpstr[2048];

	va_list arglist;
	va_start(arglist, format);
	int len = vswprintf_s(tmpstr, 2047, format, arglist);
	va_end(arglist);

	iPrintS(tmpstr);
}

void piCustomLogger::iPrintS( const wchar_t *wstr)
{
	char str[2048];
	size_t l = (int)wcstombs(str, wstr, 2047);
	str[l] = 0;

	mCustomLogCallback(str);
}

} // namespace piLibs