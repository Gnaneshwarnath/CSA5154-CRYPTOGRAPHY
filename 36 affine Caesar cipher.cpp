#include <stdio.h>

// Function to perform the encryption
char encrypt(char plaintext, int a, int b) {
    return ((a * (plaintext - 'A') + b) % 26) + 'A';
}

// Function to perform the decryption
char decrypt(char ciphertext, int a, int b) {
    int inverse_a = 0;
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            inverse_a = i;
            break;
        }
    }
    return ((inverse_a * (ciphertext - 'A' - b)) % 26) + 'A';
}

int main() {
    // Key values
    int a = 2;
    int b = 3;

    // Plaintext message
    char plaintext[] = "HELLO";

    // Encrypt the message
    char ciphertext[6];
    for (int i = 0; i < 5; i++) {
        ciphertext[i] = encrypt(plaintext[i], a, b);
    }
    ciphertext[5] = '\0'; // null-terminate the string

    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the message
    char decrypted[6];
    for (int i = 0; i < 5; i++) {
        decrypted[i] = decrypt(ciphertext[i], a, b);
    }
    decrypted[5] = '\0'; // null-terminate the string

    printf("Decrypted: %s\n", decrypted);

    return 0;
}