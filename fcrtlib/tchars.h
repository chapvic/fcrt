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

#undef _tchar
#undef _tstrlen
#undef _tstrdup
#undef _tstristr
#undef _tstr_replace
#undef _tstri_replace
#undef _tmalloc
#undef _trealloc
#undef _tmemcmp
#undef _tmemcpy
#undef _tmemset
#undef _tzero
#undef _tcopy
#undef _tstrcats
#undef _tstrcats_n
#undef _tsubstr
#undef _tindexof
#undef _tindexof_r
#undef _tbase64encode
#undef _tbase64decode
#undef _tltrim
#undef _trtrim
#undef _ttrim
#undef _tjleft
#undef _tjright
#undef _tjcenter
#undef _tdup

#undef _tregopen
#undef _treginfo

#undef _tprintf
#undef _tstrstr
#undef _tstrncpy
#undef _tstrncat
#undef _tstrchr
#undef _tstrrchr

#if !defined(_FCRT_UNICODE)

#define _tchar char
#define _tstrlen f_strlen
#define _tstrdup f_strdup
#define _tstristr f_stristr
#define _tstr_replace f_str_replace
#define _tstri_replace f_stri_replace
#define _tmalloc f_malloc
#define _trealloc f_realloc
#define _tmemcmp f_memcmp
#define _tmemcpy f_memcpy
#define _tmemset f_memset
#define _tzero f_bzero
#define _tcopy f_bcopy
#define _tstrcats f_strcats
#define _tstrcats_n f_strcats_n
#define _tsubstr f_substr
#define _tindexof f_indexof
#define _tindexof_r f_indexof_r
#define _tbase64encode f_b64enc
#define _tbase64decode f_b64dec
#define _tltrim f_ltrim
#define _trtrim f_rtrim
#define _ttrim f_trim
#define _tjleft f_jleft
#define _tjright f_jright
#define _tjcenter f_jcenter
#define _tdup f_dup

#define _tregopen f_regopen
#define _treginfo f_reginfo

// additional definitions
#define _tprintf printf
#define _tstrstr strstr
#define _tstrncpy strncpy
#define _tstrncat strncat
#define _tstrchr strchr
#define _tstrrchr strrchr

#else // defined(_FCRT_UNICODE)

#define _tchar wchar_t
#define _tstrlen f_wcslen
#define _tstrdup f_wcsdup
#define _tstristr f_wcsistr
#define _tstr_replace f_wcs_replace
#define _tstri_replace f_wcsi_replace
#define _tmalloc f_wmalloc
#define _trealloc f_wrealloc
#define _tmemcmp f_wmemcmp
#define _tmemcpy f_wmemcpy
#define _tmemset f_wmemset
#define _tzero f_wzero
#define _tcopy f_wcopy
#define _tstrcats f_wcscats
#define _tstrcats_n f_wcscats_n
#define _tsubstr f_subwcs
#define _tindexof f_windexof
#define _tindexof_r f_windexof_r
#define _tbase64encode f_b64encw
#define _tbase64decode f_b64decw
#define _tltrim f_wltrim
#define _trtrim f_wrtrim
#define _ttrim f_wtrim
#define _tjleft f_wjleft
#define _tjright f_wjright
#define _tjcenter f_wjcenter
#define _tdup f_wdup

#define _tregopen f_regwopen
#define _treginfo f_regwinfo

// additional definitions
#define _tprintf wprintf
#define _tstrstr wcsstr
#define _tstrncpy wcsncpy
#define _tstrncat wcsncat
#define _tstrchr wcschr
#define _tstrrchr wcsrchr

#endif // !defined(_FCRT_UNICODE)
