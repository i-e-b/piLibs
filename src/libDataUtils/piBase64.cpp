#include <malloc.h>
#include <string.h>

#include "../libSystem/piTypes.h"

#include "piBase64.h"

namespace piLibs {

	// code copied from http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c

	static const unsigned char base64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	/**
	* base64_encode - Base64 encode
	* @src: Data to be encoded
	* @len: Length of the data to be encoded
	* @out_len: Pointer to output length variable, or %NULL if not used
	* Returns: Allocated buffer of out_len bytes of encoded data,
	* or %NULL on failure
	*
	* Caller is responsible for freeing the returned buffer. Returned buffer is
	* nul terminated to make it easier to use as a C string. The nul terminator is
	* not included in out_len.
	*/
	bool piBase64::encode(const unsigned char *src, size_t len, unsigned char **outBuffer, size_t *out_len)
	{
		size_t olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
//		olen += olen / 72; /* line feeds */
		olen++; /* nul termination */
		if (olen < len)
			return false; /* integer overflow */

		unsigned char *out = (unsigned char *)malloc(olen);

		if (out == nullptr)
			return false;

		const unsigned char *end = src + len;
		const unsigned char *in = src;
		unsigned char *pos = out;
//		int line_len = 0;
		while (end - in >= 3)
		{
			*pos++ = base64_table[in[0] >> 2];
			*pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
			*pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
			*pos++ = base64_table[in[2] & 0x3f];
			in += 3;
	/*		line_len += 4;
			if (line_len >= 72)
			{
				*pos++ = '\n';
				line_len = 0;
			}*/
		}

		if (end - in)
		{
			*pos++ = base64_table[in[0] >> 2];
			if (end - in == 1)
			{
				*pos++ = base64_table[(in[0] & 0x03) << 4];
				*pos++ = '=';
			}
			else
			{
				*pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
				*pos++ = base64_table[(in[1] & 0x0f) << 2];
			}
			*pos++ = '=';
			//line_len += 4;
		}

		//if (line_len) *pos++ = '\n';

		*pos = '\0';

		*out_len = pos - out;
		*outBuffer = out;
		return true;
	}



}