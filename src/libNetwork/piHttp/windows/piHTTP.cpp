#include <windows.h>
#include <wininet.h>
#pragma comment(lib,"wininet.lib")
#include <malloc.h>
#include <string.h>

#include "../piHTTP.h"
//#include "../../../libDataUtils/piString.h"
//#pragma comment (lib, "urlmon.lib")

namespace piLibs {

	typedef struct
	{
		HINTERNET hIntSession;
	}iInternet;

	typedef struct
	{
		HINTERNET hHttpSession;
	}iSession;


	bool iGetResult(HINTERNET req, piInternet::RequestResult * result, bool appendEOLToResponse);

	static void CALLBACK myInternetCallback( HINTERNET hInternet, DWORD_PTR dwContext,
		                                     DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength )
	{
		//DOWNLOAD_CONTEXT *context = (DOWNLOAD_CONTEXT*)dwContext;

		switch (dwInternetStatus)
		{
			case INTERNET_STATUS_HANDLE_CREATED:
				break;
			case INTERNET_STATUS_HANDLE_CLOSING:
				break;
			case INTERNET_STATUS_RESPONSE_RECEIVED:
				break;
			case INTERNET_STATUS_REQUEST_COMPLETE:
				break;
		}
	}
	
	bool piInternet::Init(const wchar_t *name)
	{
		mData = malloc(sizeof(iInternet));
		if (!mData)
			return false;

		iInternet *me = (iInternet*)mData;

		//char httpUseragent[512];
		//DWORD szhttpUserAgent = sizeof(httpUseragent);
		//ObtainUserAgentString(0, httpUseragent, &szhttpUserAgent);
		//piString tmp; tmp.InitCopyS(httpUseragent);

		//me->hIntSession = InternetOpen(tmp.GetS(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 /*INTERNET_FLAG_ASYNC*/);
		me->hIntSession = InternetOpen(name, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 /*INTERNET_FLAG_ASYNC*/);
		if (!me->hIntSession) return nullptr;

		InternetSetStatusCallback(me->hIntSession, myInternetCallback);

		return true;
	}

	void piInternet::End(void)
	{
		iInternet *me = (iInternet*)mData;
		InternetCloseHandle(me->hIntSession);
		free(mData);
	}

	//----------------------------------------------------------------------------------------------------------


	bool piInternet::SetGetRequest( const wchar_t *url, RequestResult * result, bool appendEOLToResponse)
	{
		iInternet *mInternet = (iInternet*)mData;

		HINTERNET hHttpRequest = InternetOpenUrl(mInternet->hIntSession, url, nullptr, 0, INTERNET_FLAG_NO_UI, 0);
		if (hHttpRequest == NULL)
		{
			int dwErr = GetLastError();
			return false;
		}

		if (!iGetResult(hHttpRequest, result, appendEOLToResponse))
			return false;

		InternetCloseHandle(hHttpRequest);

		return true;
	}

	bool piInternet::SendPostRequest( const wchar_t *server, const wchar_t *file, const uint8_t *data, const uint32_t dataLen, const wchar_t *header, RequestResult * result, bool appendEOLToResponse)
	{
		piInternet::piHTTP_Session ses = this->SessionOpen( server, piInternet::Ports::HTTPS);
		if (!ses)
			return false;

		if (!this->SessionSendPostRequest(ses, header, file, data, dataLen, result, appendEOLToResponse))
			return false;

		this->SessionClose(ses);
	}
	//----------------------------------------------------------------------------------------------------------
	
	piInternet::piHTTP_Session piInternet::SessionOpen( const wchar_t *url, int port)
	{
		iInternet *mInternet = (iInternet*)mData;

		iSession *me = (iSession*)malloc(sizeof(iInternet));
		if (!me)
			return false;
		
		me->hHttpSession = InternetConnect(mInternet->hIntSession, url, port, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
		if (!me->hHttpSession) return nullptr;

		return (piHTTP_Session)me;
	}

	void piInternet::SessionClose(piHTTP_Session vme)
	{
		iSession *me = (iSession*)vme;
		InternetCloseHandle(me->hHttpSession);
	}
		
	bool piInternet::SessionSendGetRequest(piHTTP_Session vme, const wchar_t *mime, const wchar_t *url, RequestResult * result, bool appendEOLToResponse)
	{
		iInternet *mInternet = (iInternet*)mData;

		iSession *me = (iSession*)vme;

		PCTSTR rgpszAcceptTypes[] = { L"text/*", L"image/png", L"application/json", L"*/*", NULL };

		HINTERNET hHttpRequest = HttpOpenRequest(me->hHttpSession, L"GET", url, L"HTTP/1.1", 0, rgpszAcceptTypes, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_PRAGMA_NOCACHE, 0);
		if (hHttpRequest == NULL)
			return false;

		char szReq[1024] = "";
		if (!HttpSendRequest(hHttpRequest, /*szHeaders*/mime, (int)wcslen(/*szHeaders*/mime), szReq, (int)strlen(szReq)))
		{
			int dwErr = GetLastError();
			/// handle error
			return false;
		}

		if (!iGetResult(hHttpRequest, result, appendEOLToResponse))
			return false;

		InternetCloseHandle(hHttpRequest);

		return true;
	}

	bool piInternet::SessionSendPostRequest(piHTTP_Session vme, const wchar_t *header, const wchar_t *url, const uint8_t *data, const uint32_t dataLen, RequestResult * result, bool appendEOLToResponse)
	{
		iInternet *mInternet = (iInternet*)mData;

		iSession *me = (iSession*)vme;

		PCTSTR acceptTypes[] = { L"*/*", NULL };

		HINTERNET hHttpRequest = HttpOpenRequest(me->hHttpSession, L"POST", url, L"HTTP/1.1", 0, acceptTypes, INTERNET_FLAG_KEEP_CONNECTION |
			                                                                                                             //                        INTERNET_FLAG_FORMS_SUBMIT |
			                                                                                                  INTERNET_FLAG_SECURE | 
			                                                                                                  INTERNET_FLAG_HYPERLINK | 
			                                                                                                  INTERNET_FLAG_RELOAD |
			                                                                                                  INTERNET_FLAG_NO_CACHE_WRITE |
			                                                                                                  INTERNET_FLAG_PRAGMA_NOCACHE, 0);
		if (hHttpRequest == NULL)
			return false;
		/*
		wchar_t *header = L"Content-Type:application/x-www-form-urlencoded\r\n"
			              L"Accept-Encoding:identity\r\n"
			              L"Accept-Language:en-US,en;q=0.9\r\n"
			              L"Origin:null\r\n"
			              L"Connection:Keep-Alive\r\n"
		                  L"Host:graph.facebook.com\r\n\r\n";

		HttpAddRequestHeaders(hHttpRequest, header, (int)wcslen(header), HTTP_ADDREQ_FLAG_ADD);
		*/

		//wchar_t *header = L"Content-Type: application/x-www-form-urlencoded";

		if (!HttpSendRequest(hHttpRequest, header, (int)wcslen(header), (void*)data, dataLen))
		{
			int dwErr = GetLastError();
			/// handle error
			return false;
		}

		if (!iGetResult(hHttpRequest, result, appendEOLToResponse))
			return false;
		
		InternetCloseHandle(hHttpRequest);

		return true;
	}

	//---------------------------------------------------------------------------

	static bool iGetResult(HINTERNET req, piInternet::RequestResult * result, bool appendEOLToResponse)
	{
		char tmp[2048];
		const int tmpLen = sizeof(tmp);

		int     mMax = 0;
		result->mLength = 0;
		result->mBuffer = 0;

		DWORD dwRead = 0;
		while (InternetReadFile(req, tmp, tmpLen, &dwRead))
		{
			if (dwRead == 0) break;

			if (result->mLength + (int)dwRead > mMax)
			{
				const int ps1 = result->mLength + dwRead + 1; // put always one more for later EOL if necessary
				const int ps2 = result->mLength * 3 / 4;
				mMax = max(ps1, ps2);
				result->mBuffer = (char*)realloc(result->mBuffer, mMax);
				if (!result->mBuffer)
					return false;
			}

			memcpy(result->mBuffer + result->mLength, tmp, dwRead);
			result->mLength += dwRead;

			dwRead = 0;
		}

		if (appendEOLToResponse)
		{
			result->mBuffer[result->mLength] = 0;
		}
		return true;
	}


	void piInternet::FreeResponse(RequestResult * result)
	{
		if (result->mLength == 0 || result->mBuffer == nullptr) return;
		free(result->mBuffer);
	}
}