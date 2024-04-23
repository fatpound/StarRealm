#pragma once

// target Windows 7 or later
#define _WIN32_WINNT 0x0601

#include <sdkddkver.h>

#ifndef FATPOUND_FULL_WIN_TARGETED
#define WIN32_LEAN_AND_MEAN // rarely used things
#define NOGDICAPMASKS
// #define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
// #define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#endif


#define NOMINMAX
#define STRICT

#define _CRTDBG_MAP_ALLOC

#include <Windows.h>


#ifndef NDEBUG
#define IS_DEBUG true
#else
#define IS_DEBUG false
#endif // NDEBUG