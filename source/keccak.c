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

//Keccak round constants
static const keccak_lane_t __keccak_rc[KECCAK_NR] = {
	(keccak_lane_t)0x0000000000000001,
	(keccak_lane_t)0x0000000000008082,
	(keccak_lane_t)0x800000000000808A,
	(keccak_lane_t)0x8000000080008000,
	(keccak_lane_t)0x000000000000808B,
	(keccak_lane_t)0x0000000080000001,
	(keccak_lane_t)0x8000000080008081,
	(keccak_lane_t)0x8000000000008009,
	(keccak_lane_t)0x000000000000008A,
	(keccak_lane_t)0x0000000000000088,
	(keccak_lane_t)0x0000000080008009,
	(keccak_lane_t)0x000000008000000A,
	(keccak_lane_t)0x000000008000808B,
	(keccak_lane_t)0x800000000000008B,
	(keccak_lane_t)0x8000000000008089,
	(keccak_lane_t)0x8000000000008003,
	(keccak_lane_t)0x8000000000008002,
	(keccak_lane_t)0x8000000000000080,
#if (KECCAK_L >= 4)
	(keccak_lane_t)0x000000000000800A,
	(keccak_lane_t)0x800000008000000A,
#endif
#if (KECCAK_L >= 5)
	(keccak_lane_t)0x8000000080008081,
	(keccak_lane_t)0x8000000000008080,
#endif
#if (KECCAK_L >= 6)
	(keccak_lane_t)0x0000000080000001,
	(keccak_lane_t)0x8000000080008008
#endif
};


// Apply theta transformation

static void __cdecl __keccak_theta(keccak_lane_t a[5][5]) {
	keccak_lane_t c[5];
	keccak_lane_t d[5];

	//The effect of the theta transformation is to XOR each bit in the
	//state with the parities of two columns in the array
	c[0] = a[0][0] ^ a[1][0] ^ a[2][0] ^ a[3][0] ^ a[4][0];
	c[1] = a[0][1] ^ a[1][1] ^ a[2][1] ^ a[3][1] ^ a[4][1];
	c[2] = a[0][2] ^ a[1][2] ^ a[2][2] ^ a[3][2] ^ a[4][2];
	c[3] = a[0][3] ^ a[1][3] ^ a[2][3] ^ a[3][3] ^ a[4][3];
	c[4] = a[0][4] ^ a[1][4] ^ a[2][4] ^ a[3][4] ^ a[4][4];

	d[0] = c[4] ^ KECCAK_ROL(c[1], 1);
	d[1] = c[0] ^ KECCAK_ROL(c[2], 1);
	d[2] = c[1] ^ KECCAK_ROL(c[3], 1);
	d[3] = c[2] ^ KECCAK_ROL(c[4], 1);
	d[4] = c[3] ^ KECCAK_ROL(c[0], 1);

	a[0][0] ^= d[0];
	a[1][0] ^= d[0];
	a[2][0] ^= d[0];
	a[3][0] ^= d[0];
	a[4][0] ^= d[0];

	a[0][1] ^= d[1];
	a[1][1] ^= d[1];
	a[2][1] ^= d[1];
	a[3][1] ^= d[1];
	a[4][1] ^= d[1];

	a[0][2] ^= d[2];
	a[1][2] ^= d[2];
	a[2][2] ^= d[2];
	a[3][2] ^= d[2];
	a[4][2] ^= d[2];

	a[0][3] ^= d[3];
	a[1][3] ^= d[3];
	a[2][3] ^= d[3];
	a[3][3] ^= d[3];
	a[4][3] ^= d[3];

	a[0][4] ^= d[4];
	a[1][4] ^= d[4];
	a[2][4] ^= d[4];
	a[3][4] ^= d[4];
	a[4][4] ^= d[4];
}


// Apply rho transformation

static void __cdecl __keccak_rho(keccak_lane_t a[5][5]) {
	//The effect of the rho transformation is to rotate the bits of each lane by
	//an offset, which depends on the fixed x and y coordinates of the lane
	a[0][1] = KECCAK_ROL(a[0][1], 1 % KECCAK_W);
	a[0][2] = KECCAK_ROL(a[0][2], 190 % KECCAK_W);
	a[0][3] = KECCAK_ROL(a[0][3], 28 % KECCAK_W);
	a[0][4] = KECCAK_ROL(a[0][4], 91 % KECCAK_W);

	a[1][0] = KECCAK_ROL(a[1][0], 36 % KECCAK_W);
	a[1][1] = KECCAK_ROL(a[1][1], 300 % KECCAK_W);
	a[1][2] = KECCAK_ROL(a[1][2], 6 % KECCAK_W);
	a[1][3] = KECCAK_ROL(a[1][3], 55 % KECCAK_W);
	a[1][4] = KECCAK_ROL(a[1][4], 276 % KECCAK_W);

	a[2][0] = KECCAK_ROL(a[2][0], 3 % KECCAK_W);
	a[2][1] = KECCAK_ROL(a[2][1], 10 % KECCAK_W);
	a[2][2] = KECCAK_ROL(a[2][2], 171 % KECCAK_W);
	a[2][3] = KECCAK_ROL(a[2][3], 153 % KECCAK_W);
	a[2][4] = KECCAK_ROL(a[2][4], 231 % KECCAK_W);

	a[3][0] = KECCAK_ROL(a[3][0], 105 % KECCAK_W);
	a[3][1] = KECCAK_ROL(a[3][1], 45 % KECCAK_W);
	a[3][2] = KECCAK_ROL(a[3][2], 15 % KECCAK_W);
	a[3][3] = KECCAK_ROL(a[3][3], 21 % KECCAK_W);
	a[3][4] = KECCAK_ROL(a[3][4], 136 % KECCAK_W);

	a[4][0] = KECCAK_ROL(a[4][0], 210 % KECCAK_W);
	a[4][1] = KECCAK_ROL(a[4][1], 66 % KECCAK_W);
	a[4][2] = KECCAK_ROL(a[4][2], 253 % KECCAK_W);
	a[4][3] = KECCAK_ROL(a[4][3], 120 % KECCAK_W);
	a[4][4] = KECCAK_ROL(a[4][4], 78 % KECCAK_W);
}


// Apply pi transformation

static void __cdecl __keccak_pi(keccak_lane_t a[5][5]) {
	keccak_lane_t temp;

	//The effect of the pi transformation is to rearrange the
	//positions of the lanes
	temp = a[0][1];
	a[0][1] = a[1][1];
	a[1][1] = a[1][4];
	a[1][4] = a[4][2];
	a[4][2] = a[2][4];
	a[2][4] = a[4][0];
	a[4][0] = a[0][2];
	a[0][2] = a[2][2];
	a[2][2] = a[2][3];
	a[2][3] = a[3][4];
	a[3][4] = a[4][3];
	a[4][3] = a[3][0];
	a[3][0] = a[0][4];
	a[0][4] = a[4][4];
	a[4][4] = a[4][1];
	a[4][1] = a[1][3];
	a[1][3] = a[3][1];
	a[3][1] = a[1][0];
	a[1][0] = a[0][3];
	a[0][3] = a[3][3];
	a[3][3] = a[3][2];
	a[3][2] = a[2][1];
	a[2][1] = a[1][2];
	a[1][2] = a[2][0];
	a[2][0] = temp;
}


// Apply chi transformation

static void __cdecl __keccak_chi(keccak_lane_t a[5][5]) {
	keccak_lane_t temp1;
	keccak_lane_t temp2;

	//The effect of the chi transformation is to XOR each bit with
	//a non linear function of two other bits in its row
	temp1 = a[0][0];
	temp2 = a[0][1];
	a[0][0] ^= ~a[0][1] & a[0][2];
	a[0][1] ^= ~a[0][2] & a[0][3];
	a[0][2] ^= ~a[0][3] & a[0][4];
	a[0][3] ^= ~a[0][4] & temp1;
	a[0][4] ^= ~temp1 & temp2;

	temp1 = a[1][0];
	temp2 = a[1][1];
	a[1][0] ^= ~a[1][1] & a[1][2];
	a[1][1] ^= ~a[1][2] & a[1][3];
	a[1][2] ^= ~a[1][3] & a[1][4];
	a[1][3] ^= ~a[1][4] & temp1;
	a[1][4] ^= ~temp1 & temp2;

	temp1 = a[2][0];
	temp2 = a[2][1];
	a[2][0] ^= ~a[2][1] & a[2][2];
	a[2][1] ^= ~a[2][2] & a[2][3];
	a[2][2] ^= ~a[2][3] & a[2][4];
	a[2][3] ^= ~a[2][4] & temp1;
	a[2][4] ^= ~temp1 & temp2;

	temp1 = a[3][0];
	temp2 = a[3][1];
	a[3][0] ^= ~a[3][1] & a[3][2];
	a[3][1] ^= ~a[3][2] & a[3][3];
	a[3][2] ^= ~a[3][3] & a[3][4];
	a[3][3] ^= ~a[3][4] & temp1;
	a[3][4] ^= ~temp1 & temp2;

	temp1 = a[4][0];
	temp2 = a[4][1];
	a[4][0] ^= ~a[4][1] & a[4][2];
	a[4][1] ^= ~a[4][2] & a[4][3];
	a[4][2] ^= ~a[4][3] & a[4][4];
	a[4][3] ^= ~a[4][4] & temp1;
	a[4][4] ^= ~temp1 & temp2;
}


// Apply iota transformation

static void __cdecl __keccak_iota(keccak_lane_t a[5][5], unsigned long index) {
	// The iota transformation is parameterized by the round index
	a[0][0] ^= __keccak_rc[index];
}


// Block permutation

void __cdecl __keccak_permut_block(PHASH_CONTEXT context) {
	unsigned long i;
	// Each round consists of a sequence of five transformations,
	// which are called the step mappings
	for (i = 0; i < KECCAK_NR; i++) {
		// Apply theta step mapping
		__keccak_theta(context->a);
		// Apply rho step mapping
		__keccak_rho(context->a);
		// Apply pi step mapping
		__keccak_pi(context->a);
		// Apply chi step mapping
		__keccak_chi(context->a);
		// Apply iota step mapping
		__keccak_iota(context->a, i);
	}
}

// Initialize Keccak context

int __cdecl f_keccak_init(PHASH_CONTEXT context, unsigned long capacity) {
	unsigned long rate;
	int retval = 0;
	// Clear Keccak context
	f_memset(context, 0, sizeof(HASH_CONTEXT));
	// The capacity cannot exceed the width of a Keccak-p permutation
	if (capacity < KECCAK_B) {
		// The rate depends on the capacity of the sponge function
		rate = KECCAK_B - capacity;
		// The rate must be multiple of the lane size
		if ((rate % KECCAK_W) == 0) {
			// Save the block size, in bytes
			context->blockSize = rate / 8;
			// Successful initialization
			retval = 1;
		}
	}
	return retval;
}


// Absorb data

void __cdecl f_keccak_absorb(PHASH_CONTEXT context, const void* input, size_t length) {
	unsigned long i;
	size_t n;
	// Point to the state array
	keccak_lane_t* a = (keccak_lane_t*)context->a;
	// Absorbing phase
	while (length > 0) {
		// Limit the number of bytes to process at a time
		n = MIN(length, context->blockSize - context->length);
		// Copy the data to the buffer
		f_memcpy(context->buffer + context->length, input, n);
		// Number of data bytes that have been buffered
		context->length += n;
		// Advance the data pointer
		input = (unsigned char*)input + n;
		// Remaining bytes to process
		length -= n;
		// Absorb the message block by block
		if (context->length == context->blockSize) {
			// Absorb the current block
			for (i = 0; i < context->blockSize / sizeof(keccak_lane_t); i++)
				a[i] ^= KECCAK_LETOH(context->block[i]);
			// Apply block permutation function
			__keccak_permut_block(context);
			// The input buffer is empty
			context->length = 0;
		}
	}
}


// Finish absorbing phase

void __cdecl f_keccak_final(PHASH_CONTEXT context, unsigned char pad) {
	unsigned long i;
	//Point to the state array
	keccak_lane_t* a = (keccak_lane_t*)context->a;
	//Compute the number of padding bytes
	size_t q = context->blockSize - context->length;
	//Append padding
	f_memset(context->buffer + context->length, 0, q);
	context->buffer[context->length] |= pad;
	context->buffer[context->blockSize - 1] |= 0x80;
	//Absorb the final block
	for (i = 0; i < context->blockSize / sizeof(keccak_lane_t); i++)
		a[i] ^= KECCAK_LETOH(context->block[i]);
	//Apply block permutation function
	__keccak_permut_block(context);
	//Convert lanes to little-endian byte order
	for (i = 0; i < context->blockSize / sizeof(keccak_lane_t); i++)
		a[i] = KECCAK_HTOLE(a[i]);
	//Number of bytes available in the output buffer
	context->length = context->blockSize;
}


// Extract data from the squeezing phase

void __cdecl f_keccak_squeeze(PHASH_CONTEXT context, unsigned char* output, size_t length) {
	unsigned long i;
	size_t n;
	// Point to the state array
	keccak_lane_t* a = (keccak_lane_t*)context->a;
	// An arbitrary number of output bits can be squeezed out of the state
	while (length > 0) {
		//Check whether more data is required
		if (context->length == 0) {
			//Convert lanes to host byte order
			for (i = 0; i < context->blockSize / sizeof(keccak_lane_t); i++)
				a[i] = KECCAK_LETOH(a[i]);
			//Apply block permutation function
			__keccak_permut_block(context);
			//Convert lanes to little-endian byte order
			for (i = 0; i < context->blockSize / sizeof(keccak_lane_t); i++)
				a[i] = KECCAK_HTOLE(a[i]);
			//Number of bytes available in the output buffer
			context->length = context->blockSize;
		}
		//Compute the number of bytes to process at a time
		n = MIN(length, context->length);
		//Copy the output string
		if (output)
			f_memcpy(output, context->digest + context->blockSize - context->length, n);
		//Number of bytes available in the output buffer
		context->length -= n;
		//Advance the data pointer
		output = (unsigned char*)output + n;
		//Number of bytes that remains to be written
		length -= n;
	}
}
