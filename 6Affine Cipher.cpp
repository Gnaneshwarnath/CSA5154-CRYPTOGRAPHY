#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find the modular multiplicative inverse of a under modulo m
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse if this is reached
}

// Function to encrypt the text using Affine Cipher
void affineEncrypt(char* text, int a, int b) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            char offset = isupper(ch) ? 'A' : 'a';
            text[i] = ((a * (ch - offset) + b) % 26) + offset;
        }
    }
}

// Function to decrypt the text using Affine Cipher
void affineDecrypt(char* text, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Multiplicative inverse of a does not exist. Decryption is not possible.\n");
        return;
    }

    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            char offset = isupper(ch) ? 'A' : 'a';
            text[i] = (a_inv * ((ch - offset) - b + 26) % 26) + offset;
        }
    }
}

int main() 
{
    char text[100];
    int a, b;

    // Input the plaintext
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    // Input the values of a and b
    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);

    // Check if 'a' is coprime with 26
    if (modInverse(a, 26) == -1) {
        printf("The value of a is not coprime with 26. Please choose another value for a.\n");
        return 1;
    }

    // Encrypt the text
    affineEncrypt(text, a, b);
    printf("Encrypted text: %s\n", text);

    // Decrypt the text
    affineDecrypt(text, a, b);
    printf("Decrypted text: %s\n", text);

    return 0;
}
