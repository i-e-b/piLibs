#include <windows.h>
#include <shlobj.h>
#include <string.h>

#include "../piSystemFolders.h"

namespace piLibs {

wchar_t * piSystemFolders::sApplicationCurrentUserSubkey = nullptr;

void piSystemFolders::SetAppCurrentUserRegistrySubkey(wchar_t const* subkey)
{
	piSystemFolders::sApplicationCurrentUserSubkey = _wcsdup( subkey );
}

static bool iGetRegistryEntry( wchar_t *res, const wchar_t *appCurentUserSubkey, const wchar_t * subfolder)
{
	if( appCurentUserSubkey==nullptr ) return false;

	HKEY hKey = nullptr;
	if(ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, appCurentUserSubkey, 0, KEY_READ, &hKey))
	{
		DWORD dwDispositionUnused;
		if( ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, appCurentUserSubkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &dwDispositionUnused) )
		{
			hKey = nullptr;
		}
	}

	if(hKey!=nullptr)
	{
		DWORD bufferSize = 256;
		DWORD bufferType;
		if( ERROR_SUCCESS == RegGetValue(hKey, NULL, subfolder, RRF_RT_REG_SZ, &bufferType, res, &bufferSize) )
		{
		    RegCloseKey(hKey);
			return true;
		}
		RegCloseKey(hKey);
	}

	return false;
}


const wchar_t *piSystemFolders::GetPictures(void)
{
	if( !iGetRegistryEntry( picturesFolderPath, sApplicationCurrentUserSubkey, L"PicturesFolder") )
	{
		wchar_t *res;
		HRESULT h = ::SHGetKnownFolderPath(FOLDERID_Pictures, KF_FLAG_CREATE, NULL, &res);
		if( res )
        {   
            wcscpy( picturesFolderPath, res );
		    CoTaskMemFree(res);
        }
        else
        {
            return nullptr;
        }
	}
	return picturesFolderPath;
}

const wchar_t *piSystemFolders::GetAppData(void)
{
	if( !iGetRegistryEntry(appdataFolderPath, sApplicationCurrentUserSubkey, L"AppDataFolder") )
	{
		wchar_t *res;
		HRESULT h = ::SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &res);
		if(res) 
        {
            wcscpy( appdataFolderPath, res );
		    CoTaskMemFree(res);
        }
        else
        {
            return nullptr;
        }
	}
	return appdataFolderPath;
}

const wchar_t *piSystemFolders::GetDocuments(void)
{
	if( !iGetRegistryEntry(documentsFolderPath, sApplicationCurrentUserSubkey, L"DocumentsFolder") )
	{
		wchar_t *res;
		HRESULT h = ::SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, NULL, &res);
		if(res) 
        {
            wcscpy( documentsFolderPath, res );
		    CoTaskMemFree(res);
        }
        else
        {
            return nullptr;
        }
	}
	return documentsFolderPath;
}

}

