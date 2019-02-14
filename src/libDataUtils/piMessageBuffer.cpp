#include <malloc.h>
#include <string.h>
#include "piMessageBuffer.h"

piMessageBuffer::piMessageBuffer()
{
}
piMessageBuffer::~piMessageBuffer()
{
}

bool piMessageBuffer::Init(int maxSize)
{
	mMaxBytes = maxSize;
	mNumBytes = 0;
	mBuffer = (unsigned char*)malloc(maxSize);
	if (!mBuffer)
		return false;
	return true;
}
void piMessageBuffer::End(void)
{
	free(mBuffer);
}

void piMessageBuffer::Reset(void)
{
	mNumBytes = 0;
	mNumMessages = 0;
}


//----------------------------------------------------------------
bool piMessageBuffer::iPreAlloc(unsigned int num)
{
	if ((mNumBytes + num)>mMaxBytes)
	{
		unsigned int newmax = 4* mMaxBytes /3;
		if (newmax<4) newmax = 4;
		mBuffer = (unsigned char*)realloc(mBuffer, newmax);
		if (!mBuffer)
			return false;
		mMaxBytes = newmax;
	}
	return true;
}


void piMessageBuffer::StartMessage(int messageID)
{
	AddUInt32(messageID);
}

void piMessageBuffer::EndMessage(void)
{
	mNumMessages++;
}

void piMessageBuffer::AddFloat(const float v)
{
	const int len = sizeof(float);
	iPreAlloc(len);
	*((float*)(mBuffer + mNumBytes)) = v;
	mNumBytes += len;
}
void piMessageBuffer::AddFloatV(const float *v, const int num)
{
	const int len = num * sizeof(float);
	iPreAlloc(len);
	memcpy((float*)(mBuffer + mNumBytes), v, len);
	mNumBytes += len;
}
void piMessageBuffer::AddDouble(const double v)
{
	const int len = sizeof(double);
	iPreAlloc(len);
	*((double*)(mBuffer + mNumBytes)) = v;
	mNumBytes += len;
}
void piMessageBuffer::AddDoubleV(const double *v, const int num)
{
	const int len = num * sizeof(double);
	memcpy((double*)(mBuffer + mNumBytes), v, len);
	mNumBytes += len;
}
void piMessageBuffer::AddUInt8(const uint8_t v)
{
	const int len = sizeof(uint8_t);
	iPreAlloc(len);
	*((uint8_t*)(mBuffer + mNumBytes)) = v;
	mNumBytes += len;
}
void piMessageBuffer::AddUInt8V(const uint8_t *v, const int num)
{
	const int len = num * sizeof(uint8_t);
	iPreAlloc(len);
	memcpy((uint8_t*)(mBuffer + mNumBytes), v, len);
	mNumBytes += len;
}
void piMessageBuffer::AddUInt16(const uint16_t v)
{
	const int len = sizeof(uint16_t);
	iPreAlloc(len);
	*((uint16_t*)(mBuffer + mNumBytes)) = v;
	mNumBytes += len;
}
void piMessageBuffer::AddUInt16V(const uint16_t *v, const int num)
{
	const int len = num * sizeof(uint16_t);
	iPreAlloc(len);
	memcpy((uint16_t*)(mBuffer + mNumBytes), v, len);
	mNumBytes += len;
}
void piMessageBuffer::AddUInt32(const uint32_t v)
{
	const int len = sizeof(uint32_t);
	iPreAlloc(len);
	*((uint32_t*)(mBuffer + mNumBytes)) = v;
	mNumBytes += len;
}
void piMessageBuffer::AddUInt32V(const uint32_t *v, const int num)
{
	const int len = num * sizeof(uint32_t);
	iPreAlloc(len);
	memcpy((uint32_t*)(mBuffer + mNumBytes), v, len);
	mNumBytes += len;
}
void piMessageBuffer::AddUInt64(const uint64_t v)
{
	const int len = sizeof(uint64_t);
	iPreAlloc(len);
	*((uint64_t*)(mBuffer + mNumBytes)) = v;
	mNumBytes += len;
}
void piMessageBuffer::AddUInt64V(const uint64_t *v, const int num)
{
	const int len = num * sizeof(uint64_t);
	iPreAlloc(len);
	memcpy((uint64_t*)(mBuffer + mNumBytes), v, len);
	mNumBytes += len;
}

void piMessageBuffer::AddBoolean(const bool v)
{
	AddUInt8( (v) ? 1 : 0 );
}
void piMessageBuffer::AddCString(const char * str, int num)
{
	AddUInt32(num);
	AddUInt8V( (uint8_t*)str, num);
}
void piMessageBuffer::AddWString(const wchar_t * str, int num)
{
	AddUInt32(num);
	AddUInt16V((uint16_t*)str, num);
}
void piMessageBuffer::AddPString(const piString & str)
{
	const int num = str.GetLength();
	AddUInt32(num);
	AddUInt16V((uint16_t*)str.GetS(), num);
}

const int piMessageBuffer::GetNumMessages(void) const
{
	return mNumMessages;
}
const void *piMessageBuffer::GetMessages(void) const
{
	return mBuffer;
}
