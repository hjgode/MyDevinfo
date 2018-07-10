//getLocalIP.h

#ifndef _GETLOCALIP_H_
#define _GETLOCALIP_H_

typedef UINT (*PFN_GetMac)(TCHAR *);
static PFN_GetMac GetMac=NULL;
static HINSTANCE h802lib=NULL;

char* my_getLocalIP();
char* my_getLocalMAC();

#endif