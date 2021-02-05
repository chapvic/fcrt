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

_tchar * __cdecl _tsubstr(const _tchar * _str, int _origin, int _len) {
	const _tchar * p0, * p1, *p;
	_tchar * dst = nullptr;                          // default return value
	int len = 0;
	if (_str && *_str) {
		if (_origin || _len) {
			p0 = _str;                       // begin of string
			p1 = _tstrchr(_str, 0);          // end of string
			// calculating the position and length of a substring
			if (_origin < 0) p0 = (_tchar *)p1 + _origin;   // set 'p0' from the end of string
			else if (_origin > 0) p0 += _origin;            // set 'p0' from the begin of string
			if (_len < 0) {
				p1 += _len;                             // truncate the end of string, if _len < 0
			}
			else if (_len > 0) {
				p = (_len > 0) ? (_tchar *)p0 + _len : p1;
				if (p < p1) p1 = p;
			}
			// adjust pointers and get the length of the substring
			if (p0 < _str) p0 = _str;
			if (p1 < p0) p1 = p0;
			len = (int)(p1 - p0);
		}
		// substring cutting
		if (len >= 0) {
			dst = _tmalloc(len + 1);
			// don't copy if size is zero
			if (dst && (len > 0)) _tmemcpy(dst, p0, len);
		}
	}
	return dst;
}
