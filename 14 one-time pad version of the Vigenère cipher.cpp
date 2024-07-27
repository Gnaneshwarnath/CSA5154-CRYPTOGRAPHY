#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the key by repeating the given key
void generateKey(const char *plaintext, const char *givenKey, char *generatedKey) {
    int keyLength = strlen(givenKey);
    int plaintextLength = strlen(plaintext);

    for (int i = 0; i < plaintextLength; i++) {
        generatedKey[i] = givenKey[i % keyLength];
    }
    generatedKey[plaintextLength] = '\0';
}

// Function to perform one-time pad encryption
void encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int plaintextLength = strlen(plaintext);

    for (int i = 0; i < plaintextLength; i++) {
        char p = toupper(plaintext[i]);
        char k = toupper(key[i]);

        char encryptedChar = ((p - 'A') + (k - 'A')) % 26 + 'A';
        ciphertext[i] = encryptedChar;
    }
    ciphertext[plaintextLength] = '\0';
}

int main() {
    const char *plaintext = "HELLO"; // Example plaintext
    const char *givenKey = "3 19 5"; // Example key (random numbers)

    char generatedKey[100];
    generateKey(plaintext, givenKey, generatedKey);

    char ciphertext[100];
    encrypt(plaintext, generatedKey, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
