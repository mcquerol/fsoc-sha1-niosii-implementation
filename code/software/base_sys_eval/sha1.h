/*
 * sha1.h
 *
 *  Created on: 4 Jan 2024
 *      Author: robom
 */

#ifndef SHA1_H_
#define SHA1_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SHA-1 constants
#define SHA1_K1 0x5A827999
#define SHA1_K2 0x6ED9EBA1
#define SHA1_K3 0x8F1BBCDC
#define SHA1_K4 0xCA62C1D6

// Rotate left function
#define SHA1_ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// SHA-1 block size in bytes
#define SHA1_BLOCK_SIZE 64

// Internal function ft() of the compression function
// for 0<=t<=19
#define SHA1_CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
// for 20<=t<=39 && 60<=t<=79
#define SHA1_PARITY(x, y, z) ((x) ^ (y) ^ (z))
// for 40<=t<=59
#define SHA1_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

uint32_t *preproces_input(uint32_t *hash_ptr, const uint32_t *message);
void sha_1(uint32_t *hash_ptr, const uint32_t *message, const uint32_t *prev_hash);
#endif /* SHA1_H_ */
