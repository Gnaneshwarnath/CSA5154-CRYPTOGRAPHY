#include <stdio.h>
#include <string.h>

// Function to decrypt the ciphertext using the substitution key
void decrypt(char ciphertext[], char key[], char plaintext[]) {
    int i, j;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = key[ciphertext[i] - 'A'];
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = key[ciphertext[i] - 'a'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    char key[26];
    char plaintext[sizeof(ciphertext)];

    // Example substitution key (this should be provided or determined)
    // For example, if 'A' is substituted with 'X', 'B' with 'Y', etc.
    strcpy(key, "XYZABCDEFGHIJKLMNOPQRSTUVW");

    decrypt(ciphertext, key, plaintext);

    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
