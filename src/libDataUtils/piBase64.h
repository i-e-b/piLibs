#pragma once

#include "../libSystem/piTypes.h"

namespace piLibs {

	class piBase64
	{
	public:

		// Caller is responsible for freeing the returned buffer.Returned buffer is nul terminated to make it
		// easier to use as a C string.The nul terminator is not included in out_len.
		static bool encode(const unsigned char *src, size_t len, unsigned char **outBuffer, size_t *out_len);
	};

}