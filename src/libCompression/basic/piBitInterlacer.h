#pragma once

#include "../../libSystem/piTypes.h"

namespace piLibs {

	namespace piBitInterlacer
	{
		class BitStream
		{
		public:
			BitStream();
			bool output(int bit, uint8_t *val);
			bool flush(uint8_t *val);

		private:
			int mBits;
			int mState;
		};


		int  interlace16(uint8_t *dst, const uint16_t *data, int numPoints, int numChannels, int numBits);
		int  interlace32(uint8_t *dst, const uint32_t *data, int numPoints, int numChannels, int numBits);

		void deinterlace(const uint8_t *src, uint16_t *data, int numBytes, int numPoints, int numChannels, int numBits);
	}


} // namespace piLibs