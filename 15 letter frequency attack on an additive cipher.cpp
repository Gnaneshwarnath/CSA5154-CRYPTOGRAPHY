#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to decrypt a monoalphabetic substitution cipher using letter frequency attack
void decryptWithFrequencyAnalysis(const char *ciphertext, char *plaintext) {
    // Define the most frequent letters in English
    const char *T = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

    int freq[26] = {0}; // Frequency of each character in the ciphertext
    int freqSorted[26]; // Sorted frequency array
    int Used[26] = {0}; // To keep track of used characters

    int N = strlen(ciphertext);
    for (int i = 0; i < N; i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A']++;
        }
    }

    // Create a sorted frequency array
    for (int i = 0; i < 26; i++) {
        freqSorted[i] = freq[i];
    }
    // Sort in descending order
    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freqSorted[j] > freqSorted[i]) {
                int temp = freqSorted[i];
                freqSorted[i] = freqSorted[j];
                freqSorted[j] = temp;
            }
        }
    }

    // Decrypt the ciphertext using the frequency analysis
    for (int i = 0; i < 5; i++) {
        int ch = -1;
        for (int j = 0; j < 26; j++) {
            if (freqSorted[i] == freq[j] && !Used[j]) {
                Used[j] = 1;
                ch = j;
                break;
            }
        }
        if (ch == -1) break;

        int x = T[i] - 'A' - ch;
        for (int k = 0; k < N; k++) {
            if (isalpha(ciphertext[k])) {
                int y = toupper(ciphertext[k]) - 'A' + x;
                if (y < 0) y += 26;
                if (y >= 26) y -= 26;
                plaintext[k] = 'A' + y;
            } else {
                plaintext[k] = ciphertext[k]; // Preserve non-alphabetic characters
            }
        }
        plaintext[N] = '\0';
        printf("Plaintext %d: %s\n", i + 1, plaintext);
    }
}

int main() {
    const char *ciphertext = "BEQYHJXQYJYON"; // Example ciphertext
    char plaintext[100];

    decryptWithFrequencyAnalysis(ciphertext, plaintext);

    return 0;
}
