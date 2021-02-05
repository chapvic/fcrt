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

#ifndef _FCRT_ENDIAN_H
#define _FCRT_ENDIAN_H

#if !defined BIGENDIAN && !defined LITTLEENDIAN

#define BYTE_ORDER_LITTLE_ENDIAN 0x41424344UL 
#define BYTE_ORDER_BIG_ENDIAN    0x44434241UL
#define BYTE_ORDER_PDP_ENDIAN    0x42414443UL
#define BYTE_ORDER               ('ABCD')

#if BYTE_ORDER==BYTE_ORDER_LITTLE_ENDIAN
#define LITTLE_ENDIAN 1
#define BIG_ENDIAN 0
#define PDP_ENDIAN 0
#elif BYTE_ORDER==BYTE_ORDER_BIG_ENDIAN
#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1
#define PDP_ENDIAN 0
#elif BYTE_ORDER==BYTE_ORDER_PDP_ENDIAN
#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 0
#define PDP_ENDIAN 1
#endif
#else // defined BIGENDIAN && !defined LITTLEENDIAN
#define BIG_ENDIAN BIGENDIAN
#define LITTLE_ENDIAN LITTLEENDIAN
#endif // !defined BIGENDIAN && !defined LITTLEENDIAN

//Load unaligned 16-bit integer (little-endian encoding)
#define LOAD16LE(p) ( \
    ((unsigned short)(((unsigned char *)(p))[0]) << 0) | \
    ((unsigned short)(((unsigned char *)(p))[1]) << 8))

 //Load unaligned 16-bit integer (big-endian encoding)
#define LOAD16BE(p) ( \
    ((unsigned short)(((unsigned char *)(p))[0]) << 8) | \
    ((unsigned short)(((unsigned char *)(p))[1]) << 0))

 //Load unaligned 24-bit integer (little-endian encoding)
#define LOAD24LE(p) ( \
    ((unsigned long)(((unsigned char *)(p))[0]) << 0)| \
    ((unsigned long)(((unsigned char *)(p))[1]) << 8) | \
    ((unsigned long)(((unsigned char *)(p))[2]) << 16))

 //Load unaligned 24-bit integer (big-endian encoding)
#define LOAD24BE(p) ( \
    ((unsigned long)(((unsigned char *)(p))[0]) << 16) | \
    ((unsigned long)(((unsigned char *)(p))[1]) << 8) | \
    ((unsigned long)(((unsigned char *)(p))[2]) << 0))

 //Load unaligned 32-bit integer (little-endian encoding)
#define LOAD32LE(p) ( \
    ((unsigned long)(((unsigned char *)(p))[0]) << 0) | \
    ((unsigned long)(((unsigned char *)(p))[1]) << 8) | \
    ((unsigned long)(((unsigned char *)(p))[2]) << 16) | \
    ((unsigned long)(((unsigned char *)(p))[3]) << 24))

 //Load unaligned 32-bit integer (big-endian encoding)
#define LOAD32BE(p) ( \
    ((unsigned long)(((unsigned char *)(p))[0]) << 24) | \
    ((unsigned long)(((unsigned char *)(p))[1]) << 16) | \
    ((unsigned long)(((unsigned char *)(p))[2]) << 8) | \
    ((unsigned long)(((unsigned char *)(p))[3]) << 0))

 //Load unaligned 48-bit integer (little-endian encoding)
#define LOAD48LE(p) ( \
    ((unsigned long long)(((unsigned char *)(p))[0]) << 0) | \
    ((unsigned long long)(((unsigned char *)(p))[1]) << 8) | \
    ((unsigned long long)(((unsigned char *)(p))[2]) << 16) | \
    ((unsigned long long)(((unsigned char *)(p))[3]) << 24) | \
    ((unsigned long long)(((unsigned char *)(p))[4]) << 32) | \
    ((unsigned long long)(((unsigned char *)(p))[5]) << 40)

 //Load unaligned 48-bit integer (big-endian encoding)
#define LOAD48BE(p) ( \
    ((unsigned long long)(((unsigned char *)(p))[0]) << 40) | \
    ((unsigned long long)(((unsigned char *)(p))[1]) << 32) | \
    ((unsigned long long)(((unsigned char *)(p))[2]) << 24) | \
    ((unsigned long long)(((unsigned char *)(p))[3]) << 16) | \
    ((unsigned long long)(((unsigned char *)(p))[4]) << 8) | \
    ((unsigned long long)(((unsigned char *)(p))[5]) << 0))

 //Load unaligned 64-bit integer (little-endian encoding)
#define LOAD64LE(p) ( \
    ((unsigned long long)(((unsigned char *)(p))[0]) << 0) | \
    ((unsigned long long)(((unsigned char *)(p))[1]) << 8) | \
    ((unsigned long long)(((unsigned char *)(p))[2]) << 16) | \
    ((unsigned long long)(((unsigned char *)(p))[3]) << 24) | \
    ((unsigned long long)(((unsigned char *)(p))[4]) << 32) | \
    ((unsigned long long)(((unsigned char *)(p))[5]) << 40) | \
    ((unsigned long long)(((unsigned char *)(p))[6]) << 48) | \
    ((unsigned long long)(((unsigned char *)(p))[7]) << 56))

 //Load unaligned 64-bit integer (big-endian encoding)
#define LOAD64BE(p) ( \
    ((unsigned long long)(((unsigned char *)(p))[0]) << 56) | \
    ((unsigned long long)(((unsigned char *)(p))[1]) << 48) | \
    ((unsigned long long)(((unsigned char *)(p))[2]) << 40) | \
    ((unsigned long long)(((unsigned char *)(p))[3]) << 32) | \
    ((unsigned long long)(((unsigned char *)(p))[4]) << 24) | \
    ((unsigned long long)(((unsigned char *)(p))[5]) << 16) | \
    ((unsigned long long)(((unsigned char *)(p))[6]) << 8) | \
    ((unsigned long long)(((unsigned char *)(p))[7]) << 0))

 //Store unaligned 16-bit integer (little-endian encoding)
#define STORE16LE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned short)(a) >> 0) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned short)(a) >> 8) & 0xFFU

 //Store unaligned 32-bit integer (big-endian encoding)
#define STORE16BE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned short)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned short)(a) >> 0) & 0xFFU

 //Store unaligned 24-bit integer (little-endian encoding)
#define STORE24LE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned long)(a) >> 0) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned long)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[2] = ((unsigned long)(a) >> 16) & 0xFFU

 //Store unaligned 24-bit integer (big-endian encoding)
#define STORE24BE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned long)(a) >> 16) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned long)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[2] = ((unsigned long)(a) >> 0) & 0xFFU

 //Store unaligned 32-bit integer (little-endian encoding)
#define STORE32LE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned long)(a) >> 0) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned long)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[2] = ((unsigned long)(a) >> 16) & 0xFFU, \
    ((unsigned char *)(p))[3] = ((unsigned long)(a) >> 24) & 0xFFU

 //Store unaligned 32-bit integer (big-endian encoding)
#define STORE32BE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned long)(a) >> 24) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned long)(a) >> 16) & 0xFFU, \
    ((unsigned char *)(p))[2] = ((unsigned long)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[3] = ((unsigned long)(a) >> 0) & 0xFFU

 //Store unaligned 48-bit integer (little-endian encoding)
#define STORE48LE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned long long)(a) >> 0) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned long long)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[2] = ((unsigned long long)(a) >> 16) & 0xFFU, \
    ((unsigned char *)(p))[3] = ((unsigned long long)(a) >> 24) & 0xFFU, \
    ((unsigned char *)(p))[4] = ((unsigned long long)(a) >> 32) & 0xFFU, \
    ((unsigned char *)(p))[5] = ((unsigned long long)(a) >> 40) & 0xFFU,

 //Store unaligned 48-bit integer (big-endian encoding)
#define STORE48BE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned long long)(a) >> 40) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned long long)(a) >> 32) & 0xFFU, \
    ((unsigned char *)(p))[2] = ((unsigned long long)(a) >> 24) & 0xFFU, \
    ((unsigned char *)(p))[3] = ((unsigned long long)(a) >> 16) & 0xFFU, \
    ((unsigned char *)(p))[4] = ((unsigned long long)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[5] = ((unsigned long long)(a) >> 0) & 0xFFU

 //Store unaligned 64-bit integer (little-endian encoding)
#define STORE64LE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned long long)(a) >> 0) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned long long)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[2] = ((unsigned long long)(a) >> 16) & 0xFFU, \
    ((unsigned char *)(p))[3] = ((unsigned long long)(a) >> 24) & 0xFFU, \
    ((unsigned char *)(p))[4] = ((unsigned long long)(a) >> 32) & 0xFFU, \
    ((unsigned char *)(p))[5] = ((unsigned long long)(a) >> 40) & 0xFFU, \
    ((unsigned char *)(p))[6] = ((unsigned long long)(a) >> 48) & 0xFFU, \
    ((unsigned char *)(p))[7] = ((unsigned long long)(a) >> 56) & 0xFFU

 //Store unaligned 64-bit integer (big-endian encoding)
#define STORE64BE(a, p) \
    ((unsigned char *)(p))[0] = ((unsigned long long)(a) >> 56) & 0xFFU, \
    ((unsigned char *)(p))[1] = ((unsigned long long)(a) >> 48) & 0xFFU, \
    ((unsigned char *)(p))[2] = ((unsigned long long)(a) >> 40) & 0xFFU, \
    ((unsigned char *)(p))[3] = ((unsigned long long)(a) >> 32) & 0xFFU, \
    ((unsigned char *)(p))[4] = ((unsigned long long)(a) >> 24) & 0xFFU, \
    ((unsigned char *)(p))[5] = ((unsigned long long)(a) >> 16) & 0xFFU, \
    ((unsigned char *)(p))[6] = ((unsigned long long)(a) >> 8) & 0xFFU, \
    ((unsigned char *)(p))[7] = ((unsigned long long)(a) >> 0) & 0xFFU

 //Swap a 16-bit integer
#define SWAPINT16(x) ( \
    (((unsigned short)(x) & 0x00FFU) << 8) | \
    (((unsigned short)(x) & 0xFF00U) >> 8))

 //Swap a 32-bit integer
#define SWAPINT32(x) ( \
    (((unsigned long)(x) & 0x000000FFUL) << 24) | \
    (((unsigned long)(x) & 0x0000FF00UL) << 8) | \
    (((unsigned long)(x) & 0x00FF0000UL) >> 8) | \
    (((unsigned long)(x) & 0xFF000000UL) >> 24))

 //Swap a 64-bit integer
#define SWAPINT64(x) ( \
    (((unsigned long long)(x) & 0x00000000000000FFULL) << 56) | \
    (((unsigned long long)(x) & 0x000000000000FF00ULL) << 40) | \
    (((unsigned long long)(x) & 0x0000000000FF0000ULL) << 24) | \
    (((unsigned long long)(x) & 0x00000000FF000000ULL) << 8) | \
    (((unsigned long long)(x) & 0x000000FF00000000ULL) >> 8) | \
    (((unsigned long long)(x) & 0x0000FF0000000000ULL) >> 24) | \
    (((unsigned long long)(x) & 0x00FF000000000000ULL) >> 40) | \
    (((unsigned long long)(x) & 0xFF00000000000000ULL) >> 56))

//Big-endian machine?
#if BIG_ENDIAN

//Host byte order to network byte order
#define HTONS(value) (value)
#define HTONL(value) (value)
#define htons(value) ((unsigned short) (value))
#define htonl(value) ((unsigned long) (value))

//Network byte order to host byte order
#define NTOHS(value) (value)
#define NTOHL(value) (value)
#define ntohs(value) ((unsigned short) (value))
#define ntohl(value) ((unsigned long) (value))

//Host byte order to little-endian byte order
#define HTOLE16(value) SWAPINT16(value)
#define HTOLE32(value) SWAPINT32(value)
#define HTOLE64(value) SWAPINT64(value)
#define htole16(value) f_swap_int16((unsigned short) (value))
#define htole32(value) f_swap_int32((unsigned long) (value))
#define htole64(value) f_swap_int64((unsigned long long) (value))

//Little-endian byte order to host byte order
#define LETOH16(value) SWAPINT16(value)
#define LETOH32(value) SWAPINT32(value)
#define LETOH64(value) SWAPINT64(value)
#define letoh16(value) f_swap_int16((unsigned short) (value))
#define letoh32(value) f_swap_int32((unsigned long) (value))
#define letoh64(value) f_swap_int64((unsigned long long) (value))

//Host byte order to big-endian byte order
#define HTOBE16(value) (value)
#define HTOBE32(value) (value)
#define HTOBE64(value) (value)
#define htobe16(value) ((unsigned short) (value))
#define htobe32(value) ((unsigned long) (value))
#define htobe64(value) ((unsigned long long) (value))

//Big-endian byte order to host byte order
#define BETOH16(value) (value)
#define BETOH32(value) (value)
#define BETOH64(value) (value)
#define betoh16(value) ((unsigned short) (value))
#define betoh32(value) ((unsigned long) (value))
#define betoh64(value) ((unsigned long long) (value))

//Little-endian machine?
#else

//Host byte order to network byte order
#define HTONS(value) SWAPINT16(value)
#define HTONL(value) SWAPINT32(value)
#define htons(value) f_swap_int16((unsigned short) (value))
#define htonl(value) f_swap_int32((unsigned long) (value))

//Network byte order to host byte order
#define NTOHS(value) SWAPINT16(value)
#define NTOHL(value) SWAPINT32(value)
#define ntohs(value) f_swap_int16((unsigned short) (value))
#define ntohl(value) f_swap_int32((unsigned long) (value))

//Host byte order to little-endian byte order
#define HTOLE16(value) (value)
#define HTOLE32(value) (value)
#define HTOLE64(value) (value)
#define htole16(value) ((unsigned short) (value))
#define htole32(value) ((unsigned long) (value))
#define htole64(value) ((unsigned long long) (value))

//Little-endian byte order to host byte order
#define LETOH16(value) (value)
#define LETOH32(value) (value)
#define LETOH64(value) (value)
#define letoh16(value) ((unsigned short) (value))
#define letoh32(value) ((unsigned long) (value))
#define letoh64(value) ((unsigned long long) (value))

//Host byte order to big-endian byte order
#define HTOBE16(value) SWAPINT16(value)
#define HTOBE32(value) SWAPINT32(value)
#define HTOBE64(value) SWAPINT64(value)
#define htobe16(value) f_swap_int16((unsigned short) (value))
#define htobe32(value) f_swap_int32((unsigned long) (value))
#define htobe64(value) f_swap_int64((unsigned long long) (value))

//Big-endian byte order to host byte order
#define BETOH16(value) SWAPINT16(value)
#define BETOH32(value) SWAPINT32(value)
#define BETOH64(value) SWAPINT64(value)
#define betoh16(value) f_swap_int16((unsigned short) (value))
#define betoh32(value) f_swap_int32((unsigned long) (value))
#define betoh64(value) f_swap_int64((unsigned long long) (value))

#endif // BIG_ENDIAN

// Is little endian byte order
FCRT int __cdecl f_le();
// Is big endian byte order
FCRT int __cdecl f_be();
FCRT unsigned short __cdecl f_swap_int16(unsigned short value);
FCRT unsigned long __cdecl f_swap_int32(unsigned long value);
FCRT unsigned long long __cdecl f_swap_int64(unsigned long long value);
FCRT unsigned char __cdecl f_reverse_int4(unsigned char value);
FCRT unsigned char __cdecl f_reverse_int8(unsigned char value);
FCRT unsigned short __cdecl f_reverse_int16(unsigned short value);
FCRT unsigned long __cdecl f_reverse_int32(unsigned long value);
FCRT unsigned long long __cdecl f_reverse_int64(unsigned long long value);

#ifndef _FCRT_NO_ALIAS
#define le f_le
#define be f_be
#define swap_int16 f_swap_int16
#define swap_int32 f_swap_int32
#define swap_int64 f_swap_int64
#define reverse_int4 f_reverse_int4
#define reverse_int8 f_reverse_int8
#define reverse_int16 f_reverse_int16
#define reverse_int32 f_reverse_int32
#define reverse_int64 f_reverse_int64
#endif // !_FCRT_NO_ALIAS

#endif // !_FCRT_ENDIAN_H
