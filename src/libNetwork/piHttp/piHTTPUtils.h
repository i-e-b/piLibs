#pragma once

namespace piLibs {

class piHTTPUtils
{
public:
	// do not free this pointer
	static const char * GetMimeType(const wchar_t *fileExtension);

};


}