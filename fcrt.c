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

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include "fcrt_source.h"

// ---------------------------
// Build non-unicode functions
// ---------------------------

#include "source/alloc.c"
#include "source/memctl.c"
#include "source/memhlp.c"
#include "source/binhex.c"
#include "source/base64.c"
#include "source/strconv.c"
#include "source/vardump.c"
#include "source/win64.c"

#include "source/endian.c"

#include "source/crc32.c"
#include "source/md5.c"
#include "source/sha1.c"
#include "source/sha2.c"
#include "source/sha3.c"
#include "source/keccak.c"

#include "source/memlist.c"

#include "source/strlen.c"
#include "source/strdup.c"
#include "source/stristr.c"
#include "source/strcats.c"
#include "source/substr.c"
#include "source/indexof.c"
#include "source/trim.c"
#include "source/justify.c"
#include "source/dup.c"

#include "source/reg.c"

#define _FCRT_EXT_FUNC
#include "source/str_replace.c"
#undef _FCRT_EXT_FUNC
#include "source/str_replace.c"

#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 1
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 2
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 3
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 4
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 5
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 6
#include "source/itoX.c"

// --------------------------
// Build unicode of functions
// --------------------------

#define _FCRT_UNICODE
#include "source/memhlp.c"
#include "source/strlen.c"
#include "source/strdup.c"
#include "source/stristr.c"
#include "source/strcats.c"
#include "source/substr.c"
#include "source/indexof.c"
#include "source/trim.c"
#include "source/justify.c"
#include "source/dup.c"
#include "source/reg.c"

#define _FCRT_EXT_FUNC
#include "source/str_replace.c"
#undef _FCRT_EXT_FUNC
#include "source/str_replace.c"

#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 1
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 2
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 3
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 4
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 5
#include "source/itoX.c"
#undef _FCRT_VARTYPE
#define _FCRT_VARTYPE 6
#include "source/itoX.c"
#undef _FCRT_VARTYPE
