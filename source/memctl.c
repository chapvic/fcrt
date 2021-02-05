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

_fcrt_noinline
int __cdecl f_memcmp(const void * _ptr1, const void * _ptr2, size_t _count) {
	return (_ptr1 && _ptr2 && _count) ? memcmp(_ptr1, _ptr2, _count) : 0;
}

_fcrt_noinline
int __cdecl f_wmemcmp(const wchar_t * _ptr1, const wchar_t * _ptr2, size_t _count) {
	return (_ptr1 && _ptr2 && _count) ? wmemcmp(_ptr1, _ptr2, _count) : 0;
}

_fcrt_noinline
void * __cdecl f_memcpy(void * _dst, const void * _src, size_t _count) {
	return (_dst && _src && _count) ? memcpy(_dst, _src, _count) : nullptr;
}

_fcrt_noinline
void * __cdecl f_wmemcpy(void * _dst, const void * _src, size_t _count) {
	return (_dst && _src && _count) ? wmemcpy(_dst, _src, _count) : nullptr;
}

_fcrt_noinline
void * __cdecl f_memset(void * _dst, int _c, size_t _count) {
	return (_dst && _count) ? memset(_dst, _c, _count) : nullptr;
}

_fcrt_noinline
void * __cdecl f_wmemset(wchar_t * _dst, wchar_t _c, size_t _count) {
	return (_dst && _count) ? wmemset(_dst, _c, _count) : nullptr;
}
