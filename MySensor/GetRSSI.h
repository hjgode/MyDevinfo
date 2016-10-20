#include <windows.h>

#include "WifiPeek.h"

#ifndef _GETRSSI_H_
#define _GETRSSI_H_

#pragma once

#define UNKNOWERROR -250
#define LOADLIBFAILED -251
#define CONNECTFAILED -252
#define QUERYFAILED -253
#define SCANNING -254
#define NOTASSOCIATED -255

int my_getRSSI();

#endif //_GETRSSI_H_