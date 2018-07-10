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

char* my_getLocalMAC(){	
	// Get a handle to the 80211 API
	if(h802lib == NULL)
		h802lib = LoadLibrary(_T("80211api.dll"));
	if(h802lib != NULL && GetMac == NULL){
		GetMac = (PFN_GetMac)GetProcAddress(h802lib, _T("GetMac"));
	}
	static TCHAR our_mac[128];
	static char our_mac_c[128];
	wsprintf(our_mac, L"");

	if(GetMac!=NULL){
		GetMac(our_mac);
	}else{
		wsprintf(our_mac, L"no80211api");
	}
	wcstombs(our_mac_c, our_mac, 128);
	return our_mac_c;
}