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

const unsigned char __memlist_file_signature[MEMLIST_SIGNATURE_SIZE] = { 'M', 'L', 'X' };

PMEMLIST __cdecl f_memlist_new(size_t items) {
	PMEMLIST p, ptr = nullptr;
	if (items) {
		ptr = f_malloc(sizeof(MEMLIST));
		if (ptr) {
			p = ptr;
			while(--items) {
				p->next = f_malloc(sizeof(MEMLIST));
				if (p->next) p = p->next;
			}
		}
	}
	return ptr;
}

void __cdecl f_memlist_free(PMEMLIST *ptr) {
	if (ptr && *ptr) {
		PMEMLIST p = *ptr, pp = nullptr;
		do {
			pp = p->next;
			if (p->item.size) f_free(p->item.value);
			f_free(p);
		} while (p = pp);
		*ptr = nullptr;
	}
}


size_t __cdecl f_memlist_size(PMEMLIST ptr) {
	if (!ptr) return 0;
	size_t size = 1;
	while (ptr = ptr->next) ++size;
	return size;
}

size_t __cdecl f_memlist_count(PMEMLIST ptr) {
	size_t count = 0;
	if (ptr) do {
		if (ptr->item.size) count++;
	} while (ptr = ptr->next);
	return count;
}

size_t __cdecl f_memlist_empty_index(PMEMLIST ptr) {
	size_t index = 0;
	if (ptr) do {
		if (!ptr->item.size) return index;
		++index;
	} while (ptr = ptr->next);
	// No empty items
	f_memlist_push(ptr, nullptr, 0);
	return index;
}

PMEMLIST __cdecl f_memlist_clone(PMEMLIST from) {
	PMEMLIST p, clone = nullptr;
	if (from) {
		size_t len = f_memlist_size(from);
		if (len) {
			clone = f_memlist_new(len);
			if (clone) {
				p = clone;
				while (from && p) {
					if (from->item.size) {
						p->item.value = f_malloc(from->item.size);
						if (p->item.value) {
							f_memcpy(p->item.value, from->item.value, from->item.size);
							p->item.size = from->item.size;
						}
					}
					p = p->next;
					from = from->next;
				}
			}
		}
	}
	return clone;
}

size_t __cdecl f_memlist_expand(PMEMLIST ptr, size_t items) {
	if (!ptr || !items) return 0;
	// go to the end of list
	PMEMLIST p0 = nullptr, p = ptr;
	while(p = p->next) { p0 = p; }
	p0->next = f_memlist_new(items);
	return f_memlist_size(ptr);
}

int __cdecl f_memlist_push(PMEMLIST ptr, void *value, size_t size) {
	int retval = 0;
	if (ptr) {
		// go to the end of list
		PMEMLIST p = ptr;
		while(p = p->next) { ptr = p; }
		// allocate memory for new item
		ptr->next = f_malloc(sizeof(MEMLIST));
		if (ptr->next) {
			p = ptr->next;
			// store value, if exist
			if (value && size) {
				// allocate memory for item data
				p->item.value = f_malloc(size);
				if (p->item.value) {
					f_memcpy(p->item.value, value, size);
					p->item.size = size;
				}
			}
			retval = 1;
		}
	}
	return retval;
}

int __cdecl f_memlist_put(PMEMLIST ptr, size_t index, void *value, size_t size) {
	int retval = 0;
	PMEMLIST_ITEM item = nullptr;
	// skip items
	while(ptr && index--) ptr = ptr->next;
	if (ptr) {
		// delete value, if exist
		f_memlist_clear_item(&ptr->item);
		// store new value, if exist
		if (value && size) {
			ptr->item.value = f_malloc(size);
			if (ptr->item.value) {
				f_memcpy(ptr->item.value, value, size);
				ptr->item.size = size;
			}
		}
		retval = 1;
	}
	return retval;
}

int __cdecl f_memlist_delete(PMEMLIST *ptr, size_t index) {
	int retval = 0;
	if (ptr && *ptr) {
		size_t i = f_memlist_size(*ptr);
		// if index >= list size, then delete last item
		if (i <= index) index = i - 1;
		// if items count = 1, delete entire list
		if (!(*ptr)->next) {
			f_memlist_free(ptr);
			retval = 1;
		} else {
			PMEMLIST p = *ptr, pp = nullptr;
			// skip items with saving prev item
			while(p && index--) { pp = p; p = p->next; }
			// if first item
			if (!pp) {
				pp = p->next;
				if (p->item.size) f_free(p->item.value);
				f_free(p);
				*ptr = pp;
			} else {
				pp->next = p->next;
				if (p->item.size) f_free(p->item.value);
				f_free(p);
			}
			retval = 1;
		}
	}
	return retval;
}

int __cdecl f_memlist_clear(PMEMLIST ptr, size_t index) {
	return f_memlist_put(ptr, index, nullptr, 0);
}

void __cdecl f_memlist_cleanup(PMEMLIST ptr) {
	if (ptr) do {
		f_memlist_clear_item(&ptr->item);
	} while (ptr = ptr->next);
}

PMEMLIST_ITEM __cdecl f_memlist_item(PMEMLIST ptr, size_t index) {
	PMEMLIST_ITEM item = nullptr;
	while(ptr && index--) ptr = ptr->next;
	if (ptr) item = &ptr->item;
	return item;
}

void __cdecl f_memlist_clear_item(PMEMLIST_ITEM item) {
	if (item->size) {
		f_freez(&item->value);
		item->size = 0;
	}
}

void __cdecl f_memlist_shift(PMEMLIST *ptr) {
	if (ptr && *ptr) {
		PMEMLIST p = *ptr;
		*ptr = (*ptr)->next;
		if (p->item.size) f_free(p->item.value);
		f_free(p);
	}
}

void __cdecl f_memlist_trunc(PMEMLIST *ptr, size_t items) {
	if (ptr && *ptr && items) {
		size_t size = f_memlist_size(*ptr);
		if (size > items) {
			size -= items;
			PMEMLIST p = *ptr, pp = nullptr;
			// skip items before deletions
			int cnt = 0;
			while(size--) { pp = p; p = p->next; cnt++; }
			// remove trailing items
			f_memlist_free(&p);
			// cleanup next item pointer for the last item
			pp->next = nullptr;
		} else {
			// the count is exceeded or equal to the size of the list - deleting the entire list
			f_memlist_free(ptr);
		}
	}
}

void __cdecl f_memlist_rol(PMEMLIST *ptr) {
	if (ptr && *ptr && (*ptr)->next) {
		PMEMLIST p0 = nullptr, p = *ptr, pp = (*ptr)->next;
		// go to the end of list
		while(p = p->next) { p0 = p; }
		// move first item to the end of list
		p0->next = *ptr;
		// clear next item pointer for the last list item
		(*ptr)->next = nullptr;
		// set second item as first
		*ptr = pp;
	}
}

void __cdecl f_memlist_ror(PMEMLIST *ptr) {
	if (ptr && *ptr && (*ptr)->next) {
		PMEMLIST p0 = *ptr, p = *ptr, pp = nullptr;
		// go to the end of list with saving prev item
		while(p = p->next) { pp = p0; p0 = p; }
		// prev item is the end of list
		pp->next = nullptr;
		// move last item to the begin of list
		p0->next = *ptr;
		*ptr = p0;
	}
}

int __cdecl f_memlist_export(PMEMLIST ptr, char *filename) {
	size_t fsize;             // filesize return value
	// file handle
	FILE *handle = 0;
	// init file header
	MEMLIST_FILE_HEADER header = { 0 };
	if(ptr && filename && strlen(filename)) {
		handle = fopen(filename, "wb+");
		if (handle != ((void*)-1)) {
			// make file signature
			f_memcpy(&header.signature, &__memlist_file_signature, MEMLIST_SIGNATURE_SIZE);
			// save data bitness
			header.bitness = (sizeof(void*) * 8);  // 32 or 64
			// get list size
			header.size = (unsigned long)f_memlist_size(ptr);
			// get real items count
			header.items = (unsigned long)f_memlist_count(ptr);
			// start CRC32 computation (header without CRC32 field)
			header.crc32 = f_crc32(header.crc32, (unsigned char *)&header, sizeof(header) - sizeof(header.crc32));
			// write file header
			if (!fwrite(&header, sizeof(header), 1, handle)) goto Error;
			fsize = sizeof(header);
			// save each item of list (if no data, save nothing)
			unsigned long index = 0;  // index counter
			do {
				if (ptr->item.size) {
					// save index number
					if (!fwrite(&index, sizeof(index), 1, handle)) goto Error;
					fsize += sizeof(index);
					header.crc32 = f_crc32(header.crc32, (unsigned char *)&index, sizeof(index));
					// save data size
					if (!fwrite(&ptr->item.size, sizeof(ptr->item.size), 1, handle)) goto Error;
					fsize += sizeof(ptr->item.size);
					header.crc32 = f_crc32(header.crc32, (unsigned char *)&ptr->item.size, sizeof(ptr->item.size));
					// save data
					if (!fwrite(ptr->item.value, ptr->item.size, 1, handle)) goto Error;
					fsize += ptr->item.size;
					header.crc32 = f_crc32(header.crc32, (unsigned char *)ptr->item.value, ptr->item.size);
				}
				// increment memlist index
				index++;
			} while (ptr = ptr->next);
			// save header again with computed CRC32
			fseek(handle, 0, SEEK_SET);
			if (fwrite(&header, sizeof(header), 1, handle)) goto Done;
		}
	}
Error:
	fsize = 0;
Done:
	if (handle) fclose(handle);
	return fsize;
}

PMEMLIST __cdecl f_memlist_import(char *filename) {
	// return value
	PMEMLIST ptr = nullptr;
	// file handle
	FILE *handle = nullptr;
	// init file header
	MEMLIST_FILE_HEADER header = { 0 };
	size_t index = 0;               // data index buffer
	size_t size = 0;                // data size buffer
	void *buffer = nullptr;         // data buffer
	unsigned long crc = 0;          // CRC-32 calculation value
	if(filename && strlen(filename)) {
		handle = fopen(filename, "rb");
		if (handle != ((void*)-1)) {
			// read file signature
			if (!fread(&header, sizeof(header), 1, handle)) goto Done;
			// check file signature
			if (f_memcmp(&header.signature, __memlist_file_signature, MEMLIST_SIGNATURE_SIZE) != 0) goto Done;
			// check for data bitness
			if (header.bitness != (sizeof(void*) * 8)) goto Done;
			// check for memlist size
			if (!header.size) goto Done;
			// CRC-32 must not be zero!
			if (!header.crc32) goto Done;
			// create empty memory list
			ptr = f_memlist_new(header.size);
			if (!ptr) goto Done;
			// start CRC32 computation (header without CRC32 field)
			crc = f_crc32(crc, (unsigned char *)&header, sizeof(header) - sizeof(header.crc32));
			// check for data exist
			if (header.items) {
				// load each item
				while (header.items--) {
					// load index number
					if (!fread(&index, sizeof(index), 1, handle)) goto Error;
					crc = f_crc32(crc, (unsigned char *)&index, sizeof(index));
					// load data size (size must not be zero)
					if (!fread(&size, sizeof(size), 1, handle) || !size) goto Error;
					crc = f_crc32(crc, (unsigned char *)&size, sizeof(size));
					// load data
					buffer = f_realloc(buffer, size);
					if (!buffer) goto Error;
					if (!fread(buffer, size, 1, handle)) goto Error;
					if (!f_memlist_put(ptr, index, buffer, size)) goto Error;
					crc = f_crc32(crc, (unsigned char *)buffer, size);
				}
			}
			// check CRC32
			if (crc == header.crc32) goto Done;
		}
	}
Error:
	if (ptr) f_memlist_free(&ptr);
Done:
	if (buffer) f_free(buffer);
	if (handle) fclose(handle);
	return ptr;
}
