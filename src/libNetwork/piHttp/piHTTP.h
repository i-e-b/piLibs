#pragma once

#include "../../libSystem/piTypes.h"

namespace piLibs {

class piInternet
{
public:
	typedef void *piHTTP_Session;

	struct Ports
	{
		static const int HTTP = 80;
		static const int HTTPS = 443;
	};

	typedef struct
	{
		char *mBuffer;
		int   mLength;
	}RequestResult;

public:
	bool Init(const wchar_t *name);
	void End(void);

	// One shot request to a server. Do not use unless you don't plan to query the same server soon again
	bool SetGetRequest(const wchar_t *url, RequestResult * result, bool appendEOLToResponse);
	bool SendPostRequest(const wchar_t *server, const wchar_t *file, const uint8_t *data, const uint32_t dataLen, const wchar_t *header, RequestResult * result, bool appendEOLToResponse);

	// Session based queries. Useful for when many requests are expected to the same server
	piHTTP_Session SessionOpen( const wchar_t *severURL, int port);
	void           SessionClose(piHTTP_Session me);
	bool           SessionSendGetRequest(piHTTP_Session me, const wchar_t *header, const wchar_t *url, RequestResult * result, bool appendEOLToResponse);
	bool           SessionSendPostRequest(piHTTP_Session me, const wchar_t *header, const wchar_t *url, const uint8_t *data, const uint32_t dataLen, RequestResult * result, bool appendEOLToResponse);

	void           FreeResponse(RequestResult * result);

private:
	void *mData;
};


}