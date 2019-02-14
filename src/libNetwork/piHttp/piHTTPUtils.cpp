#pragma once

#include "piHTTPUtils.h"

namespace piLibs {

	static const char *mimeTypes[] = {
		"image/gif",       // 0
		"image/png",       // 1
		"image/jpg",       // 2
		"application/zip", // 3
		"text/plain",
		"audio/ogg",
		"video/mp4" };

	const char * piHTTPUtils::GetMimeType(const wchar_t *fileExtension)
	{
		if ((fileExtension[0] == 'g' || fileExtension[0] == 'G') &&
			(fileExtension[1] == 'i' || fileExtension[1] == 'I') &&
			(fileExtension[2] == 'f' || fileExtension[2] == 'F')) return mimeTypes[0];

		if ((fileExtension[0] == 'p' || fileExtension[0] == 'P') &&
			(fileExtension[1] == 'n' || fileExtension[1] == 'N') &&
			(fileExtension[2] == 'g' || fileExtension[2] == 'G')) return mimeTypes[1];

		if ((fileExtension[0] == 'j' || fileExtension[0] == 'J') &&
			(fileExtension[1] == 'p' || fileExtension[1] == 'P') &&
			(fileExtension[2] == 'g' || fileExtension[2] == 'G')) return mimeTypes[2];

		if ((fileExtension[0] == 'z' || fileExtension[0] == 'Z') &&
			(fileExtension[1] == 'i' || fileExtension[1] == 'I') &&
			(fileExtension[2] == 'p' || fileExtension[2] == 'P')) return mimeTypes[3];

		return nullptr;
	}


}