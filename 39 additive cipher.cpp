#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEXT_LENGTH 1000
#define ALPHABET_SIZE 26

// Frequency of letters in the English language (in descending order)
const char english_freq[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function to count the frequency of each letter in the ciphertext
void count_frequency(const char *text, int *freq) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = 0;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            freq[text[i] - 'A']++;
        }
    }
}

// Function to sort the letters by frequency in descending order
void sort_by_frequency(int *freq, char *sorted_freq) {
    int max, index;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        max = -1;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (freq[j] > max) {
                max = freq[j];
                index = j;
            }
        }
        sorted_freq[i] = 'A' + index;
        freq[index] = -1; // Mark this frequency as used
    }
}

// Function to decrypt the ciphertext using the given key
void decrypt(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to generate possible plaintexts
void generate_plaintexts(const char *ciphertext, int top_n) {
    int freq[ALPHABET_SIZE];
    char sorted_freq[ALPHABET_SIZE];
    char plaintext[MAX_TEXT_LENGTH];

    count_frequency(ciphertext, freq);
    sort_by_frequency(freq, sorted_freq);

    for (int i = 0; i < top_n; i++) {
        int shift = (sorted_freq[0] - 'A') - (english_freq[i] - 'A');
        decrypt(ciphertext, shift, plaintext);
        printf("Possible plaintext %d: %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    int top_n;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_n);

    generate_plaintexts(ciphertext, top_n);

    return 0;
}
