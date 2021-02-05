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

#ifndef _FCRT_VARDUMP_H
#define _FCRT_VARDUMP_H

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

#endif // !_FCRT_VARDUMP_H
