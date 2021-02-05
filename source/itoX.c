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

#ifdef _FCRT_UNICODE
#define f_itoX f_itow
#define f_utoX f_utow
#define f_ltoX f_ltow
#define f_ultoX f_ultow
#define f_lltoX f_lltow
#define f_ulltoX f_ulltow
#else
#define f_itoX f_itoa
#define f_utoX f_utoa
#define f_ltoX f_ltoa
#define f_ultoX f_ultoa
#define f_lltoX f_lltoa
#define f_ulltoX f_ulltoa
#endif

#if !defined _FCRT_VARTYPE
#error _FCRT_VARTYPE must be defined!
#endif

#if _FCRT_VARTYPE==1			// signed int (INT32)
#define _fcrt_function_name f_itoX
#define _fcrt_type int
#elif _FCRT_VARTYPE==2			// unsigned int (UINT32)
#define _fcrt_function_name f_utoX
#define _fcrt_type unsigned int
#elif _FCRT_VARTYPE==3			// signed long (INT64)
#define _fcrt_function_name f_ltoX
#define _fcrt_type long
#elif _FCRT_VARTYPE==4			// unsigned long (UINT64)
#define _fcrt_function_name f_ultoX
#define _fcrt_type unsigned long
#elif _FCRT_VARTYPE==5			// signed long long (INT64)
#define _fcrt_function_name f_lltoX
#define _fcrt_type long long
#elif _FCRT_VARTYPE==6			// unsigned long long (UINT64)
#define _fcrt_function_name f_ulltoX
#define _fcrt_type unsigned long long
#else
#error Invalid _FCRT_VARTYPE value!
#endif

_tchar * __cdecl _fcrt_function_name(_fcrt_type num, int radix, int ucase) {
	_tchar buffer[32];	// buffer size is hardcoded
	int neg = (num < 0);
	size_t len = 1 + neg;
	if (radix < 2 || radix > 36) radix = 10;
	if (radix != 10) {
#if _FCRT_VARTYPE==1
		return f_utoX(num, radix, ucase);
#elif _FCRT_VARTYPE==3
		return f_ultoX(num, radix, ucase);
#elif _FCRT_VARTYPE==5
		return f_ulltoX(num, radix, ucase);
#endif
	}
	_tmemset(buffer, 0, 32);
	int pos = 31;
	while(num != 0){
		_tchar c = (_tchar)(num % radix);
		if (neg) c = -c;
		buffer[--pos] = c + ((radix > 10) ? (c < 10 ? 48 : (ucase ? 55 : 87)) : 48);
		num /= radix;
		len++;
	}
	if(neg && radix==10) buffer[--pos] = '-';
	_tchar *retval = _tmalloc(len);
	return (retval) ? _tmemcpy(retval, &buffer[pos], len) : 0;
}

#undef _fcrt_function_name
#undef _fcrt_type
#undef f_itoX
#undef f_utoX
#undef f_ltoX
#undef f_ultoX
#undef f_lltoX
#undef f_ulltoX
