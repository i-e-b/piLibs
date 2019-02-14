#include <malloc.h>
#include "../../libSystem/piTypes.h"
#include "piBitInterlacer.h"

namespace piLibs
{
	namespace piBitInterlacer
	{

		BitStream::BitStream()
		{
			mBits = 0;
			mState = 0;
		}

		bool BitStream::output(int bit, uint8_t *res)
		{
			mState |= (bit << mBits);

			mBits++;
			if (mBits == 8)
			{
				*res = mState;
				mBits = 0;
				mState = 0;
				return true;
			}
			return false;
		}

		bool BitStream::flush(uint8_t *val)
		{
			if (mBits != 0)
			{
				*val = mState;
				return true;
			}
			return false;
		}


		int interlace16(uint8_t *dst, const uint16_t *data, int numPoints, int numChannels, int numBits)
		{
			// interlace all bits, sort bits from lower to higher bits across channels
			int num = 0;
			BitStream bit;
			for (int b = 0; b < numBits; b++)
				for (int j = 0; j < numChannels; j++)
					for (int i = 0; i < numPoints; i++)
					{
						uint8_t res;
						if (bit.output((data[numChannels*i + j] >> b) & 1, &res))
							dst[num++] = res;
					}

			uint8_t res; if (bit.flush(&res)) dst[num++] = res;

			// remove trailing zeroes
			int len = 0;
			for (int i = num - 1; i>0; i--)
			{
				if (dst[i] != 0)
				{
					len = i + 1;
					break;
				}
			}


			return len;
		}

		int interlace32(uint8_t *dst, const uint32_t *data, int numPoints, int numChannels, int numBits)
		{
			// interlace all bits, sort bits from lower to higher bits across channels
			int num = 0;
			BitStream bit;
			for (int b = 0; b < numBits; b++)
			for (int j = 0; j < numChannels; j++)
			for (int i = 0; i < numPoints; i++)
			{
				uint8_t res;
				if (bit.output((data[numChannels*i + j] >> b) & 1, &res))
					dst[num++] = res;
			}

			uint8_t res; if (bit.flush(&res)) dst[num++] = res;

			// remove trailing zeroes
			int len = 0;
			for (int i = num - 1; i>0; i--)
			{
				if (dst[i] != 0)
				{
					len = i + 1;
					break;
				}
			}

			return len;
		}

		void deinterlace(const uint8_t *src, uint16_t *data, int numBytes, int numPoints, int numChannels, int numBits)
		{
			for (int i = 0, num=numPoints*numChannels; i < num; i++)
			{
				data[i] = 0;
			}

			int bit = 0;
			int channel = 0;
			int point = 0;

			for (int i = 0; i < numBytes; i++)
			{
				const uint8_t byte = src[i];

				for (int j = 0; j < 8; j++)
				{
					const int b = (byte >> j) & 1;

					data[numChannels*point + channel] |= (b << bit);
					point++;
					if (point >= numPoints)
					{
						point = 0;
						channel++;
						if (channel >= numChannels)
						{
							channel = 0;
							bit++;
							if (bit >= numBits)
							{
								bit = 0;
								return;
							}
						}
					}
				}
			}
		}
	}

}