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

#if defined(USE_CRT_ALLOC)
#define __fcrt_malloc(s) malloc(s)
#define __fcrt_msize(p) _msize(p)
#define __fcrt_free free
#else // !defined(USE_CRT_ALLOC)
#define __fcrt_malloc(s) HeapAlloc(GetProcessHeap(),0,(s))
#define __fcrt_msize(p) HeapSize(GetProcessHeap(),0,(p))
#define __fcrt_free(p) HeapFree(GetProcessHeap(),0,(p))
#endif // defined(USE_CRT_ALLOC)

_fcrt_noinline
void * __cdecl f_realloc(void * _ptr, size_t _newsize) {
	size_t size, zoffset;
	void * retval = nullptr;
	if (!_newsize) {
		if (_ptr) __fcrt_free(_ptr);
	} else {
		retval = __fcrt_malloc(_newsize);
		if (retval) {
			// memory block offset for zeros
			zoffset = 0;
			if (_ptr) {
				// check sizes of two blocks
				size = __fcrt_msize(_ptr);
				if (_newsize < size) size = _newsize;
				// copy first 'size' data from '_ptr' into the new allocated block
				memcpy(retval, _ptr, size);
				zoffset += size;
				__fcrt_free(_ptr);
			}
			// clear last bytes of memory block
			memset((char *)retval + zoffset, 0, _newsize - zoffset);
		} else {
			retval = _ptr;
		}
	}
	return retval;
}

_fcrt_noinline
void * __cdecl f_wrealloc(void * _ptr, size_t _newsize) {
	return f_realloc(_ptr, _newsize * sizeof(wchar_t));
}

_fcrt_noinline
size_t __cdecl f_memsize(void * _ptr) {
	return (_ptr) ? __fcrt_msize(_ptr) : (size_t)-1;
}

_fcrt_noinline
void __cdecl f_free(void * _ptr) {
	if (_ptr) __fcrt_free(_ptr);
}

_fcrt_noinline
void __cdecl f_freez(void ** _ptr) {
	if (_ptr && *_ptr) {
		__fcrt_free(*_ptr);
		*_ptr = nullptr;
	}
}

_fcrt_noinline
void * __cdecl f_malloc(size_t _size) {
	return f_realloc(nullptr, _size);
}

_fcrt_noinline
void * __cdecl f_wmalloc(size_t _size) {
	return f_realloc(nullptr, _size * sizeof(wchar_t));
}

_fcrt_noinline
void * __cdecl f_calloc(size_t _number, size_t _size) {
	return f_realloc(nullptr, _number * _size);
}

_fcrt_noinline
void * __cdecl f_recalloc(void * _ptr, size_t _number, size_t _size) {
	return f_realloc(_ptr, _number * _size);
}

#undef __fcrt_malloc
#undef __fcrt_msize
#undef __fcrt_free
