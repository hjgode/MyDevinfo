#include "GetRSSI.h"

int m_currentRSSI=0;

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

		if (ndisAccess == INVALID_HANDLE_VALUE) {
			DEBUGMSG(1, (L"Could not open file %s\n", NDISUIO_DEVICE_NAME));
			return -1;
		}

		// Get Signal strength
		queryOID = (PNDISUIO_QUERY_OID)&QueryBuffer[0];
		queryOID->ptcDeviceName = ptcDeviceName;
		queryOID->Oid = OID_802_11_RSSI;

		retval = DeviceIoControl(ndisAccess, IOCTL_NDISUIO_QUERY_OID_VALUE, (LPVOID)queryOID, sizeof(NDISUIO_QUERY_OID) + sizeof(DWORD), (LPVOID)queryOID, sizeof(NDISUIO_QUERY_OID) + sizeof(DWORD), &dwBytesReturned, NULL);

		if (retval && piSignalStrength)  //test if piSignalStrength is not NULL
		{
			*piSignalStrength = *(DWORD *)&queryOID->Data;
			DEBUGMSG(1, (L"DeviceIoControl OK, RSSI=%i\n", *piSignalStrength));
			hr = 0;
		}
		else
		{
			DEBUGMSG(1, (L"DeviceIoControl failed %i\n", GetLastError()));
			if(retval==ERROR_GEN_FAILURE)
				DEBUGMSG(1, (L"A device attached to the system is not functioning.\n"));

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
			DEBUGMSG(1, (L"calling GetSignalStrength() for '%s'\n", szAdapterName));
			int iRes = GetSignalStrength(szAdapterName, &iRSSI);
			DEBUGMSG(1, (L"... GetSignalStrength() iRes=%i for '%s', RSSI=%i\n", iRes, szAdapterName, iRSSI));
			if(iRes == ERROR_SUCCESS){
				return iRSSI;
			}
			else{
				return LOADLIBFAILED;
			}
		}
	}

int my_getRSSI(){
	ULONG uRes = 0;
	uRes=GetCurrentValue();
	if(uRes>UNKNOWERROR)
		m_currentRSSI=(int)uRes;
	DEBUGMSG(1, (L"+++ my_getRSSI=%i\n", m_currentRSSI));
	return m_currentRSSI;
}

