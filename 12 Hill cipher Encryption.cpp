#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

// Key matrix
int keyMatrix[SIZE][SIZE] = {
    {9, 4},
    {5, 7}
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
    if (j % 2 != 0) {
        processed[j++] = 'X'; // Pad with 'X' if necessary
    }
    processed[j] = '\0';
}

// Function to multiply matrices
void multiplyMatrices(int a[SIZE][SIZE], int b[SIZE], int result[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            result[i] += a[i][j] * b[j];
        }
        result[i] %= 26;
    }
}

// Function to encrypt the message using Hill cipher
void encryptMessage(char message[], char encrypted[]) {
    int len = strlen(message);
    int i = 0, j = 0;
    while (i < len) {
        int digraph[SIZE] = {message[i++] - 'A', message[i++] - 'A'};
        int encryptedDigraph[SIZE];
        multiplyMatrices(keyMatrix, digraph, encryptedDigraph);
        encrypted[j++] = encryptedDigraph[0] + 'A';
        encrypted[j++] = encryptedDigraph[1] + 'A';
    }
    encrypted[j] = '\0';
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    char processed[100];
    char encrypted[100];

    preprocessMessage(message, processed);
    encryptMessage(processed, encrypted);

    printf("Original message: %s\n", message);
    printf("Processed message: %s\n", processed);
    printf("Encrypted message: %s\n", encrypted);

    return 0;
}
