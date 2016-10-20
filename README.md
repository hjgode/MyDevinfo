# MyDevinfo
Windows Mobile 6.x HTML5 NPAPI plugin

Visual Studio 2008
Windows Mobile 6 Prof. SDK

HTML5 Browser

This plugin offers a NPAPI object to retrieve the Model Code, RSSI, Battery Level of a supported device.

## HTML code

First create a new embedding

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
