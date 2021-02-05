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

const char _b64_chars_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char _b64_index_table[] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

static int __cdecl __b64dec(char * _dst, char * _src, size_t _maxlen) {
	char chr[3], enc[4];
	int i = 0, retval = 0;
	size_t outpos = 0 , len = f_strlen(_src);
	if (!_maxlen || !len) goto Exit;
	for (i = 0; i < len; i += 4) {
		if (outpos + 3 >= _maxlen) goto Exit;
		enc[0] = _b64_index_table[_src[i]];
		enc[1] = _b64_index_table[_src[i + 1]];
		enc[2] = _b64_index_table[_src[i + 2]];
		enc[3] = _b64_index_table[_src[i + 3]];
		if (enc[0] == -1 || enc[1] == -1) goto Exit;
		chr[0] = (enc[0] << 2) | (enc[1] >> 4);
		chr[1] = ((enc[1] & 15) << 4) | (enc[2] >> 2);
		chr[2] = ((enc[2] & 3) << 6) | enc[3];
		_dst[outpos++] = chr[0];
		if (enc[2] != -1) _dst[outpos++] = chr[1];
		if (enc[3] != -1) _dst[outpos++] = chr[2];
	}
	_dst[outpos] = 0;
	retval = 1;
Exit:
	return retval;
}

static int __cdecl __b64enc_w(char * _dst, wchar_t * _src, size_t _maxlen) {
	char chr[3], enc[4];
	size_t i, len, outpos = 0;
	int retval = 0;
	len = f_wcslen(_src);
	if (!_maxlen || !len) goto Exit;
	for (i = 0; i < len; i += 3) {
		if (outpos + 4 >= _maxlen) goto Exit;
		chr[0] = (char)_src[i];
		chr[1] = (char)_src[i + 1];
		chr[2] = (char)_src[i + 2];
		enc[0] = chr[0] >> 2;
		enc[1] = ((chr[0] & 0x03) << 4) | (chr[1] >> 4);
		enc[2] = ((chr[1] & 0x0F) << 2) | (chr[2] >> 6);
		enc[3] = chr[2] & 0x3F;
		_dst[outpos++] = _b64_chars_table[enc[0]];
		_dst[outpos++] = _b64_chars_table[enc[1]];
		if (i + 1 >= len)
		{
			_dst[outpos++] = '=';
			_dst[outpos++] = '=';
		}
		else if (i + 2 >= len)
		{
			_dst[outpos++] = _b64_chars_table[enc[2]];
			_dst[outpos++] = '=';
		}
		else
		{
			_dst[outpos++] = _b64_chars_table[enc[2]];
			_dst[outpos++] = _b64_chars_table[enc[3]];
		}
	}
	_dst[outpos] = 0;
	retval = 1;
Exit:
	return retval;
}


int __cdecl f_b64enc(char * _dst, char * _src, size_t _maxlen) {
	int retval = 0;
	size_t len = f_strlen(_src);
	if (!_maxlen || !len) goto Exit;
	wchar_t * t = f_str2wcs(_src);
	if (!t) goto Exit;
	retval = __b64enc_w(_dst, t, _maxlen);
	f_free(t);
Exit:
	return retval;
}

int __cdecl f_b64encw(wchar_t * _dst, wchar_t * _src, size_t _maxlen) {
	int retval = 0;
	size_t len = f_wcslen(_src);
	if (!_maxlen || !len) goto Exit;
	char * t = (char *)f_malloc(_maxlen + 1);
	if (!t) goto Exit;
	retval = __b64enc_w(t, _src, _maxlen);
	if (retval) f_cstr2wcs(_dst, t, _maxlen);
	f_free(t);
Exit:
	return retval;
}

int __cdecl f_b64encaw(wchar_t * _dst, char * _src, size_t _maxlen) {
	int retval = 0;
	int len = (int)f_strlen(_src);
	if (!_maxlen || !len) goto Exit;
	wchar_t * t = f_str2wcs(_src);
	if (!t) goto Exit;
	char * o = (char *)f_malloc(_maxlen + 1);
	if (!o) goto Cleanup;
	retval = __b64enc_w(o, t, _maxlen);
	if (retval) f_cstr2wcs(_dst, o, _maxlen + 1);
Cleanup:
	f_free(o);
	f_free(t);
Exit:
	return retval;
}

int __cdecl f_b64encwa(char * _dst, wchar_t * _src, size_t _maxlen) {
	return __b64enc_w(_dst, _src, _maxlen);
}

int __cdecl f_b64dec(char * _dst, char * _src, size_t _maxlen) {
	return __b64dec(_dst, _src, _maxlen);
}

int __cdecl f_b64decw(wchar_t * _dst, wchar_t * _src, size_t _maxlen) {
	int retval = 0;
	size_t len = f_wcslen(_src);
	if (!_maxlen || !len) goto Exit;
	char * t = (char *)f_malloc(len + 1);
	char * o = (char *)f_malloc(_maxlen + 1);
	if (!t || !o) goto Cleanup;
	f_cwcs2str(t, _src, len + 1);
	retval = __b64dec(o, t, _maxlen);
	if (retval) f_cstr2wcs(_dst, o, _maxlen);
Cleanup:
	f_free(o);
	f_free(t);
Exit:
	return retval;
}

int __cdecl f_b64decaw(wchar_t * _dst, char * _src, size_t _maxlen) {
	int retval = 0;
	size_t len = f_strlen(_src);
	if (!_maxlen || !len) goto Exit;
	char * o = (char *)f_malloc(_maxlen + 1);
	if (!o) goto Exit;
	retval = __b64dec(o, _src, _maxlen);
	if (retval) f_cstr2wcs(_dst, o, _maxlen + 1);
	f_free(o);
Exit:
	return retval;
}

int __cdecl f_b64decwa(char * _dst, wchar_t * _src, size_t _maxlen) {
	int retval = 0;
	size_t len = f_wcslen(_src);
	if (!_maxlen || !len) goto Exit;
	char *t = f_wcs2str(_src);
	if (!t) goto Exit;
	retval = __b64dec(_dst, t, _maxlen);
	f_free(t);
Exit:
	return retval;
}
