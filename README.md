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

