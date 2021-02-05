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

char * __cdecl f_bin2hex(void *_ptr, size_t _size, int _ucase, int _sparse) {
	size_t i;
	int shift;
	unsigned char l, h;
	char *buff, *retval = nullptr;
	if (_ptr && _size) {
		buff = _ptr;
		shift = _sparse ? 3 : 2;
		retval = f_malloc(_size * shift + (_sparse ? 0 : 1));
		if (retval) {
			if (_sparse) memset(retval, 32, _size * shift - 1);
			for (i = 0; i < _size; i++) {
				l = buff[i] & 0x0F;
				h = (buff[i] >> 4) & 0x0F;
				retval[i * shift] = h + (h < 10 ? 48 : (_ucase ? 55 : 87));
				retval[i * shift + 1] = l + (l < 10 ? 48 : (_ucase ? 55 : 87));
			}
		}
	}
	return retval;
}
