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

char * __cdecl f_oem2str(const char * _str) {
	char * dst = nullptr;
	if (!_str) goto Exit;
	int size = (int)f_strlen(_str);
	if (!size) goto Exit;
	dst = f_malloc(size + 1);
	if (dst) OemToCharBuffA(_str, dst, size);
Exit:
	return dst;
}

wchar_t * __cdecl f_oem2wcs(const char * _str) {
	wchar_t * dst = nullptr;
	if (!_str) goto Exit;
	int size = MultiByteToWideChar(CP_OEMCP, 0, _str, -1, NULL, 0);
	if (!size) goto Exit;
	dst = f_wmalloc(size + 1);
	if (dst) MultiByteToWideChar(CP_OEMCP, 0, _str, -1, dst, size);
Exit:
	return dst;
}

char * __cdecl f_str2oem(const char * _str) {
	int size;
	char * dst = nullptr;
	if (_str) {
		size = (int)f_strlen(_str) + 1;
		if (size) {
			dst = f_malloc(size);
			if (dst) CharToOemBuffA(_str, dst, size);
		}
	}
	return dst;
}

size_t __cdecl f_cstr2wcs(wchar_t * dst, char * src, size_t len) {
	int size = 0;
	if (src && dst) {
		size = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
		if (size && ((int)len >= size))
			MultiByteToWideChar(CP_UTF8, 0, src, -1, dst, size);
	}
	return size;
}

wchar_t * __cdecl f_str2wcs(const char * _str) {
	int size;
	wchar_t * dst = nullptr;
	if (_str) {
		size = MultiByteToWideChar(CP_UTF8, 0, _str, -1, NULL, 0);
		if (size) {
			dst = f_wmalloc(size + 1);
			if (dst) MultiByteToWideChar(CP_UTF8, 0, _str, -1, dst, size);
		}
	}
	return dst;
}

char * __cdecl f_wcs2oem(const wchar_t * _str) {
	int size;
	char * dst = nullptr;
	if (_str) {
		size = WideCharToMultiByte(CP_OEMCP, 0, _str, -1, NULL, 0, NULL, NULL);
		if (size) {
			dst = f_malloc(size + 1);
			if (dst) WideCharToMultiByte(CP_OEMCP, 0, _str, -1, dst, size, NULL, NULL);
		}
	}
	return dst;
}

size_t __cdecl f_cwcs2str(char * _dst, wchar_t * _src, size_t _len) {
	int size = 0;
	if (_src && _dst) {
		size = WideCharToMultiByte(CP_UTF8, 0, _src, -1, NULL, 0, NULL, NULL);
		if (size && ((int)_len >= size))
			WideCharToMultiByte(CP_UTF8, 0, _src, -1, _dst, size, NULL, NULL);
	}
	return size;
}

char * __cdecl f_wcs2str(const wchar_t * _str) {
	int size;
	char * dst = nullptr;
	if (_str) {
		size = WideCharToMultiByte(CP_UTF8, 0, _str, -1, NULL, 0, NULL, NULL);
		if (size) {
			dst = f_malloc(size + 1);
			if (dst) WideCharToMultiByte(CP_UTF8, 0, _str, -1, dst, size, NULL, NULL);
		}
	}
	return dst;
}
