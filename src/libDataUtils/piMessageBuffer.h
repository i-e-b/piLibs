#pragma once

#include <cstdint>
#include "piString.h"
//#include "piLibs/include/libSystem/piStr.h"
//#include "piLibs/include/libMath/piVecTypes.h"

using namespace piLibs;


class piMessageBuffer
{
public:
	piMessageBuffer();
	~piMessageBuffer();

	bool Init(int maxSize);
	void End(void);

	// for the worker
	void Reset(void);
	void StartMessage(int messageID); // no id returned - only one client can push messages at a time
		void AddUInt8(const uint8_t v);
		void AddUInt8V(const uint8_t *v, const int num);
		void AddUInt16(const uint16_t v);
		void AddUInt16V(const uint16_t *v, const int num);
		void AddUInt32(const uint32_t v);
		void AddUInt32V(const uint32_t *v, const int num);
		void AddUInt64(const uint64_t v);
		void AddUInt64V(const uint64_t *v, const int num);
		void AddBoolean(const bool v);
		void AddFloat(const float v);
		void AddFloatV(const float *v, const int num);
		void AddDouble(const double v);
		void AddDoubleV(const double *v, const int num);
		void AddCString(const char *str, int length);
		void AddWString(const wchar_t *str, int length);
		void AddPString(const piString & str);
	void EndMessage(void);

	// for the consumer
	const int  GetNumMessages(void) const;
	const void * GetMessages(void) const;

private:
	bool iPreAlloc(unsigned int num);

private:
	unsigned char *mBuffer;
	unsigned int  mMaxBytes;
	unsigned int  mNumBytes;
	unsigned int  mNumMessages;
};