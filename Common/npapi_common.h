/**
*  \file npapi_common.h
*  \brief Common NPAPI definitions.
*  File to house the common definitions and types used by all NPAPI objects
*/

#pragma once

/**
*  Class to encapsulate a plugin for the Legacy NPAPI component.  Each JS object is
*  associated wtih a mime type and the data associated with the plugin is stored
*  in this structure
*/
class CPluginInfo
{
public:
	int iPluginType;	///<  The type of plugin contained in this class
	void* pPlugin;		///<  The data associated with the plugin (pointer to Scriptable Object child)
};

/**
*  Class to represent the scriptable objects exported from the NPAPI for JS Objects.  Each 
*  Scriptable object (e.g. timer) is stored as a void* in this structure.  All scriptable
*  objects are associated with a single Mime type and are stored here.
*/
class CJSObjectPluginInfo
{
public:
	void* pTimerPlugin;
	//  TODO : ADD OTHER OBJECTS HERE.  ALTHOUGH THIS IS JUST A SINGLE VOID* POINTER AT
	//  THE MOMENT IT WOULD MAKE FAR MORE SENSE TO HAVE A LINKED LIST OF CJSOBJECTPLUGININFO 
	//  SO WE AREN'T RESTRICTED BY LENGTH... ESPECIALLY IF WE'RE GOING TO AUTO GENERATE THIS.

};

