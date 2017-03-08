#include "battery.h"

int getBatteryPercent(){
	SYSTEM_POWER_STATUS_EX spex;
	memset(&spex, 0, sizeof(SYSTEM_POWER_STATUS_EX));	
	BOOL bRes = GetSystemPowerStatusEx(&spex, TRUE);
	if(bRes){
		//return spex.BackupBatteryLifePercent;
		DEBUGMSG(1, (L"+++ BatteryLifePercent=%i\n", spex.BatteryLifePercent));
		return spex.BatteryLifePercent;
	}
	else{
		DWORD dwRes=GetLastError();
		DEBUGMSG(1, (L"GetSystemPowerStatusEx() Error; %i\n", dwRes));
	}
	return -1;
}