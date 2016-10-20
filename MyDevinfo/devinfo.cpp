#include "devinfo.h"
#include "oemioctl.h"

TCHAR modelCode[MAX_BUFF];
char modelCodeA[MAX_BUFF];

extern "C" BOOL KernelIoControl(DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned);

//BOOL KernelIoControl( IOCTL_HAL_GET_DEVICE_INFO, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned );
//BOOL KernelIoControl( IOCTL_HAL_ITC_READ_PARM,LPVOID lpInBuf,DWORD nInBufSize,LPVOID lpOutBuf,DWORD nOutBufSize,LPDWORD lpBytesReturned );
//struct PARMS {
//	BYTE id;
//	BYTE ClassId;
//};

char* getModelCode(){
	wsprintf(modelCode, L"-");
	sprintf(modelCodeA, "-");
	BYTE buf[MAX_BUFF];
	PARMS parms;
	parms.id= ITC_NVPARM_MCODE;
	DWORD dwSizeReturned=0;
	BOOL bRes = KernelIoControl(IOCTL_HAL_ITC_READ_PARM, &parms, sizeof(PARMS), &buf, MAX_BUFF, &dwSizeReturned);
	if(bRes){
		mbstowcs((TCHAR*)&modelCode, (char*)&buf, MAX_BUFF);
		DEBUGMSG(1, (L"Get Model OK: '%s'\n", modelCode));
		sprintf(modelCodeA, "%s", (char*)buf);
	}
	else{
		DEBUGMSG(1, (L"Get Model failed: %i\n", GetLastError()));
	}
	return modelCodeA;
}
