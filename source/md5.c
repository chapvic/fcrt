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

//MD5 auxiliary functions
#define F(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))

#define FF(a, b, c, d, x, s, k) a += F(b, c, d) + (x) + (k), a = ROL32(a, s) + (b)
#define GG(a, b, c, d, x, s, k) a += G(b, c, d) + (x) + (k), a = ROL32(a, s) + (b)
#define HH(a, b, c, d, x, s, k) a += H(b, c, d) + (x) + (k), a = ROL32(a, s) + (b)
#define II(a, b, c, d, x, s, k) a += I(b, c, d) + (x) + (k), a = ROL32(a, s) + (b)

//MD5 padding
static const BYTE md5_padding[64] = {
   0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//MD5 constants
static const DWORD md5_k[64] = {
   0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501,
   0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821,
   0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
   0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A,
   0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70,
   0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665,
   0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
   0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391
};

/**
 * @brief Process message in 16-word blocks
 * @param[in] context Pointer to the MD5 context
 **/

void __md5_transform(PHASH_CONTEXT context) {
    //Initialize the 4 working registers
    DWORD a = context->h32[0];
    DWORD b = context->h32[1];
    DWORD c = context->h32[2];
    DWORD d = context->h32[3];

    //Process message in 16-word blocks
    DWORD* x = context->w32;

    //Convert from little-endian byte order to host byte order
    x[0] = letoh32(x[0]);
    x[1] = letoh32(x[1]);
    x[2] = letoh32(x[2]);
    x[3] = letoh32(x[3]);
    x[4] = letoh32(x[4]);
    x[5] = letoh32(x[5]);
    x[6] = letoh32(x[6]);
    x[7] = letoh32(x[7]);
    x[8] = letoh32(x[8]);
    x[9] = letoh32(x[9]);
    x[10] = letoh32(x[10]);
    x[11] = letoh32(x[11]);
    x[12] = letoh32(x[12]);
    x[13] = letoh32(x[13]);
    x[14] = letoh32(x[14]);
    x[15] = letoh32(x[15]);

    //Round 1
    FF(a, b, c, d, x[0], 7, md5_k[0]);
    FF(d, a, b, c, x[1], 12, md5_k[1]);
    FF(c, d, a, b, x[2], 17, md5_k[2]);
    FF(b, c, d, a, x[3], 22, md5_k[3]);
    FF(a, b, c, d, x[4], 7, md5_k[4]);
    FF(d, a, b, c, x[5], 12, md5_k[5]);
    FF(c, d, a, b, x[6], 17, md5_k[6]);
    FF(b, c, d, a, x[7], 22, md5_k[7]);
    FF(a, b, c, d, x[8], 7, md5_k[8]);
    FF(d, a, b, c, x[9], 12, md5_k[9]);
    FF(c, d, a, b, x[10], 17, md5_k[10]);
    FF(b, c, d, a, x[11], 22, md5_k[11]);
    FF(a, b, c, d, x[12], 7, md5_k[12]);
    FF(d, a, b, c, x[13], 12, md5_k[13]);
    FF(c, d, a, b, x[14], 17, md5_k[14]);
    FF(b, c, d, a, x[15], 22, md5_k[15]);
    //Round 2
    GG(a, b, c, d, x[1], 5, md5_k[16]);
    GG(d, a, b, c, x[6], 9, md5_k[17]);
    GG(c, d, a, b, x[11], 14, md5_k[18]);
    GG(b, c, d, a, x[0], 20, md5_k[19]);
    GG(a, b, c, d, x[5], 5, md5_k[20]);
    GG(d, a, b, c, x[10], 9, md5_k[21]);
    GG(c, d, a, b, x[15], 14, md5_k[22]);
    GG(b, c, d, a, x[4], 20, md5_k[23]);
    GG(a, b, c, d, x[9], 5, md5_k[24]);
    GG(d, a, b, c, x[14], 9, md5_k[25]);
    GG(c, d, a, b, x[3], 14, md5_k[26]);
    GG(b, c, d, a, x[8], 20, md5_k[27]);
    GG(a, b, c, d, x[13], 5, md5_k[28]);
    GG(d, a, b, c, x[2], 9, md5_k[29]);
    GG(c, d, a, b, x[7], 14, md5_k[30]);
    GG(b, c, d, a, x[12], 20, md5_k[31]);
    //Round 3
    HH(a, b, c, d, x[5], 4, md5_k[32]);
    HH(d, a, b, c, x[8], 11, md5_k[33]);
    HH(c, d, a, b, x[11], 16, md5_k[34]);
    HH(b, c, d, a, x[14], 23, md5_k[35]);
    HH(a, b, c, d, x[1], 4, md5_k[36]);
    HH(d, a, b, c, x[4], 11, md5_k[37]);
    HH(c, d, a, b, x[7], 16, md5_k[38]);
    HH(b, c, d, a, x[10], 23, md5_k[39]);
    HH(a, b, c, d, x[13], 4, md5_k[40]);
    HH(d, a, b, c, x[0], 11, md5_k[41]);
    HH(c, d, a, b, x[3], 16, md5_k[42]);
    HH(b, c, d, a, x[6], 23, md5_k[43]);
    HH(a, b, c, d, x[9], 4, md5_k[44]);
    HH(d, a, b, c, x[12], 11, md5_k[45]);
    HH(c, d, a, b, x[15], 16, md5_k[46]);
    HH(b, c, d, a, x[2], 23, md5_k[47]);
    //Round 4
    II(a, b, c, d, x[0], 6, md5_k[48]);
    II(d, a, b, c, x[7], 10, md5_k[49]);
    II(c, d, a, b, x[14], 15, md5_k[50]);
    II(b, c, d, a, x[5], 21, md5_k[51]);
    II(a, b, c, d, x[12], 6, md5_k[52]);
    II(d, a, b, c, x[3], 10, md5_k[53]);
    II(c, d, a, b, x[10], 15, md5_k[54]);
    II(b, c, d, a, x[1], 21, md5_k[55]);
    II(a, b, c, d, x[8], 6, md5_k[56]);
    II(d, a, b, c, x[15], 10, md5_k[57]);
    II(c, d, a, b, x[6], 15, md5_k[58]);
    II(b, c, d, a, x[13], 21, md5_k[59]);
    II(a, b, c, d, x[4], 6, md5_k[60]);
    II(d, a, b, c, x[11], 10, md5_k[61]);
    II(c, d, a, b, x[2], 15, md5_k[62]);
    II(b, c, d, a, x[9], 21, md5_k[63]);

    //Update the hash value
    context->h32[0] += a;
    context->h32[1] += b;
    context->h32[2] += c;
    context->h32[3] += d;
}

void __cdecl f_md5_init(PHASH_CONTEXT context) {
    //Set initial hash value
    context->h32[0] = 0x67452301;
    context->h32[1] = 0xEFCDAB89;
    context->h32[2] = 0x98BADCFE;
    context->h32[3] = 0x10325476;
    //Number of bytes in the buffer
    context->size = 0;
    //Total length of the message
    context->totalSize = 0;
}

void __cdecl f_md5_update(PHASH_CONTEXT context, const void* data, size_t length) {
	size_t n;
	// Process the incoming data
	while (length > 0) {
		// The buffer can hold at most 64 bytes
		n = MIN(length, 64 - context->size);
		// Copy the data to the buffer
		f_memcpy(context->buffer + context->size, data, n);
		// Update the MD5 context
		context->size += n;
		context->totalSize += n;
		// Advance the data pointer
		data = (unsigned char *)data + n;
		// Remaining bytes to process
		length -= n;
		// Process message in 16-word blocks
		if (context->size == 64) {
			// Transform the 16-word block
			__md5_transform(context);
			// Empty the buffer
			context->size = 0;
		}
	}
}

void __cdecl f_md5_final(PHASH_CONTEXT context, unsigned char* digest) {
	unsigned long i;
	// Length of the original message (before padding)
	unsigned long long total = context->totalSize * 8;
	// Pad the message so that its length is congruent to 56 modulo 64
	size_t padding = (context->size < 56) ? 56 - context->size : 64 + 56 - context->size;
	// Append padding
	f_md5_update(context, md5_padding, padding);
	// Append the length of the original message
	context->w32[14] = htole32((unsigned long)total);
	context->w32[15] = htole32((unsigned long)(total >> 32));
	// Calculate the message digest
	__md5_transform(context);
	// Convert from host byte order to little-endian byte order
	for (i = 0; i < 4; i++)
		context->h32[i] = htole32(context->h32[i]);
	// Copy the resulting digest
	if (digest) f_memcpy(digest, context->digest, MD5_DIGEST_SIZE);
}

void __cdecl f_md5_final_raw(PHASH_CONTEXT context, unsigned char* digest) {
	unsigned long i;
	// Convert from host byte order to little-endian byte order
	for (i = 0; i < 4; i++)
		context->h32[i] = htole32(context->h32[i]);
	// Copy the resulting digest
	f_memcpy(digest, context->digest, MD5_DIGEST_SIZE);
	// Convert from little-endian byte order to host byte order
	for (i = 0; i < 4; i++)
		context->h32[i] = letoh32(context->h32[i]);
}

int __cdecl f_md5_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	// Allocate a memory buffer to hold the MD5 context
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		// Initialize the MD5 context
		f_md5_init(context);
		f_md5_update(context, data, length);
		f_md5_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}
