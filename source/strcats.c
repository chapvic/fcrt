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

_tchar * __cdecl _tstrcats(_tchar * _buffer, _tchar * _src, _tchar * _separator) {
	size_t src_len, sep_len;
	if (_buffer) {
		src_len = _tstrlen(_src);
		sep_len = _tstrlen(_separator);
		if (sep_len) _tstrncat(_buffer, _separator, sep_len);
		if (src_len) _tstrncat(_buffer, _src, src_len);
	}
	return _buffer;
}

_tchar * __cdecl _tstrcats_n(_tchar * _str1, _tchar * _str2, _tchar * _separator) {
	_tchar * dst = nullptr;
	size_t str1_len = _tstrlen(_str1);
	size_t str2_len = _tstrlen(_str2);
	size_t sep_len = _tstrlen(_separator);
	dst = _tmalloc(str1_len + str2_len + sep_len + 1);
	if (dst) {
		if (str1_len) _tstrncpy(dst, _str1, str1_len);
		if (sep_len) _tstrncat(dst, _separator, sep_len);
		if (str2_len) _tstrncat(dst, _str2, str2_len);
	}
	return dst;
}
