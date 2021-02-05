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

// Check switch for wrapper definition 
#ifdef _FCRT_EXT_FUNC
// Declarations for 'striXX' version
#define _fcrt_function _tstri_replace
#define _fcrt_worker _tstristr
#else
// Declarations for 'strXX' version
#define _fcrt_function _tstr_replace
#define _fcrt_worker _tstrstr
#endif // _FCRT_EXT_FUNC

_tchar * __cdecl _fcrt_function(_tchar * _search, _tchar * _replace, _tchar * _str) {
	// declare vars
	size_t slen, rlen, len;
	int delta, found;
	_tchar *src, *dst, *p, *newstr;
	// check for invalid parameters
	if (!_search || !_replace || !_str) return nullptr;  // NULL pointers!
	slen = _tstrlen(_search);        // length of the required substring
	rlen = _tstrlen(_replace);       // length of the substring to replace
	len = _tstrlen(_str);            // length of the original string
	// calculate new length for replaced string
	found = 0;
	if ((len > 0) && (slen > 0) && (slen <= len)) {
		src = _str;
		while (*src > 0) {
			p = _fcrt_worker(src, _search);
			if (p) {
				src += (p - src) + slen;
				len = len - slen + rlen;
				++found;
			} else {
				++src;
			}
		}
	}
	// allocate memory
	newstr = _tmalloc(len + 1);
	if (!newstr) return nullptr;
	// if substring(s) found, do replace
	if (found) {
		src = _str;         // source string
		dst = newstr;       // destination
		while (*src > 0) {
			p = _fcrt_worker(src, _search);
			if (p) {
				delta = (int)(p - src);
				if (delta > 0) {
					// copy prev text
					_tstrncpy(dst, src, delta);
					dst += delta;
					src += delta;
				}
				// if replacement is not empty
				if (rlen) {
					_tstrncpy(dst, _replace, rlen);
					dst += rlen;
				}
				src += slen;
			} else {
				*dst++ = *src++;
			}
		}
	} else {
		// substring(s) is not found, copy source text
		_tstrncpy(newstr, _str, len);
	}
	return newstr;
}

#undef _fcrt_function
#undef _fcrt_worker
