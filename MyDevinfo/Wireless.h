// WireLess.h

//you may use the ITC function call on Int*rm*c devices only, 
//so define USEWIFIPEEK to use a generic function
#define USEWIFIPEEK
//#undef USEWIFIPEEK

#ifdef USEWIFIPEEK
	#include "WifiPeek.h"
#endif

//extern TCHAR strMessage[MAX_PATH];
//extern int valMessage;
extern const WORD WM_UPDATESIGNAL; //

#define UNKNOWERROR -250
#define LOADLIBFAILED -251
#define CONNECTFAILED -252
#define QUERYFAILED -253
#define SCANNING -254
#define NOTASSOCIATED -255

#ifndef USEWIFIPEEK
	HINSTANCE hLib=NULL;

	// signalstrength
	typedef UINT (*PFN_GetRSSI) (ULONG &signalStrength);
	PFN_GetRSSI	GetRSSI = NULL;
	#define ERR_CONNECT_FAILED						0xC0000003		// Failure when trying to connect to the NIC
	#define ERR_QUERY_FAILED						0xC0000004		// Generic Query Failure

	// association
	typedef UINT (*PFN_GetAssociationStatus) (ULONG &Status);
	PFN_GetAssociationStatus	GetAssociationStatus = NULL;
	#define NDIS_RADIO_ASSOCIATED					0	// the radio is associated with a network
	#define NDIS_RADIO_SCANNING						1	// the radio is looking for a network to associate with

	//==================================================================
	int loadLib(){
		hLib = LoadLibrary(L"80211api.dll");
		if (hLib != NULL){
			GetRSSI = (PFN_GetRSSI) GetProcAddress(hLib, _T("GetRSSI"));
			if (GetRSSI==NULL)
				return -2;
			GetAssociationStatus = (PFN_GetAssociationStatus) GetProcAddress(hLib, _T("GetAssociationStatus"));
			if (GetAssociationStatus==NULL)
				return -3;
			return 0;
		}
		else
			return -1;
	}

	int freeLib(){
		if(hLib != NULL)
			FreeLibrary(hLib);
		return 0;
	}

	/*
		get RSSI signal strength
	*/
	ULONG getSignalStrength() 
	{
		static ULONG signalStrength=0;
		UINT uRes=-1;
		if (hLib!=NULL){
			if (GetRSSI != NULL){
				uRes = GetRSSI(signalStrength);
				if(uRes == ERROR_SUCCESS) {
	//				wsprintf(strMessage, L"%i", signalStrength);
	//				valMessage = signalStrength;
					return signalStrength;
				}
				else{
					if (uRes==ERR_CONNECT_FAILED){
						return CONNECTFAILED;
						//wsprintf(strMessage, L"cf"); //connect failed
					}
					if (uRes==ERR_QUERY_FAILED){
						return QUERYFAILED;
						//wsprintf(strMessage, L"qf"); //query failed
					}
					return UNKNOWERROR;
				}
			}
			else{
				return LOADLIBFAILED; //GetRSSI
			}
		}
		else{
			return LOADLIBFAILED;
		}
	}

	ULONG GetCurrentValue(){
		static ULONG uAssociationStatus=0;
		UINT uRes=-1;
		if(hLib==NULL)
			loadLib();
		if (hLib!=NULL){
			if (GetAssociationStatus != NULL){
				uRes = GetAssociationStatus(uAssociationStatus);
				if(uRes == ERROR_SUCCESS){
					if (uAssociationStatus == NDIS_RADIO_ASSOCIATED){
						return getSignalStrength();
					}
					else
					{
						return NOTASSOCIATED;
						//wsprintf(strMessage, L"scanning");
						//valMessage = SCANNING;
					}
				}
				else{
					return NOTASSOCIATED;
				}
			}
			else{
				return LOADLIBFAILED;
			}
		}
		else{
			return LOADLIBFAILED;
		}
	}

#else

	//for WiFi Peek usage
	//////////////////////////////////////////////////////////////////////////
	INT GetSignalStrength(TCHAR *ptcDeviceName, INT *piSignalStrength)
	{
		PNDISUIO_QUERY_OID queryOID;
		DWORD dwBytesReturned = 0;
		UCHAR QueryBuffer[sizeof(NDISUIO_QUERY_OID)+sizeof(DWORD)];
		HANDLE ndisAccess = INVALID_HANDLE_VALUE;
		BOOL retval;
		INT hr;

		// Attach to NDISUIO.
		ndisAccess = CreateFile(NDISUIO_DEVICE_NAME, 0, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		INVALID_HANDLE_VALUE );

		if (ndisAccess == INVALID_HANDLE_VALUE) 
			return -1;

		// Get Signal strength
		queryOID = (PNDISUIO_QUERY_OID)&QueryBuffer[0];
		queryOID->ptcDeviceName = ptcDeviceName;
		queryOID->Oid = OID_802_11_RSSI;

		retval = DeviceIoControl(ndisAccess,
		IOCTL_NDISUIO_QUERY_OID_VALUE, (LPVOID)queryOID,
		sizeof(NDISUIO_QUERY_OID) + sizeof(DWORD), (LPVOID)queryOID,
		sizeof(NDISUIO_QUERY_OID) + sizeof(DWORD), &dwBytesReturned, NULL);

		if (retval && piSignalStrength)
		{
			hr = 0;
			*piSignalStrength = *(DWORD *)&queryOID->Data;
		}
		else
		{
			hr = -2;
		}

		CloseHandle(ndisAccess);

		return(hr);
	}

	CWifiPeek m_wp;
	TCHAR* szAdapterName=new TCHAR[64];

	ULONG GetCurrentValue(){
		WCHAR buf[1024];
		DWORD dwSize;
		dwSize=sizeof(buf);
		if(false == m_wp.GetAdapters(buf, dwSize) || dwSize == 0)
		{
			return UNKNOWERROR;
		}
		else{
			//we are only interested in first returned name
			wsprintf(szAdapterName, L"%s", buf);
			int iRSSI=0;
			int iRes = GetSignalStrength(szAdapterName, &iRSSI);
			if(iRes == ERROR_SUCCESS){
				return iRSSI;
			}
			else{
				return LOADLIBFAILED;
			}
		}
	}
#endif


int showTaskBar(bool bShow){
	HWND hWndTB=NULL;
	hWndTB = FindWindow(L"HHTaskBar", NULL);
	if (hWndTB != NULL){
		if(bShow)
			ShowWindow(hWndTB, SW_SHOW);
		else
			ShowWindow(hWndTB, SW_HIDE);
	}
	return 0;
}

int reorderTaskBar(HWND hWnd){
	return 0;

	HWND hWndTB=NULL;
	//hWndTB = GetDesktopWindow(); //other windows will not show, except for today screen!
	hWndTB = FindWindow(L"HHTaskBar", NULL);
	//GetWindow(hWndTB, GW_HWNDFIRST);
	if (hWndTB != NULL){
		SetWindowPos(hWndTB, hWnd, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		return 0;
	}
	else 
		return -1;
}

int bringToFront(HWND hWnd){
	return SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
}


