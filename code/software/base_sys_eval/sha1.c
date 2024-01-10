/*
 * sha1.c
 *
 *  Created on: 4 Jan 2024
 *      Author: robom
 */

#include "sha1.h"

uint32_t *preproces_input(uint32_t *hash_ptr, const uint32_t *message) {

  // Breaking the message into 512-bit blocks
  const uint8_t *byte_message = (const uint8_t *)message;

  size_t message_length = strlen((const char *)byte_message);

  // Calculate Padded Length
  size_t padded_length =
      ((message_length + 8) / SHA1_BLOCK_SIZE + 1) * SHA1_BLOCK_SIZE;

  // Allocate memory for Padded Message
  uint32_t *padded_message =
      (uint32_t *)malloc(padded_length * sizeof(uint32_t));
  if (padded_message == NULL) {
    // Handle memory allocation failure
    return NULL;
  }

  // Initialize Padded Message with Zeros
  for (size_t i = 0; i < padded_length; ++i) {
    padded_message[i] = 0;
  }

  // Copy Message Data to Padded Message
  for (size_t i = 0; i < message_length; ++i) {
    padded_message[i] = byte_message[i];
  }

  // Append '1' Bit to Padded Message
  padded_message[message_length] = 0x80;

  // Adding the original message length in bits
  uint64_t bit_length = (uint64_t)message_length * 8;
  for (int i = 0; i < 8; i++) {
    padded_message[padded_length - 8 + i] =
        (uint8_t)(bit_length >> (56 - i * 8));
  }

  return padded_message;
}

void sha_1(uint32_t *hash_ptr, const uint32_t *message, const uint32_t *prev_hash) {
  // SHA-1 initialization
  uint32_t h0, h1, h2, h3, h4;
  if (prev_hash == NULL) {
    h0 = 0x67452301;
    h1 = 0xEFCDAB89;
    h2 = 0x98BADCFE;
    h3 = 0x10325476;
    h4 = 0xC3D2E1F0;
  } else {
    h0 = prev_hash[0];
    h1 = prev_hash[1];
    h2 = prev_hash[2];
    h3 = prev_hash[3];
    h4 = prev_hash[4];
  }

  const uint32_t *block = (const uint32_t *)message;

  // Initialize the message schedule
  uint32_t w[80];
  for (int i = 0; i < 16; i++) {
    w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) |
           (block[i * 4 + 2] << 8) | block[i * 4 + 3];
  }

  for (int i = 16; i < 80; i++) {
    w[i] = SHA1_ROTL((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1);
  }

  // Initialize hash value for this chunk
  uint32_t a = h0;
  uint32_t b = h1;
  uint32_t c = h2;
  uint32_t d = h3;
  uint32_t e = h4;

  // Comp function
  for (int i = 0; i < 80; i++) {
    uint32_t f, k;
    if (i < 20) {
      f = SHA1_CH(b, c, d);
      k = SHA1_K1;
    } else if (i < 40) {
      f = SHA1_PARITY(b, c, d);
      k = SHA1_K2;
    } else if (i < 60) {
      f = SHA1_MAJ(b, c, d);
      k = SHA1_K3;
    } else {
      f = SHA1_PARITY(b, c, d);
      k = SHA1_K4;
    }

    uint32_t temp = SHA1_ROTL(a, 5) + f + e + k + w[i];
    e = d;
    d = c;
    c = SHA1_ROTL(b, 30);
    b = a;
    a = temp;
  }

  // Update hash values
  h0 += a;
  h1 += b;
  h2 += c;
  h3 += d;
  h4 += e;

  // Set the final hash value
  hash_ptr[0] = h0;
  hash_ptr[1] = h1;
  hash_ptr[2] = h2;
  hash_ptr[3] = h3;
  hash_ptr[4] = h4;
}
