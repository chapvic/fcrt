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

#ifdef __GNUC__
int __cdecl fprintf_s(FILE *_File, const char *_Format,...);
#endif

#if defined(WIN64) || defined(_WIN64) || defined(__x86_64__)
	const char * hexmask = "%08I64X: ";
#else
	const char * hexmask = "%08X: ";
#endif // defined(WIN64) || defined(_WIN64) || defined(__x86_64__)

static void _dump_memory_block(FILE* handle, void * ptr, size_t len, int padding) {
	int pad;
	size_t l;
	unsigned char *p, *pp, c;
	const char * padstr = "   ";

	p = ptr;
	while (len) {
		fprintf_s(handle, hexmask, p);
		pp = p;
		l = len;
		pad = padding;
		do fprintf_s(handle, " %02X", *(unsigned char *)p++);
			while (--pad && --len);
		if (pad)
			while(pad--) fprintf_s(handle, padstr);
		fprintf_s(handle, padstr);
		p = pp;
		len = l;
		pad = padding;
		do {
			c = *(unsigned char *)p++;
			fprintf_s(handle, "%c", c < 32 ? '.' : c);
			--len;
		}
		while(--pad && len);
		fprintf_s(handle, "\n");
	}
}

void __cdecl f_vardump(void * ptr, size_t len, int padding) {
	if(!ptr || !len) return;
	_dump_memory_block(stdout, ptr, len, padding);
}

void __cdecl f_vardump_ex(void * ptr, int padding) {
	size_t msize = f_memsize(ptr);
	if(msize < 0) return;
	_dump_memory_block(stdout, ptr, msize, padding);
}

void __cdecl f_fvardump(const char * filename, void * ptr, size_t len, int padding, int force) {
	FILE* handle;
	if(!ptr || !len) return;
	if(!filename) {
		if(freopen_s(&handle, "CONOUT$", "w", stdout)) return;
	} else {
		if (force) handle = fopen(filename, "a+");
		else {
			if(fopen_s(&handle, filename, "a+")) return;
		}
	}
	if(handle == ((void *)-1)) return;                  // INVALID_HANDLE_VALUE
	_dump_memory_block(handle, ptr, len, padding);
	fflush(handle);
	if (filename) fclose(handle);
}

void __cdecl f_fvardump_ex(const char * filename, void * ptr, int padding, int force) {
	size_t msize = f_memsize(ptr);
	if (msize < 0) return;
	f_fvardump(filename, ptr, msize, padding, force);
}
