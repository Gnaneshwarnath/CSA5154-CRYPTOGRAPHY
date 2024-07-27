#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Playfair matrix
char matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

// Function to preprocess the message
void preprocessMessage(char message[], char processed[]) {
    int len = strlen(message);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            processed[j++] = toupper(message[i]);
        }
    }
    processed[j] = '\0';
}

// Function to find the position of a character in the matrix
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt the message using Playfair cipher
void encryptMessage(char message[], char encrypted[]) {
    int len = strlen(message);
    int i = 0, j = 0;
    while (i < len) {
        char a = message[i++];
        char b = (i < len) ? message[i++] : 'X'; // Pad with 'X' if necessary

        if (a == b) {
            b = 'X'; // Handle repeated characters
            i--;
        }

        int row1, col1, row2, col2;
        findPosition(a, &row1, &col1);
        findPosition(b, &row2, &col2);

        if (row1 == row2) {
            encrypted[j++] = matrix[row1][(col1 + 1) % SIZE];
            encrypted[j++] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            encrypted[j++] = matrix[(row1 + 1) % SIZE][col1];
            encrypted[j++] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            encrypted[j++] = matrix[row1][col2];
            encrypted[j++] = matrix[row2][col1];
        }
    }
    encrypted[j] = '\0';
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char processed[100];
    char encrypted[100];

    preprocessMessage(message, processed);
    encryptMessage(processed, encrypted);

    printf("Original message: %s\n", message);
    printf("Processed message: %s\n", processed);
    printf("Encrypted message: %s\n", encrypted);

    return 0;
}
