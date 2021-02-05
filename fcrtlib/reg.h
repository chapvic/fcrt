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

#ifndef _FCRT_H
#error You must include 'fcrt.h' only!
#endif // !FCRT_H

#ifndef _FCRT_REG_H
#define _FCRT_REG_H

#pragma pack(push, _CRT_PACKING)

typedef struct {
	DWORD SubKeys;              // number of subkeys 
	DWORD MaxSubKeySize;        // longest subkey size 
	DWORD MaxClassSize;         // longest class string 
	DWORD Values;               // number of values for this key 
	DWORD MaxValueSize;         // longest value name 
	DWORD MaxValueDataSize;     // longest value data 
	DWORD SecurityDescriptor;   // security descriptor 
	FILETIME LastWriteTime;     // last write time
} regkey_t;

#pragma pack(pop)

// ---------------------------------------------------------------------------
// reg.c
// ---------------------------------------------------------------------------
FCRT long __cdecl f_regopen(HKEY * _pkey, const char * _name, unsigned _machine);
FCRT long __cdecl f_regwopen(HKEY * _pkey, const wchar_t * _name, unsigned _machine);
FCRT regkey_t * __cdecl f_reginfo(const char * _name, unsigned _machine);
FCRT regkey_t * __cdecl f_regwinfo(const wchar_t * _name, unsigned _machine);

#ifndef _FCRT_NO_ALIAS
#define regopen f_regopen
#define wregopen f_wregopen
#define reginfo f_reginfo
#define wreginfo f_wreginfo
#endif // !_FCRT_NO_ALIAS

#endif // !_FCRT_REG_H
