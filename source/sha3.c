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

// Initialize SHA3-224 message digest context

void __cdecl f_sha3_224_init(PHASH_CONTEXT context) {
	// The capacity of the sponge is twice the digest length
	f_keccak_init(context, 2 * 224);
}

// Update the SHA3-224 context with a portion of the message being hashed

void __cdecl f_sha3_224_update(PHASH_CONTEXT context, const void* data, size_t length) {
	// Absorb the input data
	f_keccak_absorb(context, data, length);
}

// Finish the SHA3-224 message digest

void __cdecl f_sha3_224_final(PHASH_CONTEXT context, unsigned char* digest) {
	// Finish absorbing phase (padding byte is 0x06 for SHA-3)
	f_keccak_final(context, KECCAK_SHA3_PAD);
	// Extract data from the squeezing phase
	f_keccak_squeeze(context, digest, SHA3_224_DIGEST_SIZE);
}

// Digest a message using SHA3-224

int __cdecl f_sha3_224_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha3_224_init(context);
		f_sha3_224_update(context, data, length);
		f_sha3_224_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}

// Initialize SHA3-256 message digest context

void __cdecl f_sha3_256_init(PHASH_CONTEXT context) {
	// The capacity of the sponge is twice the digest length
	f_keccak_init(context, 2 * 256);
}

// Update the SHA3-256 context with a portion of the message being hashed

void __cdecl f_sha3_256_update(PHASH_CONTEXT context, const void* data, size_t length) {
	// Absorb the input data
	f_keccak_absorb(context, data, length);
}

// Finish the SHA3-256 message digest

void __cdecl f_sha3_256_final(PHASH_CONTEXT context, unsigned char* digest) {
	// Finish absorbing phase (padding byte is 0x06 for SHA-3)
	f_keccak_final(context, KECCAK_SHA3_PAD);
	// Extract data from the squeezing phase
	f_keccak_squeeze(context, digest, SHA3_256_DIGEST_SIZE);
}

// Digest a message using SHA3-256

int __cdecl f_sha3_256_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha3_256_init(context);
		f_sha3_256_update(context, data, length);
		f_sha3_256_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}

// Initialize SHA3-384 message digest context

void __cdecl f_sha3_384_init(PHASH_CONTEXT context) {
	// The capacity of the sponge is twice the digest length
	f_keccak_init(context, 2 * 384);
}

// Update the SHA3-384 context with a portion of the message being hashed

void __cdecl f_sha3_384_update(PHASH_CONTEXT context, const void* data, size_t length) {
	// Absorb the input data
	f_keccak_absorb(context, data, length);
}

// Finish the SHA3-384 message digest

void __cdecl f_sha3_384_final(PHASH_CONTEXT context, unsigned char* digest) {
	// Finish absorbing phase (padding byte is 0x06 for SHA-3)
	f_keccak_final(context, KECCAK_SHA3_PAD);
	// Extract data from the squeezing phase
	f_keccak_squeeze(context, digest, SHA3_384_DIGEST_SIZE);
}

// Digest a message using SHA3-384

int __cdecl f_sha3_384_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha3_384_init(context);
		f_sha3_384_update(context, data, length);
		f_sha3_384_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}

// Initialize SHA3-512 message digest context

void __cdecl f_sha3_512_init(PHASH_CONTEXT context) {
	// The capacity of the sponge is twice the digest length
	f_keccak_init(context, 2 * 512);
}

// Update the SHA3-512 context with a portion of the message being hashed

void __cdecl f_sha3_512_update(PHASH_CONTEXT context, const void* data, size_t length) {
	// Absorb the input data
	f_keccak_absorb(context, data, length);
}

// Finish the SHA3-512 message digest

void __cdecl f_sha3_512_final(PHASH_CONTEXT context, unsigned char* digest) {
	// Finish absorbing phase (padding byte is 0x06 for SHA-3)
	f_keccak_final(context, KECCAK_SHA3_PAD);
	// Extract data from the squeezing phase
	f_keccak_squeeze(context, digest, SHA3_512_DIGEST_SIZE);
}

// Digest a message using SHA3-512

int __cdecl f_sha3_512_sum(const void* data, size_t length, unsigned char* digest) {
	int retval = 0;
	PHASH_CONTEXT context = f_malloc(sizeof(HASH_CONTEXT));
	if (context) {
		f_sha3_512_init(context);
		f_sha3_512_update(context, data, length);
		f_sha3_512_final(context, digest);
		f_free(context);
		retval = 1;
	}
	return retval;
}
