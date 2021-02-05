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

_tchar * __cdecl _tstristr(const _tchar * _str, const _tchar * _substr) {
	if (!_str || !_substr) return nullptr;
	size_t len1 = _tstrlen(_str);       // length of the string
	size_t len2 = _tstrlen(_substr);    // length of the substring
	if (!len1 || !len2 || (len2 > len1)) return nullptr;
	_tchar * p = 0;                     // pointer of the first found char
	_tchar * p1 = (_tchar *)_str;       // begin of the '_str'
	_tchar * p2 = (_tchar *)_substr;    // begin of then '_substr'
	size_t cnt = len2;                  // chars counter
	// Start search
	while (*p1 && cnt > 0) {
		if (lowercase(*p1) == lowercase(*p2)) {
			if (!p) p = (_tchar *)p1;
			++p2;
			--cnt;
		} else {
			p = 0;
			p2 = (_tchar *)_substr;
			cnt = len2;
		}
		p1++;
	};
	return (!cnt) ? p : nullptr;
}
