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

#ifndef _FCRT_H
#error You must include 'fcrt.h' only!
#endif // !FCRT_H

#ifndef _FCRT_CRYPTO_H
#define _FCRT_CRYPTO_H

#define MD5_BLOCK_SIZE 64
#define MD5_DIGEST_SIZE 16
#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20
#define SHA224_BLOCK_SIZE 64
#define SHA224_DIGEST_SIZE 28
#define SHA256_BLOCK_SIZE 64
#define SHA256_DIGEST_SIZE 32
#define SHA384_BLOCK_SIZE 128
#define SHA384_DIGEST_SIZE 48
#define SHA512_BLOCK_SIZE 128
#define SHA512_DIGEST_SIZE 64
#define SHA3_224_BLOCK_SIZE 144
#define SHA3_224_DIGEST_SIZE 28
#define SHA3_256_BLOCK_SIZE 136
#define SHA3_256_DIGEST_SIZE 32
#define SHA3_384_BLOCK_SIZE 104
#define SHA3_384_DIGEST_SIZE 48
#define SHA3_512_BLOCK_SIZE 72
#define SHA3_512_DIGEST_SIZE 64
#define SHA512_224_BLOCK_SIZE 128
#define SHA512_224_DIGEST_SIZE 28
#define SHA512_256_BLOCK_SIZE 128
#define SHA512_256_DIGEST_SIZE 32

// The binary logarithm of the lane size
#ifndef KECCAK_L
#define KECCAK_L 6
#endif

//Check lane size
#if (KECCAK_L == 3)
	typedef unsigned char keccak_lane_t;
	#define KECCAK_ROL(a, n) ROL8(a, n)
	#define KECCAK_HTOLE(a) (a)
	#define KECCAK_LETOH(a) (a)
#elif (KECCAK_L == 4)
	typedef unsigned short keccak_lane_t;
	#define KECCAK_ROL(a, n) ROL16(a, n)
	#define KECCAK_HTOLE(a) htole16(a)
	#define KECCAK_LETOH(a) letoh16(a)
#elif (KECCAK_L == 5)
	typedef unsigned long keccak_lane_t;
	#define KECCAK_ROL(a, n) ROL32(a, n)
	#define KECCAK_HTOLE(a) htole32(a)
	#define KECCAK_LETOH(a) letoh32(a)
#elif (KECCAK_L == 6)
	typedef unsigned long long keccak_lane_t;
	#define KECCAK_ROL(a, n) ROL64(a, n)
	#define KECCAK_HTOLE(a) htole64(a)
	#define KECCAK_LETOH(a) letoh64(a)
#else
	#error KECCAK_L parameter is not valid!
#endif

#define KECCAK_W (1 << KECCAK_L)
#define KECCAK_B (KECCAK_W * 25)
#define KECCAK_NR (12 + 2 * KECCAK_L)
#define KECCAK_PAD 0x01
#define KECCAK_SHA3_PAD 0x06
#define KECCAK_XOF_PAD 0x1F

#pragma pack(push, _CRT_PACKING)

typedef struct _HASH_CONTEXT {
    union {
        unsigned long h32[8];
        unsigned long long h64[8];
        unsigned char digest[32];
        keccak_lane_t a[5][5];
    };
    union {
        unsigned long w32[16];
        unsigned long long w64[16];
        unsigned char buffer[128];
        keccak_lane_t block[24];
    };
    union {
        size_t size;
        size_t length;
    };
    union {
        unsigned long long totalSize;
        unsigned long blockSize;
    };
} HASH_CONTEXT, * PHASH_CONTEXT;

#pragma pack(pop)

// ---------------------------------------------------------------------------
// crc32.c
// ---------------------------------------------------------------------------
FCRT unsigned long __cdecl f_crc32(unsigned long crc, unsigned char *buffer, size_t len);

#ifndef _FCRT_NO_ALIAS
#define crc32 f_crc32
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// md5.c
// ---------------------------------------------------------------------------
FCRT void __cdecl f_md5_init(PHASH_CONTEXT context);
FCRT void __cdecl f_md5_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_md5_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT void __cdecl f_md5_final_raw(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_md5_sum(const void* data, size_t length, unsigned char* digest);

#ifndef _FCRT_NO_ALIAS
#define md5_init f_md5_init
#define md5_update f_md5_update
#define md5_final f_md5_final
#define md5_final_raw f_md5_final_raw
#define md5_sum f_md5_sum
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// sha1.c
// ---------------------------------------------------------------------------
FCRT void __cdecl f_sha1_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha1_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha1_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT void __cdecl f_sha1_final_raw(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha1_sum(const void* data, size_t length, unsigned char* digest);

#ifndef _FCRT_NO_ALIAS
#define sha1_init f_sha1_init
#define sha1_update f_sha1_update
#define sha1_final f_sha1_final
#define sha1_final_raw f_sha1_final_raw
#define sha1_sum f_sha1_sum
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// sha1.c
// ---------------------------------------------------------------------------
FCRT void __cdecl f_sha224_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha224_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha224_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT void __cdecl f_sha224_final_raw(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha224_sum(const void* data, size_t length, unsigned char* digest);
FCRT void __cdecl f_sha256_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha256_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha256_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT void __cdecl f_sha256_final_raw(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha256_sum(const void* data, size_t length, unsigned char* digest);
FCRT void __cdecl f_sha384_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha384_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha384_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT void __cdecl f_sha384_final_raw(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha384_sum(const void* data, size_t length, unsigned char* digest);
FCRT void __cdecl f_sha512_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha512_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha512_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha512_sum(const void* data, size_t length, unsigned char* digest);
FCRT void __cdecl f_sha512_224_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha512_224_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha512_224_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha512_224_sum(const void* data, size_t length, unsigned char* digest);
FCRT void __cdecl f_sha512_256_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha512_256_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha512_256_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha512_256_sum(const void* data, size_t length, unsigned char* digest);

#ifndef _FCRT_NO_ALIAS
#define sha224_init f_sha224_init
#define sha224_update f_sha224_update
#define sha224_final f_sha224_final
#define sha224_final_raw f_sha224_final_raw
#define sha224_sum f_sha224_sum
#define sha256_init f_sha256_init
#define sha256_update f_sha256_update
#define sha256_final f_sha256_final
#define sha256_final_raw f_sha256_final_raw
#define sha256_sum f_sha256_sum
#define sha384_init f_sha384_init
#define sha384_update f_sha384_update
#define sha384_final f_sha384_final
#define sha384_final_raw f_sha384_final_raw
#define sha384_sum f_sha384_sum
#define sha512_init f_sha512_init
#define sha512_update f_sha512_update
#define sha512_final f_sha512_final
#define sha512_final_raw f_sha512_final_raw
#define sha512_sum f_sha512_sum
#define sha512_224_init f_sha512_224_init
#define sha512_224_update f_sha512_224_update
#define sha512_224_final f_sha512_224_final
#define sha512_224_final_raw f_sha512_224_final_raw
#define sha512_224_sum f_sha512_224_sum
#define sha512_256_init f_sha512_256_init
#define sha512_256_update f_sha512_256_update
#define sha512_256_final f_sha512_256_final
#define sha512_256_final_raw f_sha512_256_final_raw
#define sha512_256_sum f_sha512_256_sum
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// sha3.c
// ---------------------------------------------------------------------------
FCRT void __cdecl f_sha3_224_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha3_224_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha3_224_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha3_224_sum(const void* data, size_t length, unsigned char* digest);
FCRT void __cdecl f_sha3_256_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha3_256_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha3_256_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha3_256_sum(const void* data, size_t length, unsigned char* digest);
FCRT void __cdecl f_sha3_384_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha3_384_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha3_384_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha3_384_sum(const void* data, size_t length, unsigned char* digest);
FCRT void __cdecl f_sha3_512_init(PHASH_CONTEXT context);
FCRT void __cdecl f_sha3_512_update(PHASH_CONTEXT context, const void* data, size_t length);
FCRT void __cdecl f_sha3_512_final(PHASH_CONTEXT context, unsigned char* digest);
FCRT int __cdecl f_sha3_512_sum(const void* data, size_t length, unsigned char* digest);

#ifndef _FCRT_NO_ALIAS
#define sha3_224_init f_sha3_224_init
#define sha3_224_update f_sha3_224_update
#define sha3_224_final f_sha3_224_final
#define sha3_224_sum f_sha3_224_sum
#define sha3_256_init f_sha3_256_init
#define sha3_256_update f_sha3_256_update
#define sha3_256_final f_sha3_256_final
#define sha3_256_sum f_sha3_256_sum
#define sha3_384_init f_sha3_384_init
#define sha3_384_update f_sha3_384_update
#define sha3_384_final f_sha3_384_final
#define sha3_384_sum f_sha3_384_sum
#define sha3_512_init f_sha3_512_init
#define sha3_512_update f_sha3_512_update
#define sha3_512_final f_sha3_512_final
#define sha3_512_sum f_sha3_512_sum
#define sha3_224_init f_sha3_224_init
#define sha3_224_update f_sha3_224_update
#define sha3_224_final f_sha3_224_final
#define sha3_224_sum f_sha3_224_sum
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// keccak.c
// ---------------------------------------------------------------------------
FCRT int __cdecl f_keccak_init(PHASH_CONTEXT context, unsigned long capacity);
FCRT void __cdecl f_keccak_absorb(PHASH_CONTEXT context, const void* input, size_t length);
FCRT void __cdecl f_keccak_final(PHASH_CONTEXT context, unsigned char pad);
FCRT void __cdecl f_keccak_squeeze(PHASH_CONTEXT context, unsigned char* output, size_t length);

#ifndef _FCRT_NO_ALIAS
#define keccak_init f_keccak_init
#define keccak_absorb f_keccak_absorb
#define keccak_final f_keccak_final
#define keccak_squeeze f_keccak_squeeze
#endif // !_FCRT_NO_ALIAS

#endif // !_FCRT_CRYPTO_H
