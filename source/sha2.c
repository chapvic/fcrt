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

// SHA-2 common auxiliary functions
#define B0(b, i)     b[(i) & 15]
#define B1(b, i, n)  b[((i) + n) & 15]

#define CH(x, y, z)  (((x) & (y)) | (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))

// SHA-256 auxiliary functions
#define SD1(x) (ROR32(x, 2) ^ ROR32(x, 13) ^ ROR32(x, 22))
#define SD2(x) (ROR32(x, 6) ^ ROR32(x, 11) ^ ROR32(x, 25))
#define SD3(x) (ROR32(x, 7) ^ ROR32(x, 18) ^ SHR(x, 3))
#define SD4(x) (ROR32(x, 17) ^ ROR32(x, 19) ^ SHR(x, 10))

#define FD0(x,k,l,m,n,o,p,q,r,i) n += r + SD2(o) + CH(o, p, q) + __sha256_k[i] + B0(x, i); r += SD2(o) + CH(o, p, q) + __sha256_k[i] + B0(x, i) + SD1(k) + MAJ(k, l, m)
#define FD1(x,k,l,m,n,o,p,q,r,i) B0(x, i) += SD4(B1(x, i, 14)) + B1(x, i, 9) + SD3(B1(x, i, 1)); FD0(x,k,l,m,n,o,p,q,r,i)

// SHA-512 auxiliary functions
#define SQ1(x) (ROR64(x, 28) ^ ROR64(x, 34) ^ ROR64(x, 39))
#define SQ2(x) (ROR64(x, 14) ^ ROR64(x, 18) ^ ROR64(x, 41))
#define SQ3(x) (ROR64(x, 1) ^ ROR64(x, 8) ^ SHR(x, 7))
#define SQ4(x) (ROR64(x, 19) ^ ROR64(x, 61) ^ SHR(x, 6))

#define FQ0(x,k,l,m,n,o,p,q,r,i) n += r + SQ2(o) + CH(o, p, q) + __sha512_k[i] + B0(x, i); r += SQ2(o) + CH(o, p, q) + __sha512_k[i] + B0(x, i) + SQ1(k) + MAJ(k, l, m)
#define FQ1(x,k,l,m,n,o,p,q,r,i) B0(x, i) += SQ4(B1(x, i, 14)) + B1(x, i, 9) + SQ3(B1(x, i, 1)); FQ0(x,k,l,m,n,o,p,q,r,i)

// SHA-256 padding
static const unsigned char __sha256_padding[64] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// SHA-512 padding
static const unsigned char __sha512_padding[128] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// SHA-256 constants
static const unsigned long __sha256_k[64] = {
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
	0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
	0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
	0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
	0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
	0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};

// SHA-512 constants
static const unsigned long long __sha512_k[80] = {
	0x428A2F98D728AE22, 0x7137449123EF65CD, 0xB5C0FBCFEC4D3B2F, 0xE9B5DBA58189DBBC,
	0x3956C25BF348B538, 0x59F111F1B605D019, 0x923F82A4AF194F9B, 0xAB1C5ED5DA6D8118,
	0xD807AA98A3030242, 0x12835B0145706FBE, 0x243185BE4EE4B28C, 0x550C7DC3D5FFB4E2,
	0x72BE5D74F27B896F, 0x80DEB1FE3B1696B1, 0x9BDC06A725C71235, 0xC19BF174CF692694,
	0xE49B69C19EF14AD2, 0xEFBE4786384F25E3, 0x0FC19DC68B8CD5B5, 0x240CA1CC77AC9C65,
	0x2DE92C6F592B0275, 0x4A7484AA6EA6E483, 0x5CB0A9DCBD41FBD4, 0x76F988DA831153B5,
	0x983E5152EE66DFAB, 0xA831C66D2DB43210, 0xB00327C898FB213F, 0xBF597FC7BEEF0EE4,
	0xC6E00BF33DA88FC2, 0xD5A79147930AA725, 0x06CA6351E003826F, 0x142929670A0E6E70,
	0x27B70A8546D22FFC, 0x2E1B21385C26C926, 0x4D2C6DFC5AC42AED, 0x53380D139D95B3DF,
	0x650A73548BAF63DE, 0x766A0ABB3C77B2A8, 0x81C2C92E47EDAEE6, 0x92722C851482353B,
	0xA2BFE8A14CF10364, 0xA81A664BBC423001, 0xC24B8B70D0F89791, 0xC76C51A30654BE30,
	0xD192E819D6EF5218, 0xD69906245565A910, 0xF40E35855771202A, 0x106AA07032BBD1B8,
	0x19A4C116B8D2D0C8, 0x1E376C085141AB53, 0x2748774CDF8EEB99, 0x34B0BCB5E19B48A8,
	0x391C0CB3C5C95A63, 0x4ED8AA4AE3418ACB, 0x5B9CCA4F7763E373, 0x682E6FF3D6B2B8A3,
	0x748F82EE5DEFB2FC, 0x78A5636F43172F60, 0x84C87814A1F0AB72, 0x8CC702081A6439EC,
	0x90BEFFFA23631E28, 0xA4506CEBDE82BDE9, 0xBEF9A3F7B2C67915, 0xC67178F2E372532B,
	0xCA273ECEEA26619C, 0xD186B8C721C0C207, 0xEADA7DD6CDE0EB1E, 0xF57D4F7FEE6ED178,
	0x06F067AA72176FBA, 0x0A637DC5A2C898A6, 0x113F9804BEF90DAE, 0x1B710B35131C471B,
	0x28DB77F523047D84, 0x32CAAB7B40C72493, 0x3C9EBE0A15C9BEBC, 0x431D67C49C100D4C,
	0x4CC5D4BECB3E42B6, 0x597F299CFC657E2A, 0x5FCB6FAB3AD6FAEC, 0x6C44198C4A475817
};


// Process message in 16-word blocks

void __cdecl __sha256_transform(PHASH_CONTEXT context) {
	// Initialize the 8 working registers
	unsigned long a = context->h32[0];
	unsigned long b = context->h32[1];
	unsigned long c = context->h32[2];
	unsigned long d = context->h32[3];
	unsigned long e = context->h32[4];
	unsigned long f = context->h32[5];
	unsigned long g = context->h32[6];
	unsigned long h = context->h32[7];

	// Convert from big-endian byte order to host byte order
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

	// Part 1
	FD0(context->w32, a, b, c, d, e, f, g, h, 0);
	FD0(context->w32, h, a, b, c, d, e, f, g, 1);
	FD0(context->w32, g, h, a, b, c, d, e, f, 2);
	FD0(context->w32, f, g, h, a, b, c, d, e, 3);
	FD0(context->w32, e, f, g, h, a, b, c, d, 4);
	FD0(context->w32, d, e, f, g, h, a, b, c, 5);
	FD0(context->w32, c, d, e, f, g, h, a, b, 6);
	FD0(context->w32, b, c, d, e, f, g, h, a, 7);

	FD0(context->w32, a, b, c, d, e, f, g, h, 8);
	FD0(context->w32, h, a, b, c, d, e, f, g, 9);
	FD0(context->w32, g, h, a, b, c, d, e, f, 10);
	FD0(context->w32, f, g, h, a, b, c, d, e, 11);
	FD0(context->w32, e, f, g, h, a, b, c, d, 12);
	FD0(context->w32, d, e, f, g, h, a, b, c, 13);
	FD0(context->w32, c, d, e, f, g, h, a, b, 14);
	FD0(context->w32, b, c, d, e, f, g, h, a, 15);

	// Part 2
	FD1(context->w32, a, b, c, d, e, f, g, h, 16);
	FD1(context->w32, h, a, b, c, d, e, f, g, 17);
	FD1(context->w32, g, h, a, b, c, d, e, f, 18);
	FD1(context->w32, f, g, h, a, b, c, d, e, 19);
	FD1(context->w32, e, f, g, h, a, b, c, d, 20);
	FD1(context->w32, d, e, f, g, h, a, b, c, 21);
	FD1(context->w32, c, d, e, f, g, h, a, b, 22);
	FD1(context->w32, b, c, d, e, f, g, h, a, 23);

	FD1(context->w32, a, b, c, d, e, f, g, h, 24);
	FD1(context->w32, h, a, b, c, d, e, f, g, 25);
	FD1(context->w32, g, h, a, b, c, d, e, f, 26);
	FD1(context->w32, f, g, h, a, b, c, d, e, 27);
	FD1(context->w32, e, f, g, h, a, b, c, d, 28);
	FD1(context->w32, d, e, f, g, h, a, b, c, 29);
	FD1(context->w32, c, d, e, f, g, h, a, b, 30);
	FD1(context->w32, b, c, d, e, f, g, h, a, 31);

	FD1(context->w32, a, b, c, d, e, f, g, h, 32);
	FD1(context->w32, h, a, b, c, d, e, f, g, 33);
	FD1(context->w32, g, h, a, b, c, d, e, f, 34);
	FD1(context->w32, f, g, h, a, b, c, d, e, 35);
	FD1(context->w32, e, f, g, h, a, b, c, d, 36);
	FD1(context->w32, d, e, f, g, h, a, b, c, 37);
	FD1(context->w32, c, d, e, f, g, h, a, b, 38);
	FD1(context->w32, b, c, d, e, f, g, h, a, 39);

	FD1(context->w32, a, b, c, d, e, f, g, h, 40);
	FD1(context->w32, h, a, b, c, d, e, f, g, 41);
	FD1(context->w32, g, h, a, b, c, d, e, f, 42);
	FD1(context->w32, f, g, h, a, b, c, d, e, 43);
	FD1(context->w32, e, f, g, h, a, b, c, d, 44);
	FD1(context->w32, d, e, f, g, h, a, b, c, 45);
	FD1(context->w32, c, d, e, f, g, h, a, b, 46);
	FD1(context->w32, b, c, d, e, f, g, h, a, 47);

	FD1(context->w32, a, b, c, d, e, f, g, h, 48);
	FD1(context->w32, h, a, b, c, d, e, f, g, 49);
	FD1(context->w32, g, h, a, b, c, d, e, f, 50);
	FD1(context->w32, f, g, h, a, b, c, d, e, 51);
	FD1(context->w32, e, f, g, h, a, b, c, d, 52);
	FD1(context->w32, d, e, f, g, h, a, b, c, 53);
	FD1(context->w32, c, d, e, f, g, h, a, b, 54);
	FD1(context->w32, b, c, d, e, f, g, h, a, 55);

	FD1(context->w32, a, b, c, d, e, f, g, h, 56);
	FD1(context->w32, h, a, b, c, d, e, f, g, 57);
	FD1(context->w32, g, h, a, b, c, d, e, f, 58);
	FD1(context->w32, f, g, h, a, b, c, d, e, 59);
	FD1(context->w32, e, f, g, h, a, b, c, d, 60);
	FD1(context->w32, d, e, f, g, h, a, b, c, 61);
	FD1(context->w32, c, d, e, f, g, h, a, b, 62);
	FD1(context->w32, b, c, d, e, f, g, h, a, 63);
	
	// Update the hash value
	context->h32[0] += a;
	context->h32[1] += b;
	context->h32[2] += c;
	context->h32[3] += d;
	context->h32[4] += e;
	context->h32[5] += f;
	context->h32[6] += g;
	context->h32[7] += h;
}

// Initialize SHA-256 message digest context

void __cdecl f_sha256_init(PHASH_CONTEXT context) {
	// Set initial hash value
	context->h32[0] = 0x6A09E667;
	context->h32[1] = 0xBB67AE85;
	context->h32[2] = 0x3C6EF372;
	context->h32[3] = 0xA54FF53A;
	context->h32[4] = 0x510E527F;
	context->h32[5] = 0x9B05688C;
	context->h32[6] = 0x1F83D9AB;
	context->h32[7] = 0x5BE0CD19;
	// Number of bytes in the buffer
	context->size = 0;
	// Total length of the message
	context->totalSize = 0;
}


// Update the SHA-256 context with a portion of the message being hashed

void __cdecl f_sha256_update(PHASH_CONTEXT context, const void* data, size_t length) {
	size_t n;
	// Process the incoming data
	while (length > 0) {
		// The buffer can hold at most 64 bytes
		n = MIN(length, 64 - context->size);
		// Copy the data to the buffer
		f_memcpy(context->buffer + context->size, data, n);
		// Update the SHA-256 context
		context->size += n;
		context->totalSize += n;
		// Advance the data pointer
		data = (unsigned char*)data + n;
		// Remaining bytes to process
		length -= n;
		// Process message in 16-word blocks
		if (context->size == 64) {
			// Transform the 16-word block
			__sha256_transform(context);
			// Empty the buffer
			context->size = 0;
		}
	}
}


// Finish the SHA-256 message digest

void __cdecl f_sha256_final(PHASH_CONTEXT context, unsigned char* digest) {
	size_t paddingSize;
	unsigned long long totalSize;
	// Length of the original message (before padding)
	totalSize = context->totalSize * 8;
	// Pad the message so that its length is congruent to 56 modulo 64
	paddingSize = context->size < 56 ? paddingSize = 56 - context->size : 64 + 56 - context->size;
	// Append padding
	f_sha256_update(context, __sha256_padding, paddingSize);
	// Append the length of the original message
	context->w32[14] = htobe32((unsigned long)(totalSize >> 32));
	context->w32[15] = htobe32((unsigned long)totalSize);
	// Calculate the message digest
	__sha256_transform(context);
	// Convert from host byte order to big-endian byte order
	context->h32[0] = htobe32(context->h32[0]);
	context->h32[1] = htobe32(context->h32[1]);
	context->h32[2] = htobe32(context->h32[2]);
	context->h32[3] = htobe32(context->h32[3]);
	context->h32[4] = htobe32(context->h32[4]);
	context->h32[5] = htobe32(context->h32[5]);
	context->h32[6] = htobe32(context->h32[6]);
	context->h32[7] = htobe32(context->h32[7]);
	// Copy the resulting digest
	if (digest)
		f_memcpy(digest, context->digest, SHA256_DIGEST_SIZE);
}

// Finish the SHA-256 message digest (no padding is added)

void __cdecl f_sha256_final_raw(PHASH_CONTEXT context, unsigned char* digest) {
	// Convert from host byte order to big-endian byte order
	context->h32[0] = htobe32(context->h32[0]);
	context->h32[1] = htobe32(context->h32[1]);
	context->h32[2] = htobe32(context->h32[2]);
	context->h32[3] = htobe32(context->h32[3]);
	context->h32[4] = htobe32(context->h32[4]);
	context->h32[5] = htobe32(context->h32[5]);
	context->h32[6] = htobe32(context->h32[6]);
	context->h32[7] = htobe32(context->h32[7]);
	// Copy the resulting digest
	f_memcpy(digest, context->digest, SHA256_DIGEST_SIZE);
	// Convert from big-endian byte order to host byte order
	context->h32[0] = betoh32(context->h32[0]);
	context->h32[1] = betoh32(context->h32[1]);
	context->h32[2] = betoh32(context->h32[2]);
	context->h32[3] = betoh32(context->h32[3]);
	context->h32[4] = betoh32(context->h32[4]);
	context->h32[5] = betoh32(context->h32[5]);
	context->h32[6] = betoh32(context->h32[6]);
	context->h32[7] = betoh32(context->h32[7]);
}

// Digest a message using SHA-256

int __cdecl f_sha256_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha256_init(context);
		f_sha256_update(context, data, length);
		f_sha256_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}

// Initialize SHA-224 message digest context

void __cdecl f_sha224_init(PHASH_CONTEXT context) {
	// Set initial hash value
	context->h32[0] = 0xC1059ED8;
	context->h32[1] = 0x367CD507;
	context->h32[2] = 0x3070DD17;
	context->h32[3] = 0xF70E5939;
	context->h32[4] = 0xFFC00B31;
	context->h32[5] = 0x68581511;
	context->h32[6] = 0x64F98FA7;
	context->h32[7] = 0xBEFA4FA4;
	// Number of bytes in the buffer
	context->size = 0;
	// Total length of the message
	context->totalSize = 0;
}

// Update the SHA-224 context with a portion of the message being hashed

void __cdecl f_sha224_update(PHASH_CONTEXT context, const void* data, size_t length) {
	// The function is defined in the exact same manner as SHA-256
	f_sha256_update(context, data, length);
}

// Finish the SHA-224 message digest

void __cdecl f_sha224_final(PHASH_CONTEXT context, unsigned char* digest) {
	// The function is defined in the exact same manner as SHA-256
	f_sha256_final(context, nullptr);
	// Copy the resulting digest
	if (digest)
		f_memcpy(digest, context->digest, SHA224_DIGEST_SIZE);
}

// Finish the SHA-224 message digest (no padding is added)

void __cdecl f_sha224_final_raw(PHASH_CONTEXT context, unsigned char* digest) {
	// Convert from host byte order to big-endian byte order
	context->h32[0] = htobe32(context->h32[0]);
	context->h32[1] = htobe32(context->h32[1]);
	context->h32[2] = htobe32(context->h32[2]);
	context->h32[3] = htobe32(context->h32[3]);
	context->h32[4] = htobe32(context->h32[4]);
	context->h32[5] = htobe32(context->h32[5]);
	context->h32[6] = htobe32(context->h32[6]);
	context->h32[7] = htobe32(context->h32[7]);
	// Copy the resulting digest
	f_memcpy(digest, context->digest, SHA224_DIGEST_SIZE);
	// Convert from big-endian byte order to host byte order
	context->h32[0] = betoh32(context->h32[0]);
	context->h32[1] = betoh32(context->h32[1]);
	context->h32[2] = betoh32(context->h32[2]);
	context->h32[3] = betoh32(context->h32[3]);
	context->h32[4] = betoh32(context->h32[4]);
	context->h32[5] = betoh32(context->h32[5]);
	context->h32[6] = betoh32(context->h32[6]);
	context->h32[7] = betoh32(context->h32[7]);
}


// Digest a message using SHA-224

int __cdecl f_sha224_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha224_init(context);
		f_sha224_update(context, data, length);
		f_sha224_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}


// Process message in 16-word blocks

void __cdecl __sha512_transform(PHASH_CONTEXT context) {
	// Initialize the 8 working registers
	unsigned long long a = context->h64[0];
	unsigned long long b = context->h64[1];
	unsigned long long c = context->h64[2];
	unsigned long long d = context->h64[3];
	unsigned long long e = context->h64[4];
	unsigned long long f = context->h64[5];
	unsigned long long g = context->h64[6];
	unsigned long long h = context->h64[7];

	// Convert from big-endian byte order to host byte order
	context->w64[0] = betoh64(context->w64[0]);
	context->w64[1] = betoh64(context->w64[1]);
	context->w64[2] = betoh64(context->w64[2]);
	context->w64[3] = betoh64(context->w64[3]);
	context->w64[4] = betoh64(context->w64[4]);
	context->w64[5] = betoh64(context->w64[5]);
	context->w64[6] = betoh64(context->w64[6]);
	context->w64[7] = betoh64(context->w64[7]);
	context->w64[8] = betoh64(context->w64[8]);
	context->w64[9] = betoh64(context->w64[9]);
	context->w64[10] = betoh64(context->w64[10]);
	context->w64[11] = betoh64(context->w64[11]);
	context->w64[12] = betoh64(context->w64[12]);
	context->w64[13] = betoh64(context->w64[13]);
	context->w64[14] = betoh64(context->w64[14]);
	context->w64[15] = betoh64(context->w64[15]);

	// Part 1
	FQ0(context->w64, a, b, c, d, e, f, g, h, 0);
	FQ0(context->w64, h, a, b, c, d, e, f, g, 1);
	FQ0(context->w64, g, h, a, b, c, d, e, f, 2);
	FQ0(context->w64, f, g, h, a, b, c, d, e, 3);
	FQ0(context->w64, e, f, g, h, a, b, c, d, 4);
	FQ0(context->w64, d, e, f, g, h, a, b, c, 5);
	FQ0(context->w64, c, d, e, f, g, h, a, b, 6);
	FQ0(context->w64, b, c, d, e, f, g, h, a, 7);

	FQ0(context->w64, a, b, c, d, e, f, g, h, 8);
	FQ0(context->w64, h, a, b, c, d, e, f, g, 9);
	FQ0(context->w64, g, h, a, b, c, d, e, f, 10);
	FQ0(context->w64, f, g, h, a, b, c, d, e, 11);
	FQ0(context->w64, e, f, g, h, a, b, c, d, 12);
	FQ0(context->w64, d, e, f, g, h, a, b, c, 13);
	FQ0(context->w64, c, d, e, f, g, h, a, b, 14);
	FQ0(context->w64, b, c, d, e, f, g, h, a, 15);

	// Part 2
	FQ1(context->w64, a, b, c, d, e, f, g, h, 16);
	FQ1(context->w64, h, a, b, c, d, e, f, g, 17);
	FQ1(context->w64, g, h, a, b, c, d, e, f, 18);
	FQ1(context->w64, f, g, h, a, b, c, d, e, 19);
	FQ1(context->w64, e, f, g, h, a, b, c, d, 20);
	FQ1(context->w64, d, e, f, g, h, a, b, c, 21);
	FQ1(context->w64, c, d, e, f, g, h, a, b, 22);
	FQ1(context->w64, b, c, d, e, f, g, h, a, 23);

	FQ1(context->w64, a, b, c, d, e, f, g, h, 24);
	FQ1(context->w64, h, a, b, c, d, e, f, g, 25);
	FQ1(context->w64, g, h, a, b, c, d, e, f, 26);
	FQ1(context->w64, f, g, h, a, b, c, d, e, 27);
	FQ1(context->w64, e, f, g, h, a, b, c, d, 28);
	FQ1(context->w64, d, e, f, g, h, a, b, c, 29);
	FQ1(context->w64, c, d, e, f, g, h, a, b, 30);
	FQ1(context->w64, b, c, d, e, f, g, h, a, 31);

	FQ1(context->w64, a, b, c, d, e, f, g, h, 32);
	FQ1(context->w64, h, a, b, c, d, e, f, g, 33);
	FQ1(context->w64, g, h, a, b, c, d, e, f, 34);
	FQ1(context->w64, f, g, h, a, b, c, d, e, 35);
	FQ1(context->w64, e, f, g, h, a, b, c, d, 36);
	FQ1(context->w64, d, e, f, g, h, a, b, c, 37);
	FQ1(context->w64, c, d, e, f, g, h, a, b, 38);
	FQ1(context->w64, b, c, d, e, f, g, h, a, 39);

	FQ1(context->w64, a, b, c, d, e, f, g, h, 40);
	FQ1(context->w64, h, a, b, c, d, e, f, g, 41);
	FQ1(context->w64, g, h, a, b, c, d, e, f, 42);
	FQ1(context->w64, f, g, h, a, b, c, d, e, 43);
	FQ1(context->w64, e, f, g, h, a, b, c, d, 44);
	FQ1(context->w64, d, e, f, g, h, a, b, c, 45);
	FQ1(context->w64, c, d, e, f, g, h, a, b, 46);
	FQ1(context->w64, b, c, d, e, f, g, h, a, 47);

	FQ1(context->w64, a, b, c, d, e, f, g, h, 48);
	FQ1(context->w64, h, a, b, c, d, e, f, g, 49);
	FQ1(context->w64, g, h, a, b, c, d, e, f, 50);
	FQ1(context->w64, f, g, h, a, b, c, d, e, 51);
	FQ1(context->w64, e, f, g, h, a, b, c, d, 52);
	FQ1(context->w64, d, e, f, g, h, a, b, c, 53);
	FQ1(context->w64, c, d, e, f, g, h, a, b, 54);
	FQ1(context->w64, b, c, d, e, f, g, h, a, 55);

	FQ1(context->w64, a, b, c, d, e, f, g, h, 56);
	FQ1(context->w64, h, a, b, c, d, e, f, g, 57);
	FQ1(context->w64, g, h, a, b, c, d, e, f, 58);
	FQ1(context->w64, f, g, h, a, b, c, d, e, 59);
	FQ1(context->w64, e, f, g, h, a, b, c, d, 60);
	FQ1(context->w64, d, e, f, g, h, a, b, c, 61);
	FQ1(context->w64, c, d, e, f, g, h, a, b, 62);
	FQ1(context->w64, b, c, d, e, f, g, h, a, 63);

	FQ1(context->w64, a, b, c, d, e, f, g, h, 64);
	FQ1(context->w64, h, a, b, c, d, e, f, g, 65);
	FQ1(context->w64, g, h, a, b, c, d, e, f, 66);
	FQ1(context->w64, f, g, h, a, b, c, d, e, 67);
	FQ1(context->w64, e, f, g, h, a, b, c, d, 68);
	FQ1(context->w64, d, e, f, g, h, a, b, c, 69);
	FQ1(context->w64, c, d, e, f, g, h, a, b, 70);
	FQ1(context->w64, b, c, d, e, f, g, h, a, 71);

	FQ1(context->w64, a, b, c, d, e, f, g, h, 72);
	FQ1(context->w64, h, a, b, c, d, e, f, g, 73);
	FQ1(context->w64, g, h, a, b, c, d, e, f, 74);
	FQ1(context->w64, f, g, h, a, b, c, d, e, 75);
	FQ1(context->w64, e, f, g, h, a, b, c, d, 76);
	FQ1(context->w64, d, e, f, g, h, a, b, c, 77);
	FQ1(context->w64, c, d, e, f, g, h, a, b, 78);
	FQ1(context->w64, b, c, d, e, f, g, h, a, 79);

	// Update the hash value
	context->h64[0] += a;
	context->h64[1] += b;
	context->h64[2] += c;
	context->h64[3] += d;
	context->h64[4] += e;
	context->h64[5] += f;
	context->h64[6] += g;
	context->h64[7] += h;
}

// Initialize SHA-512 message digest context

void __cdecl f_sha512_init(PHASH_CONTEXT context) {
	// Set initial hash value
	context->h64[0] = 0x6A09E667F3BCC908;
	context->h64[1] = 0xBB67AE8584CAA73B;
	context->h64[2] = 0x3C6EF372FE94F82B;
	context->h64[3] = 0xA54FF53A5F1D36F1;
	context->h64[4] = 0x510E527FADE682D1;
	context->h64[5] = 0x9B05688C2B3E6C1F;
	context->h64[6] = 0x1F83D9ABFB41BD6B;
	context->h64[7] = 0x5BE0CD19137E2179;
	// Number of bytes in the buffer
	context->size = 0;
	// Total length of the message
	context->totalSize = 0;
}


// Update the SHA-512 context with a portion of the message being hashed

void __cdecl f_sha512_update(PHASH_CONTEXT context, const void* data, size_t length) {
	size_t n;
	// Process the incoming data
	while (length > 0) {
		// The buffer can hold at most 128 bytes
		n = MIN(length, 128 - context->size);
		// Copy the data to the buffer
		f_memcpy(context->buffer + context->size, data, n);
		// Update the SHA-512 context
		context->size += n;
		context->totalSize += n;
		// Advance the data pointer
		data = (unsigned char*)data + n;
		// Remaining bytes to process
		length -= n;
		// Process message in 16-word blocks
		if (context->size == 128) {
			// Transform the 16-word block
			__sha512_transform(context);
			// Empty the buffer
			context->size = 0;
		}
	}
}


// Finish the SHA-512 message digest

void __cdecl f_sha512_final(PHASH_CONTEXT context, unsigned char* digest) {
	size_t paddingSize;
	unsigned long long totalSize;
	// Length of the original message (before padding)
	totalSize = context->totalSize * 8;
	// Pad the message so that its length is congruent to 112 modulo 128
	paddingSize = context->size < 112 ? 112 - context->size : 128 + 112 - context->size;
	// Append padding
	f_sha512_update(context, __sha512_padding, paddingSize);
	// Append the length of the original message
	context->w64[14] = 0;
	context->w64[15] = htobe64(totalSize);
	// Calculate the message digest
	__sha512_transform(context);
	// Convert from host byte order to big-endian byte order
	context->h64[0] = htobe64(context->h64[0]);
	context->h64[1] = htobe64(context->h64[1]);
	context->h64[2] = htobe64(context->h64[2]);
	context->h64[3] = htobe64(context->h64[3]);
	context->h64[4] = htobe64(context->h64[4]);
	context->h64[5] = htobe64(context->h64[5]);
	context->h64[6] = htobe64(context->h64[6]);
	context->h64[7] = htobe64(context->h64[7]);
	// Copy the resulting digest
	if (digest)
		f_memcpy(digest, context->digest, SHA512_DIGEST_SIZE);
}


// Digest a message using SHA-512

int __cdecl f_sha512_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha512_init(context);
		f_sha512_update(context, data, length);
		f_sha512_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}


// Initialize SHA-384 message digest context

void __cdecl f_sha384_init(PHASH_CONTEXT context) {
	// Set initial hash value
	context->h64[0] = 0xCBBB9D5DC1059ED8;
	context->h64[1] = 0x629A292A367CD507;
	context->h64[2] = 0x9159015A3070DD17;
	context->h64[3] = 0x152FECD8F70E5939;
	context->h64[4] = 0x67332667FFC00B31;
	context->h64[5] = 0x8EB44A8768581511;
	context->h64[6] = 0xDB0C2E0D64F98FA7;
	context->h64[7] = 0x47B5481DBEFA4FA4;
	// Number of bytes in the buffer
	context->size = 0;
	// Total length of the message
	context->totalSize = 0;
}

// Update the SHA-384 context with a portion of the message being hashed

void __cdecl f_sha384_update(PHASH_CONTEXT context, const void* data, size_t length) {
	// The function is defined in the exact same manner as SHA-512
	f_sha512_update(context, data, length);
}

// Finish the SHA-384 message digest

void __cdecl f_sha384_final(PHASH_CONTEXT context, unsigned char* digest) {
	// The function is defined in the exact same manner as SHA-512
	f_sha512_final(context, nullptr);
	// Copy the resulting digest
	if (digest)
		f_memcpy(digest, context->digest, SHA384_DIGEST_SIZE);
}

// Finish the SHA-384 message digest (no padding is added)

void __cdecl f_sha384_final_raw(PHASH_CONTEXT context, unsigned char* digest) {
	// Convert from host byte order to big-endian byte order
	context->h64[0] = htobe64(context->h64[0]);
	context->h64[1] = htobe64(context->h64[1]);
	context->h64[2] = htobe64(context->h64[2]);
	context->h64[3] = htobe64(context->h64[3]);
	context->h64[4] = htobe64(context->h64[4]);
	context->h64[5] = htobe64(context->h64[5]);
	context->h64[6] = htobe64(context->h64[6]);
	context->h64[7] = htobe64(context->h64[7]);
	// Copy the resulting digest
	f_memcpy(digest, context->digest, SHA384_DIGEST_SIZE);
	// Convert from big-endian byte order to host byte order
	context->h64[0] = betoh64(context->h64[0]);
	context->h64[1] = betoh64(context->h64[1]);
	context->h64[2] = betoh64(context->h64[2]);
	context->h64[3] = betoh64(context->h64[3]);
	context->h64[4] = betoh64(context->h64[4]);
	context->h64[5] = betoh64(context->h64[5]);
	context->h64[6] = betoh64(context->h64[6]);
	context->h64[7] = betoh64(context->h64[7]);
}

// Digest a message using SHA-384

int __cdecl f_sha384_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha384_init(context);
		f_sha384_update(context, data, length);
		f_sha384_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return TRUE;
}

// Initialize SHA-512/224 message digest context

void __cdecl f_sha512_224_init(PHASH_CONTEXT context) {
	// Set initial hash value
	context->h64[0] = 0x8C3D37C819544DA2;
	context->h64[1] = 0x73E1996689DCD4D6;
	context->h64[2] = 0x1DFAB7AE32FF9C82;
	context->h64[3] = 0x679DD514582F9FCF;
	context->h64[4] = 0x0F6D2B697BD44DA8;
	context->h64[5] = 0x77E36F7304C48942;
	context->h64[6] = 0x3F9D85A86A1D36C8;
	context->h64[7] = 0x1112E6AD91D692A1;
	// Number of bytes in the buffer
	context->size = 0;
	// Total length of the message
	context->totalSize = 0;
}


// Update the SHA-512/224 context with a portion of the message being hashed

void __cdecl f_sha512_224_update(PHASH_CONTEXT context, const void* data, size_t length) {
	// The function is defined in the exact same manner as SHA-512
	f_sha512_update(context, data, length);
}


// Finish the SHA-512/224 message digest

void __cdecl f_sha512_224_final(PHASH_CONTEXT context, unsigned char* digest) {
	// The function is defined in the exact same manner as SHA-512
	f_sha512_final(context, nullptr);
	// Copy the resulting digest
	if (digest)
		f_memcpy(digest, context->digest, SHA512_224_DIGEST_SIZE);
}

// Digest a message using SHA-512/224

int __cdecl f_sha512_224_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha512_224_init(context);
		f_sha512_224_update(context, data, length);
		f_sha512_224_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}


// Initialize SHA-512/256 message digest context

void __cdecl f_sha512_256_init(PHASH_CONTEXT context) {
	// Set initial hash value
	context->h64[0] = 0x22312194FC2BF72C;
	context->h64[1] = 0x9F555FA3C84C64C2;
	context->h64[2] = 0x2393B86B6F53B151;
	context->h64[3] = 0x963877195940EABD;
	context->h64[4] = 0x96283EE2A88EFFE3;
	context->h64[5] = 0xBE5E1E2553863992;
	context->h64[6] = 0x2B0199FC2C85B8AA;
	context->h64[7] = 0x0EB72DDC81C52CA2;
	// Number of bytes in the buffer
	context->size = 0;
	// Total length of the message
	context->totalSize = 0;
}

// Update the SHA-512/256 context with a portion of the message being hashed

void __cdecl f_sha512_256_update(PHASH_CONTEXT context, const void* data, size_t length) {
	// The function is defined in the exact same manner as SHA-512
	f_sha512_update(context, data, length);
}

// Finish the SHA-512/256 message digest

void __cdecl f_sha512_256_final(PHASH_CONTEXT context, unsigned char* digest) {
	// The function is defined in the exact same manner as SHA-512
	f_sha512_final(context, nullptr);
	// Copy the resulting digest
	if (digest)
		f_memcpy(digest, context->digest, SHA512_256_DIGEST_SIZE);
}

// Digest a message using SHA-512/256

int __cdecl f_sha512_256_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha512_256_init(context);
		f_sha512_256_update(context, data, length);
		f_sha512_256_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}
