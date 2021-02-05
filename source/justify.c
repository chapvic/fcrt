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

_tchar * __cdecl _tjleft(_tchar * _str, size_t _newsize) {
	size_t size;
	_tchar *p = nullptr, *retval = nullptr;
	if (_str) {
		size = _tstrlen(_str);
		if (_newsize < size) _newsize = size;
		p = _ttrim(_str);
		retval = _tdup(_T(' '), _newsize);
		if (p && retval) {
			size = _tstrlen(p);
			_tmemcpy(retval, p, size);
		}
	}
	f_free(p);
	return retval;
}

_tchar * __cdecl _tjright(_tchar * _str, size_t _newsize) {
	size_t size;
	_tchar *p = nullptr, *retval = nullptr;
	if (_str) {
		size = _tstrlen(_str);
		if (_newsize < size) _newsize = size;
		p = _ttrim(_str);
		retval = _tdup(_T(' '), _newsize);
		if (p && retval) {
			size = _tstrlen(p);
			_tmemcpy(retval + _newsize - size, p, size);
		}
	}
	f_free(p);
	return retval;
}

_fcrt_noinline
_tchar * __cdecl _tjcenter(_tchar * _str, size_t _newsize) {
	size_t size;
	_tchar *p = nullptr, *retval = nullptr;
	if (_str) {
		size = _tstrlen(_str);
		if (_newsize < size) _newsize = size;
		p = _ttrim(_str);
		retval = _tdup(_T(' '), _newsize);
		if (p && retval) {
			size = _tstrlen(p);
			_tmemcpy(retval + (_newsize - size) / 2, p, size);
		}
	}
	f_free(p);
	return retval;
}
