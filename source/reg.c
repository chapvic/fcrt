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

#include "../fcrt_source.h"

#ifdef _FCRT_UNICODE
#undef __fcrt_reg_open
#define __fcrt_reg_open RegOpenKeyExW
#undef __fcrt_reg_info
#define __fcrt_reg_info RegQueryInfoKeyW
#else
#undef __fcrt_reg_open
#define __fcrt_reg_open RegOpenKeyExA
#undef __fcrt_reg_info
#define __fcrt_reg_info RegQueryInfoKeyA
#endif // _FCRT_UNICODE

long __cdecl _tregopen(HKEY * _pkey, const _tchar * _name, unsigned _machine) {
	HKEY ureg;
	long status = -1;
	if (_pkey && _name) {
		if (_machine) {
			status = __fcrt_reg_open(HKEY_LOCAL_MACHINE, _name, 0, KEY_READ, _pkey);
		} else {
			status = RegOpenCurrentUser(KEY_READ, &ureg);
			if (status == ERROR_SUCCESS) {
				status = __fcrt_reg_open(ureg, _name, 0, KEY_READ, _pkey);
				RegCloseKey(ureg);
			}
		}
	}
	return status;
}

regkey_t * __cdecl _treginfo(const _tchar * _name, unsigned _machine) {
	static regkey_t retval;
	static _tchar cls[MAX_PATH + 1];
	HKEY key;
	DWORD sz = MAX_PATH;
	long status = _tregopen(&key, _name, _machine);
	if (status != ERROR_SUCCESS) return nullptr;
	_tmemset(cls, 0, MAX_PATH + 1);
	f_memset(&retval, 0, sizeof(regkey_t));
	status = __fcrt_reg_info(key, cls, &sz, NULL,
		&retval.SubKeys,              // number of subkeys 
		&retval.MaxSubKeySize,        // longest subkey size 
		&retval.MaxClassSize,         // longest class string 
		&retval.Values,               // number of values for this key 
		&retval.MaxValueSize,         // longest value name 
		&retval.MaxValueDataSize,     // longest value data 
		&retval.SecurityDescriptor,   // security descriptor 
		&retval.LastWriteTime);       // last write time
	RegCloseKey(key);
	//_tprintf(_T("Class: %s, size = %d\n"), cls, sz);
	return (status == ERROR_SUCCESS) ? &retval : nullptr;
}
