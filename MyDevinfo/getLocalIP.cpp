#include <windows.h>
#include <winsock2.h>
#pragma comment (lib, "ws2.lib")

#include "getLocalIP.h"

static char szLocalIP[16];

char* my_getLocalIP()
{
    WSADATA wsa_Data;
    WCHAR pWideCharStr[80];
    int wsa_ReturnCode = WSAStartup(0x202,&wsa_Data);
    char szHostName[255];
    gethostname(szHostName, 255);
    struct hostent *host_entry;
    host_entry=gethostbyname(szHostName);
    char * _szLocalIP;
	if(host_entry!=NULL){
		_szLocalIP = inet_ntoa (*(struct in_addr *)*host_entry->h_addr_list);
		strncpy(szLocalIP, _szLocalIP, 16);
		MultiByteToWideChar(CP_ACP, 0,_szLocalIP , -1,pWideCharStr , sizeof(pWideCharStr) / sizeof(wchar_t));
		DEBUGMSG(1, (L"getLocalIP='%s'", pWideCharStr));
		DEBUGMSG(1, (L"h_length=%i\n",host_entry->h_length)); //The length, in bytes, of each address.
	}
	else{
		DEBUGMSG(1, (L"gethostbyname error=%i\nlocalIP set to 0.0.0.0\n", WSAGetLastError()));
		printf(szLocalIP, "0.0.0.0");
	}
    WSACleanup();
    return szLocalIP;
}
