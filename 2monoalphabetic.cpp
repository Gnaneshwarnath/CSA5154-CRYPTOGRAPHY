#include <stdio.h>
#include <string.h>

// Function to encrypt the text using Monoalphabetic Substitution Cipher
void monoalphabeticCipher(char* text, const char* key) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        
        if (ch >= 'a' && ch <= 'z') {
            text[i] = key[ch - 'a'];
        } else if (ch >= 'A' && ch <= 'Z') {
            text[i] = key[ch - 'A'] - ('a' - 'A');
        }
    }
}

int main() {
    char text[100];
    const char key[100] = "QWERTYUIOPASDFGHJKLZXCVBNM"; // Example key

    // Input the text to be encrypted
    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character from input
    text[strcspn(text, "\n")] = '\0';

    // Encrypt the text
    monoalphabeticCipher(text, key);

    // Output the encrypted text
    printf("Encrypted text: %s\n", text);

    return 0;
}
