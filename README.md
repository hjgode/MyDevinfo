# MyDevinfo
Windows Mobile 6.x HTML5 NPAPI plugin

Visual Studio 2008
Windows Mobile 6 Prof. SDK

![screen shot](https://github.com/hjgode/MyDevinfo/raw/master/NPAPI_simple2.png)

HTML5 Browser

This plugin offers a NPAPI object to retrieve the Model Code, RSSI, Battery Level of a supported device.

## Installation

Copy the plugin DLL to the plugins directory of the browser. For example "\Program Files\HTML5 Browser\plugins" or "\Program Files\Enterprise Browser\plugins". No further installation needed. Just use the embedd tag and the DevInfo object as described below.

## HTML code

Note that the plugin may not work if the html is not loaded from a web server.

First create a new embedding.

    </HEAD>
    <embed id="embed1" type="application/x-itc-devinfo" hidden=true> </embed>
    <BODY>

Then create a new object 

    <script> 
    var devinfoObj = null;
    if (devinfoObj == null) {
      devinfoObj = new MyDevinfo();
    }
    else {
      alert('devinfo object already created');
    }
    ...

### Get Model Code

The following returns a string with the mode code:

    devinfoObj.modelCode;
    
### Get Battery level

The following script code returns the battery life percent

    devinfoObj.currentBatteryLevel
    
### Get WLAN receive signal strength

The RSSI in dBm is returned by the following property

    devinfoObj.currentRSSIValue
    
### get Local IP address

The first local IP address returned by following property

	devinfoObj.localIP
	
### Periodic update callback

Setting an interval and enabling the monitor will call the javascript function periodically
    
    devinfoObj.pollInterval=1000

the pollInterval has to be set in milliseconds.

    devinfoObj.monitor(boolean);
    
use true to enabling periodic callbacks and false to disable the callback.

The callback function has to be named `onBattRssiUpdate` and uses two arguments:
    
    function onBattRssiUpdate(batt, rssi){
       //do something with the supplied values
    }

## Remark

Normally place the embed object inside the `<body>` tag.

If the object will not inialize correctly during HTML loading, you may use a delayed initialisation to autload the object. For example:

    <HEAD>
    ...
    <script>
    var devinfoObj = null;
    function olinit() {
        if (devinfoObj == null) {
            devinfoObj = new MyDevinfo();
            if (devinfoObj == null) {
                alert('devinfo object NOT created');
            }
        }
        else {
            alert('devinfo object already created');
        }
    }
    
    </script> 
    <embed id="embed1" type="application/x-itc-devinfo" hidden=true> </embed> 
    
    </HEAD>
    <!-- creating the object automatically must be delayed -->
    <BODY onload="setTimeout('olinit()', 1000);">
    ...
