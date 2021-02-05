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

#define CRC32_TABLE_SIZE 256
#define CRC32_POLYNOMIAL 0xEDB88320UL

static unsigned long __crc32_table[CRC32_TABLE_SIZE];

static void __internal_crc32_fill_table() {
	unsigned long i, j, k;
	static int filled = 0;
	if (!filled) {
		for (i = 0; i < CRC32_TABLE_SIZE; i++) {
			k = i;
			for (j = 0; j < 8; j++)
				k = (k & 1) ? (k >> 1) ^ CRC32_POLYNOMIAL : k >> 1;
			__crc32_table[i] = k;
		}
		filled = 1;
	}
}

unsigned long f_crc32(unsigned long crc, unsigned char *buffer, size_t len) {
	__internal_crc32_fill_table();
	crc = ~crc;
	while (len--) crc = (crc >> 8) ^ __crc32_table[(crc & 0xff) ^ (*buffer++)];
	return ~crc;
}
