/*
MIT License

Copyright (c) 2018-2021 FoxTeam

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#if !defined(WIN32) && !defined(_WIN32)
#error FCRT supports Win32 only!
#endif

#ifndef _FCRT_H
#define _FCRT_H
#endif

#if !defined(_FCRT_CONFIG) && !defined(_FCRT_UNICODE)
#ifdef UNICODE
#define _FCRT_UNICODE
#endif // UNICODE
#endif // !defined(_FCRT_CONFIG) && !defined(_FCRT_UNICODE)

// FCRT must not be defined!
#undef FCRT

#ifdef _MSC_VER
#define _fcrt_noinline __declspec(noinline)
#define _fcrt_export __declspec(dllexport)
#define _fcrt_import __declspec(dllimport)
#else // !_MSC_VER
#define _fcrt_noinline __attribute__((noinline))
#define _fcrt_export __attribute__((dllexport))
#define _fcrt_import __attribute__((dllimport))
#endif // _MSC_VER

#if defined(FCRT_EXPORT) || defined(FCRT_DLL)
#define FCRT _fcrt_export
#elif defined(FCRT_IMPORT)
#define FCRT _fcrt_import
#elif defined(FCRT_EXTERN)
#define FCRT extern
#else // !defined(FCRT_EXPORT) || defined(FCRT_DLL)
#define FCRT
#endif // defined(FCRT_EXPORT) || defined(FCRT_DLL)

#ifndef _FCRT_SOURCE
#ifdef FCRT_IMPORT
#pragma comment(lib, "fcrt")
#else // !FCRT_IMPORT
#pragma comment(lib, "fcrt_s")
#endif // FCRT_IMPORT
#endif // !_FCRT_SOURCE

#include "fcrtlib/std.h"
#include "fcrtlib/tchars.h"
#include "fcrtlib/endian.h"
#include "fcrtlib/crypto.h"
#include "fcrtlib/memlist.h"
#include "fcrtlib/reg.h"
#include "fcrtlib/vardump.h"

// -----------------------------------------------------------
#ifndef _MSC_VER
errno_t __cdecl freopen_s(FILE **, const char *, const char *, FILE *);
errno_t __cdecl fopen_s(FILE **, const char *, const char *);
#endif
// -----------------------------------------------------------

#ifndef __GNUC__
#pragma comment(lib, "user32")
#pragma comment(lib, "advapi32")
#endif // !__GNUC__
