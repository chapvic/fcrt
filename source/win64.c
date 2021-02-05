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

typedef BOOL(WINAPI *fn_IsWow64Process)(HANDLE, PBOOL);

_fcrt_noinline
int __cdecl f_is_app64() {
	return (int)(sizeof(void *) == 8);
}

_fcrt_noinline
int __cdecl f_is_wow64() {
#if !defined(_WIN64) && !defined(WIN64) && !defined(__x86_64__)
	int retval = 0;
	fn_IsWow64Process isWow64Process;
	HMODULE hModule = GetModuleHandle(_T("kernel32.dll"));
	if (hModule) {
		isWow64Process = (fn_IsWow64Process)GetProcAddress(hModule, "IsWow64Process");
		if (isWow64Process && isWow64Process(GetCurrentProcess(), &retval)) return retval;
	}
#endif // !defined(_WIN64) && !defined(WIN64) && !defined(__x86_64__)
	return 0;
}

_fcrt_noinline
int __cdecl f_is_win64() {
#if !defined(_WIN64) && !defined(WIN64) && !defined(__x86_64__)
	return f_is_wow64() || f_is_app64();
#else
	return 1;
#endif // !defined(_WIN64) && !defined(WIN64) && !defined(__x86_64__)
}
