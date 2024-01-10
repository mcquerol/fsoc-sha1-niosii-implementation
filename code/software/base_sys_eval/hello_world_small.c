#include "system.h"
#include "sys/alt_stdio.h"
#include "sha1.h"

typedef unsigned int alt_u32;

#define __I volatile const // read-only permission
#define __IO volatile // read/write permission ...
#define __O volatile // write only permission ;-) doesn't work in C...

typedef struct {
    __IO alt_u32 DATA_REG;
    __IO alt_u32 DIRECTION_REG;
    __IO alt_u32 INTERRUPTMASK_REG;
    __IO alt_u32 EDGECAPTURE_REG;
    __O alt_u32 OUTSET_REG;
    __O alt_u32 OUTCLEAR_REG;
} PIO_TYPE;

#define LEDS (*((PIO_TYPE *) 0x80011020 ))
volatile unsigned long delay = 0;

int main(void){
    //message to pass to sha1 function
    char message[] = "FSOC23/24 is fun!";

    // sha1 hash for "FSOC23/24 is fun!"
    uint32_t expectedHash[5] = {0xa617f4b3, 0xa108b6dd, 0x82bb8c4a, 0x16ab0b35, 0x2a32a0b9};
    //hash variable to be used in custom sha1 function
    uint32_t hash[5] = {0};

	//keep track of how many hashes are matching
	int hashMatches = 0;

    //Padded message length calculation (consider that a byte is formed by 8 bits)
    uint64_t padded_messageLen = ((strlen(message) / 55 ) + 1) * 64 ;

    //Message padding
	uint32_t *padded_message = preproces_input(hash, (const uint32_t *)message);


	for (size_t offset = 0; offset < 64; offset += SHA1_BLOCK_SIZE) {
		const uint32_t *block = padded_message + offset;

		if (offset == 0) {
			sha_1(hash, (const uint32_t *)block, NULL);
		} else if (offset > 0) {
			sha_1(hash, (const uint32_t *)block, hash);
		}
	}

	//print the hashes
	alt_putstr("Expected hash: ");
	for (int i = 0; i < 5; i++) {
		printf("%08x", expectedHash[i]);
	}
	alt_putchar('\n');
	alt_putstr("Sha1 hash: ");
	for (int i = 0; i < 5; i++) {
		printf("%08x", hash[i]);
	}
	alt_putchar('\n');

	//check if generated hash matches expected hash
	for(int i = 0; i < 5; i++){
		if(hash[i] == expectedHash[i]) {
			hashMatches++;
		}
	}

	// check if hash matches expected hash and turn on or off LED
	if(hashMatches == 5) {
		alt_putstr("Correct hash, turning LEDs ON");
		LEDS.DATA_REG = 0xFF;
	} else {
		alt_putstr("Incorrect hash, turning LEDs OFF");
		LEDS.DATA_REG = 0x00;
	}
	alt_putchar('\n');

	return 0;
}
