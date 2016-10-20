#ifndef __OEMIOCTL_H__
#define __OEMIOCTL_H__

/* Copyright © 2000-2001 Intel Corp.  */
/*++

Module Name:  $Workfile: oemioctl.h $

Abstract:
 Contains definitions specific to Intel XScale
 Microarchitecture OEMIOcontrol calls.

--*/

#include <winioctl.h>

//------------------------------------------------------------------------------------------------------------
// NOTE:  IF YOU ADD OR CHANGE AN IOCTL, ALSO ADD/CHANGE IT IN OEMIOCTLPRIV.H.
// THIS HELPS DEVELOPERS WHEN THEY ARE ADDING NEW VALUES, AND WILL ALSO THROW COMPILER WARNINGS IF SOMEONE 
// CHANGES AN EXISTING VALUE.  NOTE THAT THE IOCTLS IN THIS FILE WILL BE MADE VISIBLE TO CUSTOMERS IN THE SDK

#define CORE_OEM_IOCTL_BASE						0x800	// 0x800 - 0x8AF
#define IOCTL_HAL_GET_OAL_VERINFO				CTL_CODE( FILE_DEVICE_HAL, CORE_OEM_IOCTL_BASE + 0,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_GET_BOOTLOADER_VERINFO		CTL_CODE( FILE_DEVICE_HAL, CORE_OEM_IOCTL_BASE + 1,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_WARMBOOT						CTL_CODE( FILE_DEVICE_HAL, CORE_OEM_IOCTL_BASE + 4,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_COLDBOOT						CTL_CODE( FILE_DEVICE_HAL, CORE_OEM_IOCTL_BASE + 5,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_GET_BOOT_DEVICE				CTL_CODE( FILE_DEVICE_HAL, CORE_OEM_IOCTL_BASE + 22, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_GET_RESET_INFO				CTL_CODE( FILE_DEVICE_HAL, CORE_OEM_IOCTL_BASE + 23, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define PLATFORM_ITC_IOCTL_BASE					0x8B0	// 0x8B0 - 0xF9F
#define IOCTL_HAL_ITC_READ_PARM					CTL_CODE(FILE_DEVICE_HAL, PLATFORM_ITC_IOCTL_BASE + 1,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_NMSD_READ_PARM				CTL_CODE(FILE_DEVICE_HAL, PLATFORM_ITC_IOCTL_BASE + 1,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_ITC_READ_SYSPARM				CTL_CODE(FILE_DEVICE_HAL, PLATFORM_ITC_IOCTL_BASE + 4,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_ITC_WRITE_SYSPARM				CTL_CODE(FILE_DEVICE_HAL, PLATFORM_ITC_IOCTL_BASE + 5,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_ITC_READ_PARM_BYTE			CTL_CODE(FILE_DEVICE_HAL, PLATFORM_ITC_IOCTL_BASE + 28, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_RAM_APD							CTL_CODE(FILE_DEVICE_HAL, PLATFORM_ITC_IOCTL_BASE + 32, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_ITC_CLEAN_DEVICE	            CTL_CODE(FILE_DEVICE_HAL, PLATFORM_ITC_IOCTL_BASE + 60, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define PLATFORM_PMU_IOCTL_BASE					0xFA0	// 0xFA0 - 0xF
#define IOCTL_PMU_CONFIG						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 0,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_CPU_ID						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 1,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PMU_CCF							CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 2,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TURBO_MODE						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 3,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_CP_REGS						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 4,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_CP_REGS						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 5,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_FREQUENCY						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 6,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_FREQVOLT						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 7,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_VOLTAGE						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 8,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_FREQUENCY						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 9,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ENTER_TURBO						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 10, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_QUERY_DISPLAY_SETTINGS		CTL_CODE(FILE_DEVICE_HAL, PLATFORM_PMU_IOCTL_BASE + 11, METHOD_BUFFERED, FILE_ANY_ACCESS)

#if defined( BSP_IPSM )
#define PLATFORM_INTEL_IOCTL_BASE				0xFE0	// 0xFE0 - 0xFFF
#define IOCTL_PSM_FLASH_CMD						CTL_CODE(FILE_DEVICE_HAL, PLATFORM_INTEL_IOCTL_BASE + 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif




#if (0)
//-----------------------------------------------
// The following indicates which IOCTLS reference 
// the vars in OEMGlobals
//-----------------------------------------------

EEPROM.Config[16];					// ITC_NVPARM_MCODE
EEPROM.BCD_SerialNumber[6];			// ITC_NVPARM_SERIAL_NUM
EEPROM.BCD_ManufDate[4];			// ITC_NVPARM_MANF_DATE
EEPROM.BCD_LastRepairDate[4];		// ITC_NVPARM_SERVICE_DATE
EEPROM.AppliedECNs;					// ITC_NVPARM_ECN
EEPROM.Entropy[8];					// OCTL_HAL_SET_HWENTROPY, IOCTL_HAL_GET_HWENTROPY
EEPROM.atod_calibration;			// 
EEPROM.RTC_TrimValue;				// ITC_NVPARM_RTC_TRIM_VALUE
EEPROM.MfgTest;						// ITC_NVPARM_MFG_TEST
EEPROM._Reserved0[1];				// 
EEPROM.MacAddr[6];					// ITC_NVPARM_ETHERNET_ID
EEPROM._Reserved[2					// 

EEPROM.MaxTempExtreme;				//
EEPROM.MinTempExtreme;				//
EEPROM.MaxChargeVoltageExtreme;		// 
EEPROM.MinChargeVoltageExtreme;		// 
EEPROM.MaxBatteryVoltageExtreme;	// 
EEPROM.MinBatteryVoltageExtreme;	// 
EEPROM.MaxBackupVoltageExtreme;		// 
EEPROM.MinBackupVoltageExtreme;		// 
EEPROM._Reserved2[32];				// 

EEPROM.PenCalibData[8];			    // ITC_NVPARM_PEN_CALIBRATION
EEPROM.CPU_Freq;					// ITC_NVPARM_CPU_FREQUENCY
EEPROM.AudioCfgIndex;				// ITC_NVPARM_AUDIO_TYPE
EEPROM.KeyboardCfgIndex;			// ITC_NVPARM_KEYBOARD_TYPE, ITC_GET_KEYBOARD_TYPE
EEPROM.DisplayIndex;				// ITC_NVPARM_DISPLAY_TYPE
EEPROM.DisplayRefreshRate;			// ITC_NVPARM_DISPLAY_REFRESH_RATE
EEPROM.ScannerID;					// ITC_NVPARM_INTERMEC_DATACOLLECTION_HW
EEPROM.WANID;						// ITC_NVPARM_WAN_INSTALLED, ITC_NVPARM_WAN_RADIOTYPE, ITC_NVPARM_PERIPH_FLAGS
EEPROM.BTCfgIndex;					// ITC_NVPARM_BLUETOOTH_TYPE
EEPROM.MfgFlags[3];					// ITC_NVPARM_MANU_FLAGS, (plus many other bit references)
EEPROM.NetworkStartup;				// 
EEPROM.BluetoothStartup;			// 
EEPROM._80211Startup;				// 
EEPROM.RegSaveLocation;				// ITC_REGISTRY_LOCATION, ITC_REGISTRY_SAVE_ENABLE:
EEPROM.PrimaryBootDevice;			// ITC_NVPARM_BOOT_DEVICE
EEPROM.SecondaryBootDevice;			// TC_NVPARM_BOOT_DEVICE_SECONDARY
EEPROM.Password[4];					// ITC_SET_SYS_PASSWORD, ITC_GET_SYS_PASSWORD
EEPROM.KitlTransport;				// ITC_NVPARM_KITL_TRANSPORT
EEPROM.EtherDebug_IPAddress;		// ITC_NVPARM_EDG_IP
EEPROM.EtherDebug_SubnetMask;		// ITC_NVPARM_EDBG_SUBNET
EEPROM.WakeUpMask;					// ITC_WAKEUP_MASK
EEPROM.KitlSerialPort;				// ITC_NVPARM_KITL_SERIALPORT
EEPROM.DebugSerialPort;				// ITC_NVPARM_DEBUG_SERIALPORT
EEPROM._Reserved6[2];				// 
EEPROM.CDMA_Carrier_ID;				// ITC_NVPARM_CDMA_CARRIER_TYPE
EEPROM._Reserved4[63];				// 


EEPROM.VersionNumber[4];			// ITC_NVPARM_VERSION_NUMBER
EEPROM.FrontlightThreshold;			// ITC_AMBIENT_FRONTLIGHT_EEPROM
EEPROM.BacklightThreshold;			// ITC_AMBIENT_KEYBOARD_EEPROM
EEPROM.BacklightBrightness;			// 
EEPROM.ChargeDetectThreshold;		// 
EEPROM._Reserved5[8];				// 



MISC.BL_major_ver;					// IOCTL_HAL_GET_BOOTLOADER_VERINFO, ITC_NVPARM_VERSION_NUMBER
MISC.BL_minor_ver;					// IOCTL_HAL_GET_BOOTLOADER_VERINFO, ITC_NVPARM_VERSION_NUMBER
MISC.BL_patch_ver;					// IOCTL_HAL_GET_BOOTLOADER_VERINFO
MISC.BL_build_ver;					// IOCTL_HAL_GET_BOOTLOADER_VERINFO
MISC.UP_major_ver;					// 
MISC.UP_minor_ver;					// 
MISC.dwDRamSz;						// ITC_GET_RAM_SIZE
MISC.RomSize;						// ITC_GET_ROM_SIZE
MISC.RomType;						// 
MISC.BootDevice;					// IOCTL_HAL_GET_BOOT_DEVICE
MISC.bootstrap_bootflag;			// 
MISC.CEEntryPoint;					// 
MISC.ce_loaded_once;				// 
MISC.resetreason;					// IOCTL_HAL_GET_RESET_INFO
MISC.kb_resume_key;					// 
MISC.wakeup_source;					// IOCTL_HAL_GET_WAKE_SOURCE
MISC.critical_suspend;				// 
MISC.pwrfail_in_progress;			// 
MISC.inpowerhandler;				// 
MISC.mdrefr_shadow;					// 
MISC.bcrShadow;						// 
MISC.pwer_shadow;					// 
MISC.prer_shadow;					// 
MISC.pfer_shadow;					// 
MISC.BackLight;						// 
MISC.contrast;						// 
MISC.brightness;					// 
MISC.offButton;						// 
MISC.numSlots;						// 
MISC.critical_radio;				// 
MISC.scrreg;						// 
MISC.serialModemReg;				// 
MISC.USBCableEvent;    				// 
MISC.critical_atod;					// 
MISC.*mem_table;					// 
MISC.FPGA_Programmed;				// ITC_GET_FPGA_PROGRAMMED_STATUS
MISC.FPGA_PhysLoc;					// 
MISC.FPGA_Size;						// 
MISC.FPGA_ref_count;				// 
MISC.FPGA_dynclock_enable;			// 
MISC.CacheToggle;			        // 

#endif




//----------------------------------------------------------------------------
// Structures & definitions
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// IOCTL_HAL_ITC_READ_PARM_BYTE
// IOCTL_HAL_ITC_READ_PARM

typedef struct PARMS {
	BYTE	id;
	BYTE	ClassId;
}ITC_PARMS, *PITC_PARMS;

#define ITC_NVPARM_ETHERNET_ID					1	// EEPROM.Vars.MacAddr,					RW
#define ITC_NVPARM_SERIAL_NUM					2	// EEPROM.Vars.BCD_SerialNumber			RW
#define ITC_NVPARM_MANF_DATE					3	// EEPROM.Vars.BCD_ManufDate			RW
#define ITC_NVPARM_SERVICE_DATE					4	// EEPROM.Vars.BCD_LastRepairDate		RW
#define ITC_NVPARM_DISPLAY_TYPE					5	// EEPROM.Vars.DisplayIndex				RW
#define ITC_NVPARM_EDG_IP						6	// EEPROM.Vars.EtherDebug_IPAddress		RW
#define ITC_NVPARM_EDBG_SUBNET					7	// EEPROM.Vars.EtherDebug_SubnetMask	RW
#define ITC_NVPARM_ECN							8	// EEPROM.Vars.AppliedECNs				RW
#define ITC_NVPARM_CONTRAST						9	// Unsupported
#define ITC_NVPARM_MCODE						10	// EEPROM.Vars.Config,					RW
#define ITC_IRQS								11	// Unsupported
#define ITC_NVPARM_VERSION_NUMBER				14	// VN_CLASS_KBD	:      EEPROM.Vars.VersionNumber	R	***
													// VN_CLASS_ASIC:	   FPGA_REG600 					R	***
													// VN_CLASS_BOOTSTRAP: misc.BL_major_ver &			R 
													//                     misc.BL_minor_ver			R
													// VN_CLASS_MICRO:	   ReadMicroVersion()			R

	//----------------------------------------------------------------------
	#define VN_CLASS_KBD			1				
	#define VN_CLASS_ASIC			2				
	#define VN_CLASS_BOOTSTRAP		3
	#define VN_CLASS_MICRO			4
	//----------------------------------------------------------------------
		

#define ITC_NVPARM_SOFTWARE_FLAGS				15	// Unsupported
#define ITC_NVPARM_INTERMEC_SOFTWARE_CONTENT	16	// Unsupported (see next)
#define ITC_NVPARM_INTERMEC_BOOT_MODE			16	// EEPROM.Vars.MfgFlags[1] & ITC_MFLAG_CONTENT		RW
#define ITC_RTC_RESTORE_ENABLE					17	// Unsupported 
#define ITC_NVPARM_RTC_RESTORE					17	// Unsupported
#define ITC_NVPARM_WAKEUP_MASK					18	// EEPROM.Vars.WakeUpMask

	//----------------------------------------------------------------------
	// WakeUpMask definitions
	//
	// LEGACY definitions of these bits.  Still mapped to same locations.
	#define	SCANNER_TRIGGER						0x00000001		
	#define SCANNER_LEFT						0x00000002
	#define SCANNER_RIGHT						0x00000004
	#define GOLD_A1								0x00000008
	#define	GOLD_A2								0x00000010

	#define ITC_WAKEUP_MASK_KEYPAD_K07			0x00000001	// Center Scan	
	#define ITC_WAKEUP_MASK_KEYPAD_K00			0x00000002	// Left Scan, side of terminal
	#define ITC_WAKEUP_MASK_KEYPAD_K01			0x00000004	// Right Scan, side of terminal
	#define ITC_WAKEUP_MASK_KEYPAD_K03			0x00000008	// Left Side, on keypad
	#define ITC_WAKEUP_MASK_KEYPAD_K02			0x00000010	// Right Side, on keypad
	#define ITC_WAKEUP_MASK_KEYPAD_K04			0x00000020
	#define ITC_WAKEUP_MASK_KEYPAD_K05			0x00000040
	#define ITC_WAKEUP_MASK_KEYPAD_K06			0x00000080
	#define ITC_WAKEUPMASK_KEYPAD	(ITC_WAKEUP_MASK_KEYPAD_K00|ITC_WAKEUP_MASK_KEYPAD_K01|ITC_WAKEUP_MASK_KEYPAD_K02|ITC_WAKEUP_MASK_KEYPAD_K03|ITC_WAKEUP_MASK_KEYPAD_K04|ITC_WAKEUP_MASK_KEYPAD_K05|ITC_WAKEUP_MASK_KEYPAD_K06|ITC_WAKEUP_MASK_KEYPAD_K07)
	//----------------------------------------------------------------------
	

#define ITC_NVPARM_PHYSICAL_MEMORY				19	// Unsupported
#define ITC_NVPARM_ANTENNA_DIVERSITY			20	// EEPROM.Vars.MfgFlags[0] & ITC_MFLAG_DIVERSITY		RW
#define ITC_NVPARM_WAN_RI						21	// Unsupported
#define ITC_NVPARM_PERIPH_FLAGS					22	// (Multiple sources, see code)
#define ITC_NVPARM_SOFT_ENABLE_FLAGS			23	// EEPROM.Vars.MfgFlags[0] & ITC_MFLAG_RTC_RESTORE		RW
#define ITC_NVPARM_BOOT_DEVICE					24	// EEPROM.Vars.PrimaryBootDevice						RW
#define ITC_NVPARM_MIXER_DATA					25	// Unsupported

#define ITC_NVPARM_INTERMEC_DATACOLLECTION_HW	26	// EEPROM.Vars.ScannerID								RW
#define ITC_NVPARM_INTERMEC_DATACOLLECTION_SW	27	// EEPROM.Vars.MfgFlags[1] & ITC_MFLAG_DATACOLLECTION	RW
#define ITC_NVPARM_WAN_INSTALLED				28	// EEPROM.Vars.WANID									R
#define ITC_NVPARM_WAN_FREQUENCY				29	// EEPROM.Vars.MfgFlags[0] & ITC_MFLAG_US				RW
#define ITC_NVPARM_WAN_RADIOTYPE				30	// EEPROM.Vars.WANID									RW
#define ITC_NVPARM_80211_INSTALLED				31	// EEPROM.Vars.MfgFlags[0] & ITC_PFLAG_80211			R
#define ITC_NVPARM_80211_RADIOTYPE				32	// Fixed: ITC_DEVID_80211RADIO_NONE						R
#define ITC_NVPARM_BLUETOOTH_INSTALLED			33	// EEPROM.Vars.MfgFlags[0] & ITC_MFLAG_BLUETOOTH		RW
#define ITC_NVPARM_SERIAL2_INSTALLED			34	// Serial2DriverLoaded()								R
#define ITC_NVPARM_VIBRATE_INSTALLED			35	// EEPROM.Vars.MfgFlags[0] & ITC_MFLAG_VIBRATE			RW
#define ITC_NVPARM_LAN9000_INSTALLED			36	// Fixed : Returns TRUE
#define ITC_NVPARM_SIM_PROTECT_HW_INSTALLED		37	// EEPROM.Vars.MfgFlags[0] & ITC_MFLAG_SIMPROT			RW
#define ITC_NVPARM_SIM_PROTECT_SW_INSTALLED		38	// EEPROM.Vars.MfgFlags[0] & ITC_MFLAG_SIMPROT			RW
#define ITC_NVPARM_MANU_FLAGS					39	// EEPROM.Vars.MfgFlags[0]								R
#define ITC_NVPARM_EXTENDED_FLAGS				40	// Unsupported
// #define ITC_NVPARM_reserved					41	// 
#define ITC_NVPARM_MODEL_NUMBER					42	// Returns 
#define ITC_NVPARM_ZERO_CONFIG					43	// EEPROM.Vars.MfgFlags[0] & ITC_MFLAG_ZERO_CONFIG		RW
	
#define ITC_NVPARM_MODE_80211D					44	// Unsupported
#define ITC_NVPARM_NET_DEFAULT_STARTUP			45	// Unsupported

#define ITC_GET_SYSINTR_VALUE					46	// Unsupported
#define ITC_GET_KEYBOARD_TYPE					47	// EEPROM.Vars.KeyboardCfgIndex							R


#define ITC_NVPARM_RTC_TRIM_VALUE				48
#define ITC_NVPARM_MFG_TEST						49
#define ITC_NVPARM_PEN_CALIBRATION				50	
#define ITC_NVPARM_CPU_FREQUENCY				51	
#define ITC_NVPARM_AUDIO_TYPE					52	
#define ITC_NVPARM_KEYBOARD_TYPE				53	
#define ITC_NVPARM_DISPLAY_REFRESH_RATE			54
#define ITC_NVPARM_BLUETOOTH_TYPE				55
#define ITC_NVPARM_BOOT_DEVICE_SECONDARY		56
#define ITC_NVPARM_KITL_TRANSPORT				57
#define ITC_NVPARM_KITL_SERIALPORT				58
#define ITC_NVPARM_DEBUG_SERIALPORT				59
#define ITC_NVPARM_CDMA_CARRIER_TYPE			60

#define ITC_GET_RAM_SIZE						61
#define ITC_GET_ROM_SIZE						62
#define ITC_GET_FPGA_PROGRAMMED_STATUS	        63
#define ITC_NVPARM_LCDPANEL_TYPE                64  // JAC 10/21/2004
#define ITC_NVPARM_COM1_DTR_RTS					65
#define ITC_NVPARM_80211_REGDOMAINCODE			66
#define ITC_NVPARM_80211_BANDENABLE				67

#define ITC_PARM_CE_ENTRY_POINT				   100
#define ITC_PARM_RESET_REASON				   101




#define ITC_NET_START_AUTO		0
#define ITC_NET_START_ETHERNET	1
#define ITC_NET_START_WLAN		2
#define ITC_NET_START_DISABLED	3
#define ITC_NET_START_BOTH		4
#define ITC_NET_START_SWITCHED	5


#define ITC_DEVID_MASK					0x7F	// scanner device id's are stored in the lower 7 dev id bits
#define ITC_DEVID_S6ENGINE_MASK			0x80	// the s6 engine flag is stored in the high dev id bit
#define ITC_DEVID_SCANHW_NONE			0x00
#define ITC_DEVID_OEM2D_IMAGER			0x01
#define ITC_DEVID_INTERMEC2D_IMAGER		0x02
#define ITC_DEVID_SE900_LASER			0x03
#define ITC_DEVID_SE900HS_LASER			0x04
#define ITC_DEVID_INTERMEC_E1210		0x05
#define ITC_DEVID_INTERMEC_EV10			0x06
#define ITC_DEVID_INTERMEC_EL10			0x07
#define ITC_DEVID_INTERMEC_EV15			0x08
#define ITC_DEVID_SCANHW_HIGHEST		0x08  // Set to highest defined value
#define ITC_DEVID_SCANHW_MAX			0x7F	// This is the max value for scanner id's

#define ITC_DEVID_WANRADIO_NONE				0x00
#define ITC_DEVID_WANRADIO_SIERRA_SB555		0x01 // CDMA
#define ITC_DEVID_WANRADIO_XIRCOM_GEM3503	0x02 // GSM/GPRS
#define ITC_DEVID_WANRADIO_SIEMENS_MC45		0x03 // GSM/GPRS
#define ITC_DEVID_WANRADIO_UHF418_COM4		0x04 // periph board uart
#define ITC_DEVID_WANRADIO_UHF418_COM2		0x05 // cotulla uart
#define ITC_DEVID_WANRADIO_SIERRA_EM3420	0x06
#define ITC_DEVID_WANRADIO_SIEMENS_MC46		0x07 // GSM/GPRS
#define ITC_DEVID_WANRADIO_MAX				0x0F

#define ITC_CDMACARRIER_UNKNOWN			0
#define ITC_CDMACARRIER_VERIZON			1
#define ITC_CDMACARRIER_SPRINT			2
#define ITC_CDMACARRIER_TELUS			3
#define ITC_CDMACARRIER_BELLMOBILITY	4

#define ITC_DEVID_80211RADIO_NONE				0x00
#define ITC_DEVID_80211RADIO_INTEL_2011B		0x01
#define ITC_DEVID_80211RADIO_ACTIONTEC_802CFI3  0x02
#define ITC_DEVID_80211RADIO_ACTIONTEC_802USB   0x06
#define ITC_DEVID_80211RADIO_MAX				0x0F


#define    REG_DOMAIN_FCC     0x10
#define    REG_DOMAIN_IC      0x20
#define    REG_DOMAIN_ETSI    0x30
#define    REG_DOMAIN_SPAIN   0x31
#define    REG_DOMAIN_FRANCE  0x32
#define    REG_DOMAIN_MKK     0x40
#define    REG_DOMAIN_MKK1    0x41


// DRH 10/6/2003
#define ITC_80211D_MODE_NONE           0x00
#define ITC_80211D_MODE_STRICT         0x01
#define ITC_80211D_MODE_FLEXIBLE       0x02
#define ITC_80211D_MODE_INVALID        0x03

// Norand standard parameter ID's
#define APM_PARM_ETHERNET_ID		1	// Ethernet ID 6 bytes + 1 byte CRC.
#define APM_PARM_ETHERNET_LTH		6	// Ethernet ID length
#define APM_PARM_MANF_DATE			3	// Manf date. BCD: yymmdd.
#define APM_PARM_PEN_ALIGN_ID 		19	// Pen alignment id: 8 bytes at the moment.
#define APM_PARM_PEN_ALIGN_LTH		8	// Pen alignment length

// IOCTL_HAL_ITC_READ_PARM_BYTE
// IOCTL_HAL_ITC_READ_PARM
// END
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// IOCTL_HAL_ITC_READ_SYSPARM
// IOCTL_HAL_ITC_WRITE_SYSPARM

#define ITC_REGISTRY_LOCATION			1
#define	ITC_REGISTRY_SAVE_ENABLE		2
#define ITC_DOCK_SWITCH					3

	#define DOCK_MODEM					0x40	// Sets the switch to "0" (modem)
	#define DOCK_SERIAL					0		// Sets the switch to "1" (serial)

// This is for masking individual wakeup keys for the keypad (including scanner buttons which are 
// still processed by the keypad.  The individual bits are defined above for ITC_NVPARM_WAKEUP_MASK

#define ITC_WAKEUP_MASK					4
#define ITC_AMBIENT_KEYBOARD			5
#define ITC_AMBIENT_FRONTLIGHT			6
#define ITC_COMMIT_AMBIENT_KEYBOARD		7
#define ITC_COMMIT_AMBIENT_FRONTLIGHT	8
#define ITC_AMBIENT_KEYBOARD_EEPROM		9
#define ITC_AMBIENT_FRONTLIGHT_EEPROM	10
#define ITC_A2D							11
#define ITC_GET_SYSPARM_AUDIO           12
#define ITC_SET_SYSPARM_AUDIO			13
#define ITC_GET_SYS_PASSWORD			14
#define ITC_SET_SYS_PASSWORD			15
#define ITC_ENABLE_SYS_PASSWORD			16
#define ITC_IS_SYS_PASSWORD_ENABLED		17
#define ITC_MAINBOARD_TYPE_ID			18

	#define MAIN_BATT_A2D			1
	#define EXT_POWER_A2D			2
	#define CHG_CURR_A2D			3
	#define HEADSET_A2D				4
	#define AMBIENT_A2D				5

#define ITC_GET_SYSINTR_IMAGER          0		// imager dma interrupt sysintr
#define ITC_GET_SYSINTR_SCANNER_FPGA	1		// scanner fpga sysintr
#define ITC_GET_SYSINTR_SERIAL_FPGA		2		// serialA fpga sysintr

// IOCTL_HAL_ITC_READ_SYSPARM
// IOCTL_HAL_ITC_WRITE_SYSPARM
// END
//----------------------------------------------------------------------------


//
// IOCTL_HAL_ITC_CLEAN_DEVICE
//
#define ITC_CLEAR_RESTORE_FLAGS		 0
#define ITC_FORMAT_OBJECT_STORE		 ( 1 << CLEANBOOTFLAG_FORMAT_OBJECT_STORE )
#define ITC_FORMAT_SECONDARY_STORAGE ( 1 << CLEANBOOTFLAG_FORMAT_SECONDARY_STORAGE )
#define ITC_RESTORE_USER_HIVE		 ( 1 << CLEANBOOTFLAG_USERHIVE )
#define ITC_RESTORE_SYSTEM_HIVE		 ( 1 << CLEANBOOTFLAG_SYSTEMHIVE )
#define ITC_RESTORE_SYSTEM_TIME		 ( 1 << CLEANBOOTFLAG_DEFAULT_DATE )
#define ITC_CLEAN_BOOT				 ( ITC_FORMAT_OBJECT_STORE | ITC_RESTORE_USER_HIVE | ITC_RESTORE_SYSTEM_HIVE | ITC_RESTORE_SYSTEM_TIME )
//
// END: IOCTL_HAL_ITC_CLEAN_DEVICE
//


//----------------------------------------------------------------------------
// RAM APD Settings
//----------------------------------------------------------------------------
	#define ENABLE_APD	1
	#define DISABLE_APD	2
	#define QUERY_APD	3

//----------------------------------------------------------------------------
// IOCTL_HAL_GET_BOOT_DEVICE
#define HAL_BOOT_DEVICE_UNKNOWN			0
#define HAL_BOOT_DEVICE_ROM_XIP			1
#define HAL_BOOT_DEVICE_ROM				2
#define HAL_BOOT_DEVICE_PCMCIA_ATA		3
#define HAL_BOOT_DEVICE_PCMCIA_LINEAR	4
#define HAL_BOOT_DEVICE_IDE_ATA			5
#define HAL_BOOT_DEVICE_IDE_ATAPI		6
#define HAL_BOOT_DEVICE_ETHERNET		7
#define HAL_BOOT_DEVICE_80211b			8
#define HAL_BOOT_DEVICE_SDMMC			9

//----------------------------------------------------------------------------
// IOCTL_HAL_GET_RESET_INFO
typedef struct {
	DWORD ResetReason;		// type of the most recent reset
	DWORD ObjectStoreState;	// state of the object store
} HAL_RESET_INFO, * PHAL_RESET_INFO;

#define HAL_RESET_TYPE_UNKNOWN			0
#define HAL_RESET_REASON_HARDWARE		1
#define HAL_RESET_REASON_SOFTWARE		2
#define HAL_RESET_REASON_WATCHDOG		4
#define HAL_RESET_BATT_FAULT			8
#define HAL_RESET_VDD_FAULT				16

#define HAL_OBJECT_STORE_STATE_UNKNOWN	0
#define HAL_OBJECT_STORE_STATE_CLEAR	1

//----------------------------------------------------------------------------
// IOCTL_HAL_GET_OAL_VERINFO
typedef struct VersionInfo
{
	int				cboemverinfo;			// sizeof (tagOemVerInfo);
	unsigned short	verinfover;				// version number of version info structure
	char			sig[8];					//
	char			id;						// 'B' = boot loader, 'N' = CE image
	char			tgtcustomer[24];		// _TGTCUSTOMER -    customer name
	char			tgtplat[24];			// _TGTPLAT - 	     platform name
	char			tgtplatversion[13];		// _TGTPLATVERSION - platform version
	char			tgtcputype[8];			// _TGTCPUTYPE -     CPU type
	char			tgtcpu[12];				// _TGTCPU -         CPU name
	char			tgtcoreversion[8];		//
	char			date[12];				// __DATE__ -        build date
	char			time[12];				// __TIME__ -        build time

} VERSIONINFO, *PVERSIONINFO;

#endif //__OEMIOCTL_H__

