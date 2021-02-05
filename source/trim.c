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

_tchar * __cdecl _tltrim(_tchar * _str) {
	size_t size = 0;
	_tchar *p, *retval = nullptr;
	if (_str && _tstrlen(_str)) {
		p = _str;
		while (*p == _T(' ')) ++p;
		size = _tstrlen(p) + sizeof(_tchar);
		retval = _tmalloc(size);
		if (retval) _tmemcpy(retval, p, size);
	}
	return retval;
}

_tchar * __cdecl _trtrim(_tchar * _str) {
	_tchar *p, *retval = nullptr;
	size_t size = _tstrlen(_str);
	if (_str && size) {
		p = _tstrchr(_str, 0);
		while ((p > _str) && (*(_tchar *)--p == _T(' '))) { --size; }
		retval = _tmalloc(size + sizeof(_tchar));
		if (retval) _tmemcpy(retval, _str, size);
	}
	return retval;
}

_fcrt_noinline
_tchar * __cdecl _ttrim(_tchar * _str) {
	_tchar *retval = nullptr, *s = _tltrim(_str);
	retval = _trtrim(s);
	f_free(s);
	return retval;
}
