#include "MyDevinfoPlugin.h"

#include "npfunctions.h"

#include <stdio.h>
#include <windows.h>

#include "getRSSI.h"
#include "battery.h"
#include "devinfo.h"

//  These are the method / property names our plugin object will export
static NPIdentifier sMonitor_id;


static NPIdentifier sPollInterval_id;
static NPIdentifier sCurrentValue_id;
//static NPIdentifier sSensorType_id;

static NPIdentifier sCurrentRSSIValue_id;
static NPIdentifier sCurrentBattery_id;
static NPIdentifier sModelCode_id;

static NPObject * AllocateMyDevinfoPluginObject(NPP npp, NPClass *aClass)
{
	//  Called in response to NPN_CreateObject
	MyDevinfoPluginObject* obj = new MyDevinfoPluginObject(npp);
	//  Setting the default properties of the created object.
	obj->m_iPollInterval = 3000;
	obj->m_iCurrentValue = 0;

	obj->m_iCurrentRSSIValue=0;

	obj->m_hStopSensorMonitor = CreateEvent(NULL, FALSE, FALSE, NULL);
//	obj->m_iSensorType = -1;

	//  Create a Hidden Window so our sensor thread can re-synchronize back
	//  to the main thread
	obj->hWindow = CreateWindow(L"DevinfoWindow", NULL, 0, 0, 0, 0, 0, NULL, (HMENU) 0, NULL, NULL);
	if (obj->hWindow == NULL)
	{
		WNDCLASS wndclass;
		memset (&wndclass, 0, sizeof wndclass);
		wndclass.lpfnWndProc = obj->NpapiProc;
		wndclass.hInstance = NULL;
		wndclass.lpszClassName = L"DevinfoWindow";
		RegisterClass (&wndclass);
		obj->hWindow = CreateWindow(L"DevinfoWindow", NULL, 0, 0, 0, 0, 0, NULL, (HMENU) 0, NULL, NULL);
	}
	SetWindowLong(obj->hWindow, GWL_WNDPROC, (DWORD)obj->NpapiProc);
	return obj;
}

//  NPAPI Macro
DECLARE_NPOBJECT_CLASS_WITH_BASE(MyDevinfoPluginObject,
                                 AllocateMyDevinfoPluginObject);

bool MyDevinfoPluginObject::Construct(const NPVariant *args, uint32_t argCount,
                                     NPVariant *result)
{
	
	//  Where the JS Object is created, called when we say:
	//  var myObj = new MyDevinfo();
	bool bRetVal = false;
	//  Create Object, expect no arguments
	if (argCount == 0)
	{
		NPObject* genericObj = NPN_CreateObject(mNpp, GET_NPOBJECT_CLASS(MyDevinfoPluginObject));
		if (!genericObj)
			return false;
		MyDevinfoPluginObject* obj = (MyDevinfoPluginObject*)genericObj;
		OBJECT_TO_NPVARIANT(genericObj, *result);
		//  We have a function in our plugin to output text to a text box
		MessageToUser("Creating Devinfo object");
		bRetVal = true;
	}
  return bRetVal;
}

//  Called when the JS Object is destroyed
MyDevinfoPluginObject::~MyDevinfoPluginObject()
{
	SetEvent(m_hStopSensorMonitor);
}


bool MyDevinfoPluginObject::HasMethod(NPIdentifier name)
{
	//  Called by the plugin framework to query whether an object
	//  has a specified method, we only have one method, 'monitor()'
	return (name == sMonitor_id);
}

bool MyDevinfoPluginObject::HasProperty(NPIdentifier name)
{
	//  Called by the plugin framework to query whether a JS object
	//  has a specified property, we have three properties.
	return (name == sPollInterval_id ||
			name == sCurrentValue_id ||
//			name == sSensorType_id ||
			name == sCurrentRSSIValue_id ||
			name == sCurrentBattery_id ||
			name == sModelCode_id
			);
}

bool MyDevinfoPluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
	//  Retrieve the value of a property.  *result is an out parameter
	//  into which we should store the value
	bool bReturnVal = false;
	VOID_TO_NPVARIANT(*result);

	if (name == sCurrentValue_id)
	{
		//  Called by: var sensorVal = mySensor.currentValue;
		//  Return the current value to the web page.
		//  First truncate current value
		DOUBLE_TO_NPVARIANT(((float)this->m_iCurrentValue) / 100.0, *result);
		bReturnVal = true;
	}
	else if (name == sCurrentRSSIValue_id)
	{
		//  Called by: var sensorVal = myDevinfo.currentRSSIValue;
		//  Return the current value to the web page.
		this->m_iCurrentRSSIValue=my_getRSSI();
		INT32_TO_NPVARIANT(this->m_iCurrentRSSIValue , *result);// (((float)this->m_iCurrentValue) / 100.0, *result);
		bReturnVal = true;
	}
	else if (name == sCurrentBattery_id)
	{
		//  Called by: var sensorVal = myDevinfo.currentBatteryLevel;
		//  Return the current value to the web page.
		this->m_iCurrentBatteryLevel=getBatteryPercent();
		INT32_TO_NPVARIANT( this->m_iCurrentBatteryLevel, *result);// (((float)this->m_iCurrentValue) / 100.0, *result);
		bReturnVal = true;
	}
	else if (name == sModelCode_id)
	{
		//  Called by: var sensorVal = myDevinfo.modelCode;
		//  Return the value to the web page.
		char* npOutString = (char *)NPN_MemAlloc(MAX_BUFF);
		sprintf(npOutString, "%s", getModelCode());
		//pMyDevinfoPlugin

		STRINGZ_TO_NPVARIANT( npOutString , *result);// (((float)this->m_iCurrentValue) / 100.0, *result);
		bReturnVal = true;
	}
	if (!bReturnVal)
		VOID_TO_NPVARIANT(*result);
	return bReturnVal;
}

bool MyDevinfoPluginObject::SetProperty(NPIdentifier name, const NPVariant *value)
{
	//  Sets the specified property to the specified value.
	bool bRetVal = false;
	//if (name == sSensorType_id)
	//{
	//	//  mySensor.myType = 'devinfo';
	//	char szSensor[1024];
	//	memset(szSensor, 0, 1024);
	//	sprintf(szSensor, NPVARIANT_TO_STRING(*value).UTF8Characters);
	//	if (strcmp(szSensor, "devinfo") == 0)
	//		this->m_iSensorType = 0;
	//	else if (strcmp(szSensor, "pressure") == 0)
	//		this->m_iSensorType = 1;		
	//	bRetVal = true;
	//}
	//else 
	if (name == sPollInterval_id)
	{
		//  mySensor.pollInterval = [value];
		this->m_iPollInterval = (int)NPVARIANT_TO_DOUBLE(*value);		

		//  NB:  If you want to return a string you need to allocate the memory for it
		//char* szReturnBuffer = (char*) NPN_MemAlloc(wcslen(value) + 1);
		//wcstombs(szReturnBuffer, tcUID, wcslen(value) + 1);
		//STRINGZ_TO_NPVARIANT(szReturnBuffer, *result);
		bRetVal = true;
	}
	return bRetVal;
}

char* MyDevinfoPluginObject::npStrDup(const char* sIn)
{
	char* sOut = (char*)NPN_MemAlloc(strlen(sIn) + 1);
	if (sOut)
		strcpy(sOut, sIn);

	return sOut;
}

bool MyDevinfoPluginObject::Invoke(NPIdentifier name, const NPVariant *args,
                               uint32_t argCount, NPVariant *result)
{
	//  Called when a method is called on an object
	bool bReturnVal = false;
	VOID_TO_NPVARIANT(*result);
	//  Convert to lower case to make our methods case insensitive
	char* szNameCmp = _strlwr(NPN_UTF8FromIdentifier(name));
	NPIdentifier methodName =  NPN_GetStringIdentifier(szNameCmp);
	NPN_MemFree(szNameCmp);
	//  mySensor.monitor(bool)
	if (methodName == sMonitor_id)
	{
		//  Expect one argument which is a boolean (start / stop)
		if (argCount == 1 && NPVARIANT_IS_BOOLEAN(args[0]))
		{
			if (NPVARIANT_TO_BOOLEAN(args[0]))
			{
				//  mySensor.monitor(true);
				//  Create a thread to monitor the sensor			
				CloseHandle(CreateThread(NULL, 0,
				(LPTHREAD_START_ROUTINE)SensorMonitorThread, this, 0, NULL));
			}
			else
			{
				//  mySensor.monitor(false);
				//  Stop monitoring the sensor
				SetEvent(m_hStopSensorMonitor);
			}
			//  Monitor has no return value
			VOID_TO_NPVARIANT(*result);
			bReturnVal = true;
		}
	}
	if (!bReturnVal)
		VOID_TO_NPVARIANT(*result);
	return bReturnVal;
}

//  This is where we simulate the Sensor by returning random values
//  based on the type of the sensor
DWORD MyDevinfoPluginObject::SensorMonitorThread(LPVOID lpParameter)
{
	MyDevinfoPluginObject* pSensor = (MyDevinfoPluginObject*)lpParameter;
	bool exitThread = false;
	DWORD dwEvent;
	HANDLE hWaitHandles[1];
	hWaitHandles[0] = pSensor->m_hStopSensorMonitor;
	DEBUGMSG(TRUE, (L"Sensor Monitor Thread Starting\n"));

	while (true)
	{
		//  Wait for an exit event (indicating stop the thread) or timeout
		//  Note if we change the timeout value we have to wait until the next cycle
		//  before the new timeout value is read... this is just an example.
		dwEvent = WaitForMultipleObjects(
			1,
			hWaitHandles,
			FALSE,
			pSensor->m_iPollInterval);
		switch (dwEvent)
		{
		case WAIT_OBJECT_0:
			{
				goto _exitThread;
			}
		case WAIT_TIMEOUT:
			{
				//  Create a fake sensor reading to send to the page
				//char szSensorReading[512];
				//if (pSensor->m_iSensorType == 0)
				//{
				//	float currentValue = (float)((rand() % 100 + 10000) / 100.0);
				//	//  truncate the output
				//	pSensor->m_iCurrentValue = (int)(currentValue * 100);
				//	sprintf(szSensorReading, "Sensor Reading: %.02f Kelvin", currentValue);
				//}
				//else
				//{
				//	float currentValue = (float)((rand() % 100 + 1000) / 100.0);
				//	//  truncate the output
				//	pSensor->m_iCurrentValue = (int)(currentValue * 100);
				//	sprintf(szSensorReading, "Sensor Reading: %.02f Pascals", currentValue);
				//}
				////  Contention here if timeout is too small but this is just a demo
				////  Resynchronise with the main thread.
				//PostMessage(pSensor->hWindow, WM_USER + 1, (WPARAM)pSensor, (LPARAM)szSensorReading);

				CombinedMessage stMessage;
				stMessage.iBatt=getBatteryPercent();
				stMessage.iRSSI=my_getRSSI();
				PostMessage(pSensor->hWindow, WM_USER + 2, (WPARAM)pSensor, (LPARAM)&stMessage);
			}
		}  //  End Switch
	}	//  End While !exitThread
_exitThread:
	DEBUGMSG(TRUE, (L"Sensor Monitor Thread Exiting\n"));
	return 0;
}

//  Message handler for our hidden window to resynchronize with the main thread (NPAPI is not 
//  threadsafe)
LRESULT CALLBACK MyDevinfoPluginObject::NpapiProc (HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_USER + 1)
	{
		MyDevinfoPluginObject* pSensor = (MyDevinfoPluginObject*)wparam;
		char* szMessage = (char*)lparam;
		//  Inform the user that the sensor has a new value
		pSensor->MessageToUser(szMessage);
		return 0;
	}
	if (message == WM_USER + 2)
	{
		MyDevinfoPluginObject* pSensor = (MyDevinfoPluginObject*)wparam;
		CombinedMessage* stMessage = (CombinedMessage*)lparam;
		//  Inform the user that the sensor has a new value
		pSensor->MessageToUser(stMessage);
		return 0;
	}
	return DefWindowProc (hwnd, message, wparam, lparam);
}


bool MyDevinfoPluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount,
													NPVariant *result)
{
	STRINGZ_TO_NPVARIANT(npStrDup("default method return val"), *result);
	return true;
}

//  Constructor for the Plugin, called when the embedded mime type is found on a web page (see npp_new).
//  <embed id="embed1" type="application/x-itc-devinfo" hidden=true> </embed> 
CMyDevinfoPlugin::CMyDevinfoPlugin(NPP pNPInstance) :
  m_pNPInstance(pNPInstance),
  m_pNPStream(NULL),
  m_bInitialized(FALSE),
  m_pScriptableObject(NULL)
{
	
  	// Must initialise this before getting NPNVPluginElementNPObject, as it'll
	// call back into our GetValue method and require a valid plugin.
	pNPInstance->pdata = this;

    // Say that we're a windowless plugin.
    NPN_SetValue(m_pNPInstance, NPPVpluginWindowBool, false);

	//  Instantiate the values of the methods / properties we possess
	sMonitor_id = NPN_GetStringIdentifier("monitor");
	sPollInterval_id = NPN_GetStringIdentifier("pollInterval");
	sCurrentValue_id = NPN_GetStringIdentifier("currentValue");
	
	sCurrentRSSIValue_id = NPN_GetStringIdentifier("currentRSSIValue");
	sCurrentBattery_id = NPN_GetStringIdentifier("currentBatteryLevel");
	sModelCode_id = NPN_GetStringIdentifier("modelCode");

//	sSensorType_id = NPN_GetStringIdentifier("myType");

	//  Export onto the webpage the JS object 'MyDevinfo'.  This enables us
	//  to say var myObj = new MyDevinfo();
	NPObject *sWindowObj;
	NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &sWindowObj);
	NPObject *mySensorObject =NPN_CreateObject(m_pNPInstance,GET_NPOBJECT_CLASS(MyDevinfoPluginObject));
	NPVariant v;
	OBJECT_TO_NPVARIANT(mySensorObject, v);
	NPIdentifier n = NPN_GetStringIdentifier("MyDevinfo");
	NPN_SetProperty(m_pNPInstance, sWindowObj, n, &v);
	NPN_ReleaseObject(mySensorObject);
	NPN_ReleaseObject(sWindowObj);

}

CMyDevinfoPlugin::~CMyDevinfoPlugin()
{

}

void MyDevinfoPluginObject::MessageToUser(CombinedMessage* combinedMessage)
{
	NPVariant functionval;
	NPVariant rval;
	NPObject *sWindowObj;
	NPN_GetValue(mNpp, NPNVWindowNPObject, &sWindowObj);
	//  Populate 'functionval' with the name of our function
	if(!NPN_GetProperty(mNpp, sWindowObj, NPN_GetStringIdentifier("onBattRssiUpdate"), &functionval))
		DEBUGMSG(1, (L"MessageToUser: getValues not found\n"));
	NPVariant arg[2];
	if (NPVARIANT_TO_OBJECT(functionval) == 0){
		DEBUGMSG(1, (L"MessageToUser: NPVARIANT_TO_OBJECT failed\n"));
		return;
	}
	//  Create the arguments to call 'addSensorOutput' with
	INT32_TO_NPVARIANT(combinedMessage->iBatt, arg[0]);
	INT32_TO_NPVARIANT(combinedMessage->iRSSI, arg[1]);

	//  Invoke the Javascript function on the page
	NPN_InvokeDefault(mNpp, NPVARIANT_TO_OBJECT(functionval), arg, 2, &rval);
	//  Clean up allocated memory
	NPN_ReleaseVariantValue(&functionval);
	NPN_ReleaseVariantValue(&rval);
	NPN_ReleaseObject(sWindowObj);
}

//  This code is called to update the box at the bottom of the page,
//  the Javascript function 'addSensorOutput' is invoked which interacts
//  with the DOM.
void MyDevinfoPluginObject::MessageToUser(char* szMessage)
{
	NPVariant functionval;
	NPVariant rval;
	NPObject *sWindowObj;
	NPN_GetValue(mNpp, NPNVWindowNPObject, &sWindowObj);
	//  Populate 'functionval' with the name of our function
	NPN_GetProperty(mNpp, sWindowObj, NPN_GetStringIdentifier("addSensorOutput"), &functionval);
	NPVariant arg;
	if (NPVARIANT_TO_OBJECT(functionval) == 0)
		return;
	//  Create the argument to call 'addSensorOutput' with
	char szSourceMessage[1024];
	//if (m_iSensorType == 0)
	//	sprintf(szSourceMessage, "Temperature: %s", szMessage);
	//else if (m_iSensorType == 1)
	//	sprintf(szSourceMessage, "Pressure: %s", szMessage);
	//else
		sprintf(szSourceMessage, "%s", szMessage);
	//  Add the string argument to our javascript function to an argument, 'arg'
	STRINGZ_TO_NPVARIANT(szSourceMessage, arg);
	//  Invoke the Javascript function on the page
	NPN_InvokeDefault(mNpp, NPVARIANT_TO_OBJECT(functionval), &arg, 1,
						&rval);
	//  Clean up allocated memory
	NPN_ReleaseVariantValue(&functionval);
	NPN_ReleaseVariantValue(&rval);
	NPN_ReleaseObject(sWindowObj);
}

NPBool CMyDevinfoPlugin::init(NPWindow* pNPWindow)
{
  if(pNPWindow == NULL)
    return FALSE;

  if (SetWindow(pNPWindow))
      m_bInitialized = TRUE;

  return m_bInitialized;
}

void CMyDevinfoPlugin::shut()
{
	m_bInitialized = FALSE;
}

NPBool CMyDevinfoPlugin::isInitialized()
{
  return m_bInitialized;
}

NPError CMyDevinfoPlugin::SetWindow(NPWindow* pNPWindow)
{
  if(pNPWindow == NULL)
    return FALSE;

  m_Window = pNPWindow;
  NPWindow* window = pNPWindow;
  return TRUE;
}


NPObject* CMyDevinfoPlugin::GetScriptableObject()
{
	return NULL;
}
