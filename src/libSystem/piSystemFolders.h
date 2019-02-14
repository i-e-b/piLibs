#pragma once

#include "piTypes.h"

namespace piLibs {

class piSystemFolders
{
public:
    static void SetAppCurrentUserRegistrySubkey(wchar_t const* subkey);
    static wchar_t const* GetPictures(void);
    static wchar_t const* GetAppData(void);
    static wchar_t const* GetDocuments(void);

private:
    static wchar_t *piSystemFolders::sApplicationCurrentUserSubkey;
    static wchar_t piSystemFolders::picturesFolderPath[256];
    static wchar_t piSystemFolders::appdataFolderPath[256];
    static wchar_t piSystemFolders::documentsFolderPath[256];

};

} // namespace piLibs