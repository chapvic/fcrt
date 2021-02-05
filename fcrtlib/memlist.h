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

#ifndef _FCRT_MEMLIST_H
#define _FCRT_MEMLIST_H

#ifndef MEMLIST_SIGNATURE_SIZE
#define MEMLIST_SIGNATURE_SIZE 3
#endif // !MEMLIST_SIGNATURE_SIZE

#pragma pack(push, _CRT_PACKING)

typedef struct _MEMLIST_FILE_HEADER {
	unsigned char signature[MEMLIST_SIGNATURE_SIZE];  // file signature
	unsigned char bitness;                            // data bitness
	unsigned long size;                               // number of items
	unsigned long items;                              // number of real items with existing data
	unsigned long crc32;                              // CRC32 checksum
} MEMLIST_FILE_HEADER, *PMEMLIST_FILE_HEADER;

typedef struct _MEMLIST_ITEM {
	size_t size;
	void * value;
} MEMLIST_ITEM, *PMEMLIST_ITEM;

typedef struct _MEMLIST {
	MEMLIST_ITEM item;
	void * next;  // PMEMLIST
} MEMLIST, *PMEMLIST;

#pragma pack(pop)

// Create new memlist
FCRT PMEMLIST __cdecl f_memlist_new(size_t items);
// Release memlist
FCRT void __cdecl f_memlist_free(PMEMLIST *ptr);
// Get memlist size in items
FCRT size_t __cdecl f_memlist_size(PMEMLIST ptr);
// Get memlist items count with data
FCRT size_t __cdecl f_memlist_count(PMEMLIST ptr);
// Get first empty item index. If no empty items, new item will be added
FCRT size_t __cdecl f_memlist_empty_index(PMEMLIST ptr);
// Clone memlist
FCRT PMEMLIST __cdecl f_memlist_clone(PMEMLIST from);
// Expand memlist
FCRT size_t __cdecl f_memlist_expand(PMEMLIST ptr, size_t items);
// Append new item with or without data to the end of list
FCRT int __cdecl f_memlist_push(PMEMLIST ptr, void *value, size_t size);
// Put value to item by index
FCRT int __cdecl f_memlist_put(PMEMLIST ptr, size_t index, void *value, size_t size);
// Delete item from memlist
FCRT int __cdecl f_memlist_delete(PMEMLIST *ptr, size_t index);
// Remove data from item by index
FCRT int __cdecl f_memlist_clear(PMEMLIST ptr, size_t index);
// Remove all data from memlist (make empty)
FCRT void __cdecl f_memlist_cleanup(PMEMLIST ptr);
// Get memlist item by index
FCRT PMEMLIST_ITEM __cdecl f_memlist_item(PMEMLIST ptr, size_t index);
// Clear memlist item data
FCRT void __cdecl f_memlist_clear_item(PMEMLIST_ITEM item);
// Remove 1st element of memlist
FCRT void __cdecl f_memlist_shift(PMEMLIST *ptr);
// Remove last <items> element(s)
FCRT void __cdecl f_memlist_trunc(PMEMLIST *ptr, size_t items);
// Rotate left memlist items (first => last)
FCRT void __cdecl f_memlist_rol(PMEMLIST *ptr);
// Rotate right memlist items (last => first)
FCRT void __cdecl f_memlist_ror(PMEMLIST *ptr);
// Export memlist to file
FCRT int __cdecl f_memlist_export(PMEMLIST ptr, char *filename);
// Import memlist from file
FCRT PMEMLIST __cdecl f_memlist_import(char *filename);

#ifndef _FCRT_NO_ALIAS
#define memlist_new f_memlist_new
#define memlist_free f_memlist_free
#define memlist_size f_memlist_size
#define memlist_count f_memlist_count
#define memlist_empty_index f_memlist_empty_index
#define memlist_clone f_memlist_clone
#define memlist_expand f_memlist_expand
#define memlist_push f_memlist_push
#define memlist_put f_memlist_put
#define memlist_delete f_memlist_delete
#define memlist_clear f_memlist_clear
#define memlist_cleanup f_memlist_cleanup
#define memlist_item f_memlist_item
#define memlist_clear_item f_memlist_clear_item
#define memlist_shift f_memlist_shift
#define memlist_trunc f_memlist_trunc
#define memlist_rol f_memlist_rol
#define memlist_ror f_memlist_ror
#define memlist_export f_memlist_export
#define memlist_import f_memlist_import
#endif // !_FCRT_NO_ALIAS

#endif // !_FCRT_MEMLIST_H
