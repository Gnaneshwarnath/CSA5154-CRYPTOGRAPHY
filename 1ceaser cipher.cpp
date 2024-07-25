#include <stdio.h>

// Function to encrypt the text using Caesar Cipher
void caesarCipher(char* text, int key) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        
        if (ch >= 'a' && ch <= 'z') 
		{
            text[i] = ((ch - 'a' + key) % 26) + 'a';
        } 
		else if (ch >= 'A' && ch <= 'Z') 
		{
            text[i] = ((ch - 'A' + key) % 26) + 'A';
        }
    }
}

int main() {
    char text[100];
    int key;

    // Input text to be encrypted
    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character from input
    text[strcspn(text, "\n")] = '\0';

    // Input the key
    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    // Validate the key
    if (key < 1 || key > 25) {
        printf("Invalid key. Please enter a key between 1 and 25.\n");
        return 1;
    }

    // Encrypt the text
    caesarCipher(text, key);

    // Output the encrypted text
    printf("Encrypted text: %s\n", text);

    return 0;
}
