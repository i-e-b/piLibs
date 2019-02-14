#pragma once

#include "piLog.h"

namespace piLibs {

class piCustomLogger: public piLogger
{
public:
	piCustomLogger( void(*customLogCallback)(char*) );
	~piCustomLogger();

	virtual bool Init( const wchar_t *path, const piLogStartInfo *info );
    virtual void End( void );
	virtual void Printf( int messageId, int threadId, const wchar_t *file, const wchar_t *func, int line, int type, const wchar_t *str );

private:
	void(*mCustomLogCallback)(char*);

	void iPrintF(const wchar_t *format, ...);
	void iPrintS(const wchar_t *str);

};

} // namespace piLibs