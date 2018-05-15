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
    _szLocalIP = inet_ntoa (*(struct in_addr *)*host_entry->h_addr_list);
	strncpy(szLocalIP, _szLocalIP, 16);

    MultiByteToWideChar(CP_ACP, 0,_szLocalIP , -1,pWideCharStr , sizeof(pWideCharStr) / sizeof(wchar_t));

    //MultiByteToWideChar(CP_UTF8, MB_COMPOSITE,szLocalIP , 32, pWideCharStr,32);
    MessageBox(NULL,pWideCharStr, TEXT("IP address"), MB_OK|MB_ICONERROR);

    WSACleanup();
    return szLocalIP;
}
