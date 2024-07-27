#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to perform the RSA encryption
int rsa_encrypt(int plaintext, int e, int n) {
    int ciphertext = 1;
    for (int i = 0; i < e; i++) {
        ciphertext = (ciphertext * plaintext) % n;
    }
    return ciphertext;
}

// Function to perform the RSA decryption
int rsa_decrypt(int ciphertext, int d, int n) {
    int plaintext = 1;
    for (int i = 0; i < d; i++) {
        plaintext = (plaintext * ciphertext) % n;
    }
    return plaintext;
}

int main() {
    // Large modulus n and public key e
    int n = 3234567890123456789; // modulus (n = pq)
    int e = 65537; // public key

    // Alice's message
    char message[] = "HELLO";

    // Encrypt each character separately using RSA
    int ciphertext[5];
    for (int i = 0; i < 5; i++) {
        int plaintext = message[i] - 'A'; // convert to integer between 0 and 25
        ciphertext[i] = rsa_encrypt(plaintext, e, n);
    }

    // Bob receives the ciphertext and decrypts it
    int decrypted[5];
    for (int i = 0; i < 5; i++) {
        decrypted[i] = rsa_decrypt(ciphertext[i], 275, n); // assume Bob has the private key d
    }

    // Print the decrypted message
    for (int i = 0; i < 5; i++) {
        printf("%c", decrypted[i] + 'A'); // convert back to character
    }
    printf("\n");

    return 0;
}