#include <windows.h>

#include "regMyDevInfo.h"

static TCHAR wifiname[MAX_PATH];

#define regSubkey L"Software\\MyDevInfo"
#define regname L"AdapterName"
/*
see L"HKEY_LOCAL_MACHINE\\System\\State\\Connections\\Network:Adapters"
for Name of WiFi adapter to be used
*/

TCHAR* getModelInfo(){
	DEBUGMSG(1, (L"getModelInfo()...\n"));
	static TCHAR modellinfo[MAX_PATH];
	wsprintf(modellinfo, L"");
	TCHAR origname[64];
	TCHAR name[64];
	HKEY hKey;
	long lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Ident", 0, KEY_ALL_ACCESS, &hKey);
	if(lRes==ERROR_SUCCESS){
		DEBUGMSG(1, (L"getModelInfo() Ident RegOpenKeyEx OK\n"));
		DWORD dwType=REG_SZ;
		DWORD dwCount=64;
		BYTE* buf=(BYTE*)malloc(dwCount);
		long lRes = RegQueryValueEx(hKey, L"OrigName", 0, &dwType, buf, &dwCount);
		if(lRes==ERROR_SUCCESS){
			wsprintf(origname, L"%s", buf);
			DEBUGMSG(1, (L"getModelInfo() RegQueryValueEx OrigName=%s\n", origname));
		}
		else
			DEBUGMSG(1, (L"getModelInfo() RegQueryValueEx OrigName failed %i\n", GetLastError()));

		dwCount=64;
		memset(buf, 0, dwCount);
		dwType=REG_SZ;
		lRes = RegQueryValueEx(hKey, L"Name", 0, &dwType, buf, &dwCount);
		if(lRes==ERROR_SUCCESS){
			wsprintf(name, L"%s", buf);
			DEBUGMSG(1, (L"getModelInfo() RegQueryValueEx Name=%s\n", name));
		}
		else
			DEBUGMSG(1, (L"getModelInfo() RegQueryValueEx Name failed %i\n", GetLastError()));

		wsprintf(modellinfo, L"%s %s", origname, name);
		
		DEBUGMSG(1, (L"getModelInfo() done: '%s'\n", modellinfo));

		RegCloseKey(hKey);
		free(buf);
	}
	else{
		DEBUGMSG(1, (L"regReadNetAdapter RegOpenKeyEx failed: %i\n", GetLastError()));
		wsprintf(modellinfo, L"unknown");
	}
	return modellinfo;
}

TCHAR* regReadNetAdapter(){
	static TCHAR netAdapter[MAX_PATH];
	wsprintf(netAdapter, L"");
	HKEY hKey;
	long lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"System\\State\\Connections\\Network", 0, KEY_ALL_ACCESS, &hKey);
	if(lRes==ERROR_SUCCESS){
		DWORD dwType=REG_SZ;
		DWORD dwCount=MAX_PATH;
		BYTE* buf=(BYTE*)malloc(dwCount);
		long lRes = RegQueryValueEx(hKey, L"Adapters", 0, &dwType, buf, &dwCount);
		if(lRes==ERROR_SUCCESS){
			wsprintf(netAdapter, L"%s", buf);
		}
		RegCloseKey(hKey);
		free(buf);
	}
	else{
		DEBUGMSG(1, (L"regReadNetAdapter RegOpenKeyEx failed: %i\n", GetLastError()));
	}
	return netAdapter;
}

TCHAR* getWifiAdapterName(){

	if(wcslen(wifiname)==0){
		HKEY hKey=NULL;
		DWORD dwDispo=0;
		long lRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regSubkey, 
			0, NULL, 
			REG_OPTION_NON_VOLATILE, //dwOptions
			KEY_ALL_ACCESS, //SAM
			NULL, //security
			&hKey, &dwDispo);
		if(dwDispo==REG_OPENED_EXISTING_KEY){
			DEBUGMSG(1, (L"Software\\MyDevInfo opened existing key\n"));
			DWORD dwType=REG_SZ;
			DWORD dwCount=MAX_PATH;
			BYTE* buf=(BYTE*)malloc(dwCount);
			long lRes = RegQueryValueEx(hKey, regname, 0, &dwType, buf, &dwCount);
			if(lRes==ERROR_SUCCESS){
				wsprintf(wifiname, L"%s", buf);
			}
			else{
				DEBUGMSG(1, (L"RegQueryValueEx %s:%s failed: %i\n", regSubkey, regname, GetLastError()));
			}
		}
		else if(dwDispo==REG_CREATED_NEW_KEY){
			DEBUGMSG(1, (L"Software\\MyDevInfo opened new key\n"));
			wsprintf(wifiname, L"%s", regReadNetAdapter());
			long lRes=RegSetValueEx(hKey, regname, 0, REG_SZ, (BYTE*)wifiname, (wcslen(wifiname)+1)*sizeof(TCHAR));
			if(lRes==ERROR_SUCCESS){
				DEBUGMSG(1, (L"RegSetValueEx %s: OK for %s to %s\n", regSubkey, regname, wifiname));
			}
			else{
				DEBUGMSG(1, (L"RegSetValueEx Software\\MyDevInfo failed: %i\n", GetLastError()));
			}
		}
		RegCloseKey(hKey);
	}
	else{
		//just return known name
	}
	return wifiname;
}
