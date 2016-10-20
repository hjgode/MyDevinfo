#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "npapi.h"
#include "npruntime.h"
#include "nullplugin.h"
#include "ScriptablePluginObjectBase.h"

struct CombinedMessage{
	int iRSSI;
	int iBatt;
};

class CMyDevinfoPlugin
{
private:
	NPP m_pNPInstance;

	NPWindow * m_Window;
	NPStream * m_pNPStream;
	NPBool m_bInitialized;
	NPObject *m_pScriptableObject;
	PluginInstance nullPluginInstance;

public:
	CMyDevinfoPlugin(NPP pNPInstance);
	~CMyDevinfoPlugin();

	NPBool init(NPWindow* pNPWindow);
	void shut();
	NPBool isInitialized();

	NPError SetWindow(NPWindow* pNPWindow);

	NPObject *GetScriptableObject();
};

class MyDevinfoPluginObject : public ScriptablePluginObjectBase
{
public:
	MyDevinfoPluginObject(NPP npp) : ScriptablePluginObjectBase(npp)  { }

	virtual ~MyDevinfoPluginObject();

	virtual bool Construct(const NPVariant *args, uint32_t argCount,
		NPVariant *result);
	char* npStrDup(const char* sIn);
	virtual bool HasMethod(NPIdentifier name);
	virtual bool HasProperty(NPIdentifier name);
	virtual bool GetProperty(NPIdentifier name, NPVariant *result);
	virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
	virtual bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);
	void MessageToUser(char* szMessage);
	
	void MessageToUser(CombinedMessage* combinedMessage);

	static DWORD SensorMonitorThread(LPVOID lpParameter);
	static LRESULT CALLBACK NpapiProc (HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
//	int m_iSensorType;
	int m_iPollInterval;
	int m_iCurrentValue;

	int m_iCurrentRSSIValue;
	int m_iCurrentBatteryLevel;

	HANDLE m_hStopSensorMonitor;
	HWND hWindow;

};


#endif // __PLUGIN_H__
