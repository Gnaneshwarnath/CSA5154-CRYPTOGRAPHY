#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 // Block size in bytes

void XOR(unsigned char *a, unsigned char *b, unsigned char *result, int length) {
    for (int i = 0; i < length; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void CBC_MAC(unsigned char *key, unsigned char *message, unsigned char *mac, int length) {
    unsigned char block[BLOCK_SIZE];
    unsigned char iv[BLOCK_SIZE] = {0}; // Initialization vector set to zero

    // Initialize MAC with IV
    memcpy(mac, iv, BLOCK_SIZE);

    // Process each block
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        XOR(mac, message + i, block, BLOCK_SIZE);
        // Encrypt the block (placeholder for actual encryption function)
        // For simplicity, we'll just copy the block to MAC
        memcpy(mac, block, BLOCK_SIZE);
    }
}

int main() {
    unsigned char key[BLOCK_SIZE] = "key12345"; // Example key
    unsigned char message[BLOCK_SIZE] = "message1"; // One-block message X
    unsigned char mac[BLOCK_SIZE]; // To store the MAC

    // Compute CBC-MAC for the one-block message X
    CBC_MAC(key, message, mac, BLOCK_SIZE);
    printf("CBC-MAC for one-block message X: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", mac[i]);
    }
    printf("\n");

    // Compute the two-block message X || (X ? T)
    unsigned char two_block_message[2 * BLOCK_SIZE];
    unsigned char xor_block[BLOCK_SIZE];

    // First block is X
    memcpy(two_block_message, message, BLOCK_SIZE);

    // Second block is X ? T
    XOR(message, mac, xor_block, BLOCK_SIZE);
    memcpy(two_block_message + BLOCK_SIZE, xor_block, BLOCK_SIZE);

    // Compute CBC-MAC for the two-block message
    unsigned char mac_two_block[BLOCK_SIZE];
    CBC_MAC(key, two_block_message, mac_two_block, 2 * BLOCK_SIZE);
    printf("CBC-MAC for two-block message X || (X ? T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", mac_two_block[i]);
    }
    printf("\n");

    return 0;
}
