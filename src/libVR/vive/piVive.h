#pragma once

#include "../piVR.h"

namespace piLibs {

class piVRVive : public piVR
{
public:
    bool      Init(const char * appID);
    void      DeInit(void);
    piVRHMD  *CreateHmd(int deviceID, float pixelDensity);
    void      DestroyHmd(piVRHMD * me);
	void GetLastError(char* errorString);
};


}