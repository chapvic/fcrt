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

int __cdecl f_le() {
    unsigned long value = 0x0001;
    return (*(unsigned char*)&value) == 1 ? 1 : 0;
}

int __cdecl f_be() {
    unsigned long value = 0x0001;
    return (*(unsigned char*)&value) == 0 ? 1 : 0;
}

unsigned short __cdecl f_swap_int16(unsigned short value) {
    return SWAPINT16(value);
}

unsigned long __cdecl f_swap_int32(unsigned long value) {
    return SWAPINT32(value);
}

unsigned long long __cdecl f_swap_int64(unsigned long long value) {
    return SWAPINT64(value);
}

unsigned char __cdecl f_reverse_int4(unsigned char value) {
    value = ((value & 0x0C) >> 2) | ((value & 0x03) << 2);
    value = ((value & 0x0A) >> 1) | ((value & 0x05) << 1);
    return value;
}

unsigned char __cdecl f_reverse_int8(unsigned char value) {
    value = ((value & 0xF0) >> 4) | ((value & 0x0F) << 4);
    value = ((value & 0xCC) >> 2) | ((value & 0x33) << 2);
    value = ((value & 0xAA) >> 1) | ((value & 0x55) << 1);
    return value;
}

unsigned short __cdecl f_reverse_int16(unsigned short value) {
    value = ((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8);
    value = ((value & 0xF0F0) >> 4) | ((value & 0x0F0F) << 4);
    value = ((value & 0xCCCC) >> 2) | ((value & 0x3333) << 2);
    value = ((value & 0xAAAA) >> 1) | ((value & 0x5555) << 1);
    return value;
}

unsigned long __cdecl f_reverse_int32(unsigned long value) {
    value = ((value & 0xFFFF0000UL) >> 16) | ((value & 0x0000FFFFUL) << 16);
    value = ((value & 0xFF00FF00UL) >> 8) | ((value & 0x00FF00FFUL) << 8);
    value = ((value & 0xF0F0F0F0UL) >> 4) | ((value & 0x0F0F0F0FUL) << 4);
    value = ((value & 0xCCCCCCCCUL) >> 2) | ((value & 0x33333333UL) << 2);
    value = ((value & 0xAAAAAAAAUL) >> 1) | ((value & 0x55555555UL) << 1);
    return value;
}

unsigned long long __cdecl f_reverse_int64(unsigned long long value) {
    value = ((value & 0xFFFFFFFF00000000ULL) >> 32) | ((value & 0x00000000FFFFFFFFULL) << 32);
    value = ((value & 0xFFFF0000FFFF0000ULL) >> 16) | ((value & 0x0000FFFF0000FFFFULL) << 16);
    value = ((value & 0xFF00FF00FF00FF00ULL) >> 8) | ((value & 0x00FF00FF00FF00FFULL) << 8);
    value = ((value & 0xF0F0F0F0F0F0F0F0ULL) >> 4) | ((value & 0x0F0F0F0F0F0F0F0FULL) << 4);
    value = ((value & 0xCCCCCCCCCCCCCCCCULL) >> 2) | ((value & 0x3333333333333333ULL) << 2);
    value = ((value & 0xAAAAAAAAAAAAAAAAULL) >> 1) | ((value & 0x5555555555555555ULL) << 1);
    return value;
}
