#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt the text using Vigenère Cipher
void vigenereCipher(char* text, char* key) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int i, j;

    // Convert key to uppercase
    for (i = 0; i < keyLen; i++) {
        key[i] = toupper(key[i]);
    }

    // Encrypt the text
    for (i = 0, j = 0; i < textLen; i++) {
        char ch = text[i];

        if (isalpha(ch)) {
            char offset = isupper(ch) ? 'A' : 'a';
            text[i] = ((ch - offset + (key[j % keyLen] - 'A')) % 26) + offset;
            j++;
        }
    }
}

int main() {
    char text[100];
    char key[100];

    // Input the plaintext
    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    // Input the key
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    // Encrypt the text
    vigenereCipher(text, key);

    // Output the encrypted text
    printf("Encrypted text: %s\n", text);

    return 0;
}
