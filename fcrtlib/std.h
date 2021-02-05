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

#ifndef _FCRT_STD_H
#define _FCRT_STD_H

#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE
#endif
#endif // UNICODE

#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE
#endif
#endif // _UNICODE

#if defined(UNICODE) && defined(_MBCS)
#undef _MBCS
#endif // defined(UNICODE) && defined(_MBCS)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <io.h>
#include <errno.h>
#include <tchar.h>
#include <strsafe.h>

#ifndef __cplusplus
#ifndef nullptr
#define nullptr (void*)0
#endif // !nullptr
#endif __cplusplus

#ifndef lowercase
#define lowercase(x) (((x)<'A'||(x)>'Z') ? (x) : ((x)+32))
#endif // !lowercase

#ifndef uppercase
#define uppercase(x) (((x)<'a'||(x)>'z') ? (x) : ((x)-32))
#endif // !uppercase

#ifndef bitcheck
#define bitcheck(var,val) (((var)&(val))==(val))
#endif // !bitcheck

#define REGKEY_MAXLEN 256
#define REGVAL_MAXLEN 16384

#define HKLM 1
#define HKCU 2

#define ROL8(a, n) (((a) << (n)) | ((a) >> (8 - (n))))
#define ROL16(a, n) (((a) << (n)) | ((a) >> (16 - (n))))
#define ROL32(a, n) (((a) << (n)) | ((a) >> (32 - (n))))
#define ROL64(a, n) (((a) << (n)) | ((a) >> (64 - (n))))

#define ROR8(a, n) (((a) >> (n)) | ((a) << (8 - (n))))
#define ROR16(a, n) (((a) >> (n)) | ((a) << (16 - (n))))
#define ROR32(a, n) (((a) >> (n)) | ((a) << (32 - (n))))
#define ROR64(a, n) (((a) >> (n)) | ((a) << (64 - (n))))

#define SHL(a, n) ((a) << (n))
#define SHR(a, n) ((a) >> (n))

#define LSB(x) ((x) & 0xFF)
#define MSB(x) (((x) >> 8) & 0xFF)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// ---------------------------------------------------------------------------
// alloc.c
// ---------------------------------------------------------------------------
FCRT void * __cdecl f_malloc(size_t _size);
FCRT void * __cdecl f_wmalloc(size_t _size);
FCRT void * __cdecl f_realloc(void * _ptr, size_t _newsize);
FCRT void * __cdecl f_wrealloc(void * _ptr, size_t _newsize);
FCRT void * __cdecl f_calloc(size_t _number, size_t _size);
FCRT void * __cdecl f_recalloc(void * _ptr, size_t _number, size_t _size);
FCRT size_t __cdecl f_memsize(void * _ptr);
FCRT void __cdecl f_free(void * _ptr);
FCRT void __cdecl f_freez(void ** _ptr);

#ifndef _FCRT_NO_ALIAS
#define malloc f_malloc
#define wmalloc f_wmalloc
#define realloc f_realloc
#define wrealloc f_wrealloc
#define calloc f_calloc
#define recalloc f_recalloc
#define memsize f_memsize
#define free f_free
#define freez f_freez
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// memctl.c
// ---------------------------------------------------------------------------
FCRT int __cdecl f_memcmp(const void * _ptr1, const void * _ptr2, size_t _count);
FCRT int __cdecl f_wmemcmp(const wchar_t * _ptr1, const wchar_t * _ptr2, size_t _count);
FCRT void * __cdecl f_memcpy(void * _dst, const void * _src, size_t _count);
FCRT void * __cdecl f_wmemcpy(void * _dst, const void * _src, size_t _count);
FCRT void * __cdecl f_memset(void * _dst, int _c, size_t _count);
FCRT void * __cdecl f_wmemset(wchar_t * _dst, wchar_t _c, size_t _count);

#ifndef _FCRT_NO_ALIAS
#define memcmp f_memcmp
#define wmemcmp f_wmemcmp
#define memcpy f_memcpy
#define wmemcpy f_wmemcpy
#define memset f_memset
#define wmemset f_wmemset
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// memhlp.c
// ---------------------------------------------------------------------------
FCRT void * __cdecl f_bzero(void * _ptr, size_t _count);
FCRT void * __cdecl f_wzero(void * _ptr, size_t _count);
FCRT void * __cdecl f_bcopy(void * _src, size_t _origin, size_t _len);
FCRT void * __cdecl f_wcopy(void * _src, size_t _origin, size_t _len);

#ifndef _FCRT_NO_ALIAS
#define bzero f_bzero
#define wzero f_wzero
#define bcopy f_bcopy
#define wcopy f_wcopy
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// binhex.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_bin2hex(void *_ptr, size_t _size, int _ucase, int _sparse);

#ifndef _FCRT_NO_ALIAS
#define bin2hex f_bin2hex
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// strlen.c
// ---------------------------------------------------------------------------
FCRT size_t __cdecl f_strlen(const char * _string);
FCRT size_t __cdecl f_wcslen(const wchar_t * _string);

#ifndef _FCRT_NO_ALIAS
#define strlen f_strlen
#define wcslen f_wcslen
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// strdup.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_strdup(const char * _string);
FCRT wchar_t * __cdecl f_wcsdup(const wchar_t * _string);

#ifndef _FCRT_NO_ALIAS
#define strdup f_strdup
#define wcsdup f_wcsdup
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// str_replace.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_str_replace(char * _search, char * _replace, char * _str);
FCRT wchar_t * __cdecl f_wcs_replace(wchar_t * _search, wchar_t * _replace, wchar_t * _str);
FCRT char * __cdecl f_stri_replace(char * _search, char * _replace, char * _str);
FCRT wchar_t * __cdecl f_wcsi_replace(wchar_t * _search, wchar_t * _replace, wchar_t * _str);

#ifndef _FCRT_NO_ALIAS
#define str_replace f_str_replace
#define wcs_replace f_wcs_replace
#define stri_replace f_stri_replace
#define wcsi_replace f_wcsi_replace
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// strcats.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_strcats(char * _buffer, char * _src, char * _separator);
FCRT wchar_t * __cdecl f_wcscats(wchar_t * _buffer, wchar_t * _src, wchar_t * _separator);
FCRT char * __cdecl f_strcats_n(char * _str1, char * _str2, char * _separator);
FCRT wchar_t * __cdecl f_wcscats_n(wchar_t * _str1, wchar_t * _str2, wchar_t * _separator);

#ifndef _FCRT_NO_ALIAS
#define strcats f_strcats
#define wcscats f_wcscats
#define strcats_n f_strcats_n
#define wcscats_n f_wcscats_n
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// stristr.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_stristr(const char * _str, const char * _substr);
FCRT wchar_t * __cdecl f_wcsistr(const wchar_t * _str, const wchar_t * _substr);

#ifndef _FCRT_NO_ALIAS
#define stristr f_stristr
#define wcsistr f_wcsistr
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// substr.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_substr(const char * _str, int _origin, int _len);
FCRT wchar_t * __cdecl f_subwcs(const wchar_t * _str, int _origin, int _len);

#ifndef _FCRT_NO_ALIAS
#define substr f_substr
#define subwcs f_subwcs
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
//indexof.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_indexof(const char * _str, int _ch);
FCRT wchar_t * __cdecl f_windexof(const wchar_t * _str, int _ch);
FCRT char * __cdecl f_indexof_r(const char * _str, int _ch);
FCRT wchar_t * __cdecl f_windexof_r(const wchar_t * _str, int _ch);

#ifndef _FCRT_NO_ALIAS
#define indexof f_indexof
#define windexof f_windexof
#define indexof_r f_indexof_r
#define windexof_r f_windexof_r
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// strconv.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_str2oem(const char * _str);
FCRT char * __cdecl f_wcs2oem(const wchar_t * _str);
FCRT char * __cdecl f_oem2str(const char * _str);
FCRT wchar_t * __cdecl f_oem2wcs(const char * _str);
FCRT wchar_t * __cdecl f_str2wcs(const char * _str);
FCRT size_t __cdecl f_cstr2wcs(wchar_t * _dst, char * _src, size_t _len);
FCRT char * __cdecl f_wcs2str(const wchar_t * _str);
FCRT size_t __cdecl f_cwcs2str(char * _dst, wchar_t * _src, size_t _len);

#ifndef _FCRT_NO_ALIAS
#define str2oem f_str2oem
#define wcs2oem f_wcs2oem
#define oem2str f_oem2str
#define oem2wcs f_oem2wcs
#define str2wcs f_str2wcs
#define cstr2wcs f_cstr2wcs
#define wcs2str f_wcs2str
#define cwcs2str f_cwcs2str
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// vardump.c
// ---------------------------------------------------------------------------
FCRT void __cdecl f_vardump(void * ptr, size_t len, int padding);
FCRT void __cdecl f_fvardump(const char * filename, void * ptr, size_t len, int padding, int force);
FCRT void __cdecl f_vardump_ex(void * ptr, int padding);
FCRT void __cdecl f_fvardump_ex(const char * filename, void * ptr, int padding, int force);

#ifndef _FCRT_NO_ALIAS
#define vardump f_vardump
#define fvardump f_fvardump
#define vardump_ex f_vardump_ex
#define fvardump_ex f_fvardump_ex
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// base64.c
// ---------------------------------------------------------------------------
FCRT int __cdecl f_b64enc(char * _dst, char * _src, size_t _maxlen);
FCRT int __cdecl f_b64encw(wchar_t * _dst, wchar_t * _src, size_t _maxlen);
FCRT int __cdecl f_b64encaw(wchar_t * _dst, char * _src, size_t _maxlen);
FCRT int __cdecl f_b64encwa(char * _dst, wchar_t * _src, size_t _maxlen);
FCRT int __cdecl f_b64dec(char * _dst, char * _src, size_t _maxlen);
FCRT int __cdecl f_b64decw(wchar_t * _dst, wchar_t * _src, size_t _maxlen);
FCRT int __cdecl f_b64decaw(wchar_t * _dst, char * _src, size_t _maxlen);
FCRT int __cdecl f_b64decwa(char * _dst, wchar_t * _src, size_t _maxlen);

#ifndef _FCRT_NO_ALIAS
#define b64enc f_b64enc
#define b64encw f_b64encw
#define b64encaw f_b64encaw
#define b64encwa f_b64encwa
#define b64dec f_b64dec
#define b64decw f_b64decw
#define b64decaw f_b64decaw
#define b64decwa f_b64decwa
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// trim.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_ltrim(char * _str);
FCRT wchar_t * __cdecl f_wltrim(wchar_t * _str);
FCRT char * __cdecl f_rtrim(char * _str);
FCRT wchar_t * __cdecl f_wrtrim(wchar_t * _str);
FCRT char * __cdecl f_trim(char * _str);
FCRT wchar_t * __cdecl f_wtrim(wchar_t * _str);

#ifndef _FCRT_NO_ALIAS
#define ltrim f_ltrim
#define wltrim f_wltrim
#define rtrim f_rtrim
#define wrtrim f_wrtrim
#define trim f_trim
#define wtrim f_wtrim
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// justify.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_jleft(char * _str, size_t _newsize);
FCRT wchar_t * __cdecl f_wjleft(wchar_t * _str, size_t _newsize);
FCRT char * __cdecl f_jright(char * _str, size_t _newsize);
FCRT wchar_t * __cdecl f_wjright(wchar_t * _str, size_t _newsize);
FCRT char * __cdecl f_jcenter(char * _str, size_t _newsize);
FCRT wchar_t * __cdecl f_wjcenter(wchar_t * _str, size_t _newsize);

#ifndef _FCRT_NO_ALIAS
#define jleft f_jleft
#define wjleft f_wjleft
#define jright f_jright
#define wjright f_wjright
#define jcenter f_jcenter
#define wjcenter f_wjcenter
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// dup.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_dup(char _char, size_t _count);
FCRT wchar_t * __cdecl f_wdup(wchar_t _char, size_t _count);

#ifndef _FCRT_NO_ALIAS
#define dup f_dup
#define wdup f_wdup
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// win64.c
// ---------------------------------------------------------------------------
FCRT int __cdecl f_is_app64();
FCRT int __cdecl f_is_wow64();
FCRT int __cdecl f_is_win64();

#ifndef _FCRT_NO_ALIAS
#define is_app64 f_is_app64
#define is_wow64 f_is_wow64
#define is_win64 f_is_win64
#endif // !_FCRT_NO_ALIAS

// ---------------------------------------------------------------------------
// _itoX.c
// ---------------------------------------------------------------------------
FCRT char * __cdecl f_itoa(int num, int radix, int ucase);
FCRT wchar_t * __cdecl f_itow(int num, int radix, int ucase);
FCRT char * __cdecl f_utoa(unsigned int num, int radix, int ucase);
FCRT wchar_t * __cdecl f_utow(unsigned int num, int radix, int ucase);
FCRT char * __cdecl f_ltoa(long num, int radix, int ucase);
FCRT wchar_t * __cdecl f_ltow(long num, int radix, int ucase);
FCRT char * __cdecl f_ultoa(unsigned long num, int radix, int ucase);
FCRT wchar_t * __cdecl f_ultow(unsigned long num, int radix, int ucase);
FCRT char * __cdecl f_lltoa(long long num, int radix, int ucase);
FCRT wchar_t * __cdecl f_lltow(long long num, int radix, int ucase);
FCRT char * __cdecl f_ulltoa(unsigned long long num, int radix, int ucase);
FCRT wchar_t * __cdecl f_ulltow(unsigned long long num, int radix, int ucase);

#ifndef _FCRT_NO_ALIAS
#define itoa f_itoa
#define itow f_itow
#define uitoa f_uitoa
#define uitow f_uitow
#define lltoa f_lltoa
#define lltow f_lltow
#define ulltoa f_ulltoa
#define ulltow f_ulltow
#endif // !_FCRT_NO_ALIAS

#endif // !_FCRT_STD_H
