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

// Macro to access the workspace as a circular buffer

#define A0(block,i)                                 (block[i&15] = ROL32(block[(i+13)&15] ^ block[(i+8)&15] ^ block[(i+2)&15] ^ block[i&15],1))
#define R0(block,v,w,x,y,z,i) z += ((w&(x^y))^y)     + block[i]     + 0x5a827999 + ROL32(v,5); w=ROL32(w,30);
#define R1(block,v,w,x,y,z,i) z += ((w&(x^y))^y)     + A0(block,i) + 0x5a827999 + ROL32(v,5); w=ROL32(w,30);
#define R2(block,v,w,x,y,z,i) z += (w^x^y)           + A0(block,i) + 0x6ed9eba1 + ROL32(v,5); w=ROL32(w,30);
#define R3(block,v,w,x,y,z,i) z += (((w|x)&y)|(w&x)) + A0(block,i) + 0x8f1bbcdc + ROL32(v,5); w=ROL32(w,30);
#define R4(block,v,w,x,y,z,i) z += (w^x^y)           + A0(block,i) + 0xca62c1d6 + ROL32(v,5); w=ROL32(w,30);


// SHA-1 padding
static const unsigned char __sha1_padding[64] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// SHA-1 constants
static const unsigned long sha1_k[4] = {
	0x5A827999,
	0x6ED9EBA1,
	0x8F1BBCDC,
	0xCA62C1D6
};


// Process message in 16-word blocks

void __cdecl __sha1_transform(PHASH_CONTEXT context) {
	//Initialize the 5 working registers
	unsigned long a = context->h32[0];
	unsigned long b = context->h32[1];
	unsigned long c = context->h32[2];
	unsigned long d = context->h32[3];
	unsigned long e = context->h32[4];

	//Convert from big-endian byte order to host byte order
	context->w32[0] = betoh32(context->w32[0]);
	context->w32[1] = betoh32(context->w32[1]);
	context->w32[2] = betoh32(context->w32[2]);
	context->w32[3] = betoh32(context->w32[3]);
	context->w32[4] = betoh32(context->w32[4]);
	context->w32[5] = betoh32(context->w32[5]);
	context->w32[6] = betoh32(context->w32[6]);
	context->w32[7] = betoh32(context->w32[7]);
	context->w32[8] = betoh32(context->w32[8]);
	context->w32[9] = betoh32(context->w32[9]);
	context->w32[10] = betoh32(context->w32[10]);
	context->w32[11] = betoh32(context->w32[11]);
	context->w32[12] = betoh32(context->w32[12]);
	context->w32[13] = betoh32(context->w32[13]);
	context->w32[14] = betoh32(context->w32[14]);
	context->w32[15] = betoh32(context->w32[15]);

	//SHA-1 hash computation
	R0(context->w32, a, b, c, d, e, 0);
	R0(context->w32, e, a, b, c, d, 1);
	R0(context->w32, d, e, a, b, c, 2);
	R0(context->w32, c, d, e, a, b, 3);
	R0(context->w32, b, c, d, e, a, 4);
	R0(context->w32, a, b, c, d, e, 5);
	R0(context->w32, e, a, b, c, d, 6);
	R0(context->w32, d, e, a, b, c, 7);
	R0(context->w32, c, d, e, a, b, 8);
	R0(context->w32, b, c, d, e, a, 9);
	R0(context->w32, a, b, c, d, e, 10);
	R0(context->w32, e, a, b, c, d, 11);
	R0(context->w32, d, e, a, b, c, 12);
	R0(context->w32, c, d, e, a, b, 13);
	R0(context->w32, b, c, d, e, a, 14);
	R0(context->w32, a, b, c, d, e, 15);
	R1(context->w32, e, a, b, c, d, 16);
	R1(context->w32, d, e, a, b, c, 17);
	R1(context->w32, c, d, e, a, b, 18);
	R1(context->w32, b, c, d, e, a, 19);
	R2(context->w32, a, b, c, d, e, 20);
	R2(context->w32, e, a, b, c, d, 21);
	R2(context->w32, d, e, a, b, c, 22);
	R2(context->w32, c, d, e, a, b, 23);
	R2(context->w32, b, c, d, e, a, 24);
	R2(context->w32, a, b, c, d, e, 25);
	R2(context->w32, e, a, b, c, d, 26);
	R2(context->w32, d, e, a, b, c, 27);
	R2(context->w32, c, d, e, a, b, 28);
	R2(context->w32, b, c, d, e, a, 29);
	R2(context->w32, a, b, c, d, e, 30);
	R2(context->w32, e, a, b, c, d, 31);
	R2(context->w32, d, e, a, b, c, 32);
	R2(context->w32, c, d, e, a, b, 33);
	R2(context->w32, b, c, d, e, a, 34);
	R2(context->w32, a, b, c, d, e, 35);
	R2(context->w32, e, a, b, c, d, 36);
	R2(context->w32, d, e, a, b, c, 37);
	R2(context->w32, c, d, e, a, b, 38);
	R2(context->w32, b, c, d, e, a, 39);
	R3(context->w32, a, b, c, d, e, 40);
	R3(context->w32, e, a, b, c, d, 41);
	R3(context->w32, d, e, a, b, c, 42);
	R3(context->w32, c, d, e, a, b, 43);
	R3(context->w32, b, c, d, e, a, 44);
	R3(context->w32, a, b, c, d, e, 45);
	R3(context->w32, e, a, b, c, d, 46);
	R3(context->w32, d, e, a, b, c, 47);
	R3(context->w32, c, d, e, a, b, 48);
	R3(context->w32, b, c, d, e, a, 49);
	R3(context->w32, a, b, c, d, e, 50);
	R3(context->w32, e, a, b, c, d, 51);
	R3(context->w32, d, e, a, b, c, 52);
	R3(context->w32, c, d, e, a, b, 53);
	R3(context->w32, b, c, d, e, a, 54);
	R3(context->w32, a, b, c, d, e, 55);
	R3(context->w32, e, a, b, c, d, 56);
	R3(context->w32, d, e, a, b, c, 57);
	R3(context->w32, c, d, e, a, b, 58);
	R3(context->w32, b, c, d, e, a, 59);
	R4(context->w32, a, b, c, d, e, 60);
	R4(context->w32, e, a, b, c, d, 61);
	R4(context->w32, d, e, a, b, c, 62);
	R4(context->w32, c, d, e, a, b, 63);
	R4(context->w32, b, c, d, e, a, 64);
	R4(context->w32, a, b, c, d, e, 65);
	R4(context->w32, e, a, b, c, d, 66);
	R4(context->w32, d, e, a, b, c, 67);
	R4(context->w32, c, d, e, a, b, 68);
	R4(context->w32, b, c, d, e, a, 69);
	R4(context->w32, a, b, c, d, e, 70);
	R4(context->w32, e, a, b, c, d, 71);
	R4(context->w32, d, e, a, b, c, 72);
	R4(context->w32, c, d, e, a, b, 73);
	R4(context->w32, b, c, d, e, a, 74);
	R4(context->w32, a, b, c, d, e, 75);
	R4(context->w32, e, a, b, c, d, 76);
	R4(context->w32, d, e, a, b, c, 77);
	R4(context->w32, c, d, e, a, b, 78);
	R4(context->w32, b, c, d, e, a, 79);

	//Update the hash value
	context->h32[0] += a;
	context->h32[1] += b;
	context->h32[2] += c;
	context->h32[3] += d;
	context->h32[4] += e;
}


// Initialize SHA-1 message digest context

void __cdecl f_sha1_init(PHASH_CONTEXT context) {
	//Set initial hash value
	context->h32[0] = 0x67452301;
	context->h32[1] = 0xEFCDAB89;
	context->h32[2] = 0x98BADCFE;
	context->h32[3] = 0x10325476;
	context->h32[4] = 0xC3D2E1F0;
	// Number of bytes in the buffer
	context->size = 0;
	// Total length of the message
	context->totalSize = 0;
}


// Update the SHA-1 context with a portion of the message being hashed

void __cdecl f_sha1_update(PHASH_CONTEXT context, const void* data, size_t length) {
	size_t n;
	// Process the incoming data
	while (length > 0) {
		// The buffer can hold at most 64 bytes
		n = MIN(length, 64 - context->size);
		// Copy the data to the buffer
		f_memcpy(context->buffer + context->size, data, n);
		// Update the SHA-1 context
		context->size += n;
		context->totalSize += n;
		// Advance the data pointer
		data = (unsigned char*)data + n;
		// Remaining bytes to process
		length -= n;
		// Process message in 16-word blocks
		if (context->size == 64) {
			// Transform the 16-word block
			__sha1_transform(context);
			// Empty the buffer
			context->size = 0;
		}
	}
}


// Finish the SHA-1 message digest

void __cdecl f_sha1_final(PHASH_CONTEXT context, unsigned char* digest) {
	size_t paddingSize;
	unsigned long long totalSize;
	if (!digest) return;
	// Length of the original message (before padding)
	totalSize = context->totalSize * 8;
	// Pad the message so that its length is congruent to 56 modulo 64
	paddingSize = context->size < 56 ? 56 - context->size : 64 + 56 - context->size;
	// Append padding
	f_sha1_update(context, __sha1_padding, paddingSize);
	// Append the length of the original message
	context->w32[14] = htobe32((unsigned long)(totalSize >> 32));
	context->w32[15] = htobe32((unsigned long)totalSize);
	// Calculate the message digest
	__sha1_transform(context);
	// Convert from host byte order to big-endian byte order
	context->h32[0] = htobe32(context->h32[0]);
	context->h32[1] = htobe32(context->h32[1]);
	context->h32[2] = htobe32(context->h32[2]);
	context->h32[3] = htobe32(context->h32[3]);
	context->h32[4] = htobe32(context->h32[4]);
	// Copy the resulting digest
	if (digest)
		f_memcpy(digest, context->digest, SHA1_DIGEST_SIZE);
}


// Finish the SHA-1 message digest (no padding is added)

void __cdecl f_sha1_final_raw(PHASH_CONTEXT context, unsigned char* digest) {
	// Convert from host byte order to big-endian byte order
	context->h32[0] = htobe32(context->h32[0]);
	context->h32[1] = htobe32(context->h32[1]);
	context->h32[2] = htobe32(context->h32[2]);
	context->h32[3] = htobe32(context->h32[3]);
	context->h32[4] = htobe32(context->h32[4]);
	// Copy the resulting digest
	f_memcpy(digest, context->digest, SHA1_DIGEST_SIZE);
	// Convert from big-endian byte order to host byte order
	context->h32[0] = betoh32(context->h32[0]);
	context->h32[1] = betoh32(context->h32[1]);
	context->h32[2] = betoh32(context->h32[2]);
	context->h32[3] = betoh32(context->h32[3]);
	context->h32[4] = betoh32(context->h32[4]);
}

// Digest a message using SHA-1

int __cdecl f_sha1_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha1_init(context);
		f_sha1_update(context, data, length);
		f_sha1_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}
