// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400

#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <tchar.h>
#include "core/JCThread.h"
#include "core/TString.h"

// Includes for plugins
#include <Pdh.h>
#include <Tlhelp32.h>
#include <Iphlpapi.h>
#ifdef _DEBUG
#undef _DEBUG
#define _NDEBUG
#include <Python.h>
#undef _NDEBUG
#define _DEBUG
#else
#include <Python.h>
#endif
 