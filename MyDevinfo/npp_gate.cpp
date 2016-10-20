/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

////////////////////////////////////////////////////////////
//
// Implementation of plugin entry points (NPP_*)
// most are just empty stubs for this particular plugin 
//
#include "MyDevinfoPlugin.h"
#include "../Common/npapi_common.h"
#include <stddef.h>
#include <stdio.h>

#include <windows.h>

static CMyDevinfoPlugin* pMyDevinfoPlugin = NULL;

char* NPP_GetMIMEDescription(void)
{
  return "application/x-itc-devinfo";
}


NPError NPP_Initialize(void)
{
	DEBUGMSG(1, (L"NPP_Initialize...\n"));
  return NPERR_NO_ERROR;
}

void NPP_Shutdown(void)
{
	DEBUGMSG(1, (L"NPP_Shutdown...\n"));
}

//  Called when the web page encounters the embed tag:
//  <embed id="embed1" type="application/x-itc-devinfo" hidden=true> </embed> 
NPError NPP_New(NPMIMEType pluginType,
                NPP instance,
                uint16_t mode,
                int16_t argc,
                char* argn[],
                char* argv[],
                NPSavedData* saved)
{   
	DEBUGMSG(1, (L"NPP_New...\n"));
//	fprintf (stderr, "NPP New for %s\n", pluginType);
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;

  if (strcmp(pluginType, "application/x-itc-devinfo") == 0)
  {
	  CMyDevinfoPlugin * pMyDevinfoPlugin = new CMyDevinfoPlugin(instance);
	  if(pMyDevinfoPlugin == NULL)
		return NPERR_OUT_OF_MEMORY_ERROR;

	  CPluginInfo* pluginInfoObject = new CPluginInfo();
		pluginInfoObject->iPluginType = 0;
		pluginInfoObject->pPlugin = (void *)pMyDevinfoPlugin;
	  instance->pdata = (void *)pluginInfoObject;
  }
  return rv;
}

// here is the place to clean up and destroy the CGenericPlugin object
NPError NPP_Destroy (NPP instance, NPSavedData** save)
{
	DEBUGMSG(1, (L"NPP_Destroy...\n"));
//	fprintf (stderr, "NPP Destroy\n");
	if(instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	NPError rv = NPERR_NO_ERROR;

	CPluginInfo * pPluginInfo = (CPluginInfo *)instance->pdata;
	if(pPluginInfo != NULL) 
	{
		CMyDevinfoPlugin * pMyDevinfoPlugin = (CMyDevinfoPlugin *)pPluginInfo->pPlugin;
		pMyDevinfoPlugin->shut();
		delete pMyDevinfoPlugin;
		delete pPluginInfo;
	}		
	return rv;
}

// during this call we know when the plugin window is ready or
// is about to be destroyed so we can do some gui specific
// initialization and shutdown
NPError NPP_SetWindow (NPP instance, NPWindow* pNPWindow)
{
	if(instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	NPError rv = NPERR_NO_ERROR;

	if(pNPWindow == NULL)
		return NPERR_GENERIC_ERROR;

	CPluginInfo * pPluginInfo = (CPluginInfo *)instance->pdata;

	if(pPluginInfo == NULL) 
		return NPERR_GENERIC_ERROR;

	if (pPluginInfo && pPluginInfo->iPluginType == 0)
	{
		CMyDevinfoPlugin* pMyDevinfoPlugin = (CMyDevinfoPlugin*)pPluginInfo->pPlugin;
		// window just created
		if(!pMyDevinfoPlugin->isInitialized()) 
		{ 
			if(!pMyDevinfoPlugin->init(pNPWindow)) 
			{
				delete pMyDevinfoPlugin;
				pMyDevinfoPlugin = NULL;
				return NPERR_MODULE_LOAD_FAILED_ERROR;
			}
		}
		// window goes away
		if((pNPWindow->window == NULL) && pMyDevinfoPlugin->isInitialized())
			return pMyDevinfoPlugin->SetWindow(pNPWindow);

		// window resized?
		if(pMyDevinfoPlugin->isInitialized() && (pNPWindow->window != NULL))
			return pMyDevinfoPlugin->SetWindow(pNPWindow);

		// this should not happen, nothing to do
		if((pNPWindow->window == NULL) && !pMyDevinfoPlugin->isInitialized())
			return pMyDevinfoPlugin->SetWindow(pNPWindow);
	}

	return rv;
}

// ==============================
// ! Scriptability related code !
// ==============================
//
// here the plugin is asked by Mozilla to tell if it is scriptable
// we should return a valid interface id and a pointer to 
// nsScriptablePeer interface which we should have implemented
// and which should be defined in the corressponding *.xpt file
// in the bin/components folder
NPError	NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
	if(instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	NPError rv = NPERR_NO_ERROR;

	if(instance == NULL)
		return NPERR_GENERIC_ERROR;

	CPluginInfo * pluginInfo = (CPluginInfo *)instance->pdata;
	if(pluginInfo == NULL)
		return NPERR_GENERIC_ERROR;

	switch (variable) 
	{
	case NPPVpluginNameString:
		*((char **)value) = "My Plugin";
		break;
	case NPPVpluginDescriptionString:
		*((char **)value) = "Sample NPAPI Plugin";
		break;
	case NPPVpluginScriptableNPObject:
		if (pluginInfo->iPluginType == 0)
		{
			CMyDevinfoPlugin* pMyDevinfoPlugin = (CMyDevinfoPlugin*)pluginInfo->pPlugin;
			*(NPObject **)value = pMyDevinfoPlugin->GetScriptableObject();
		}
		break;
	default:
		rv = NPERR_GENERIC_ERROR;
	}

	return rv;
}

NPError NPP_NewStream(NPP instance,
                      NPMIMEType type,
                      NPStream* stream, 
                      NPBool seekable,
                      uint16_t* stype)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;
  return rv;
}

int32_t NPP_WriteReady (NPP instance, NPStream *stream)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  int32_t rv = 0x0fffffff;
  return rv;
}

int32_t NPP_Write (NPP instance, NPStream *stream, int32_t offset, int32_t len, void *buffer)
{   
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  int32_t rv = len;
  return rv;
}

NPError NPP_DestroyStream (NPP instance, NPStream *stream, NPError reason)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;
  return rv;
}

void NPP_StreamAsFile (NPP instance, NPStream* stream, const char* fname)
{
  if(instance == NULL)
    return;
}

void NPP_Print (NPP instance, NPPrint* printInfo)
{
  if(instance == NULL)
    return;
}

void NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
  if(instance == NULL)
    return;
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;
  return rv;
}

int16_t	NPP_HandleEvent(NPP instance, void* event)
{
	if(instance == NULL)
		return 0;

	int16_t rv = 0;
	return rv;
}

#ifdef OJI
jref NPP_GetJavaClass (void)
{
  return NULL;
}
#endif

NPObject *NPP_GetScriptableInstance(NPP instance)
{
	if(!instance)
		return 0;

	NPObject *npobj = 0;
	CPluginInfo * pPluginInfo = (CPluginInfo *)instance->pdata;
	if (!pPluginInfo)
	{
		if (pPluginInfo->iPluginType == 0)
		{
			CMyDevinfoPlugin* pMyDevinfoPlugin = (CMyDevinfoPlugin*)pPluginInfo->pPlugin;
			npobj = pMyDevinfoPlugin->GetScriptableObject();
		}
	}
	return npobj;
}
