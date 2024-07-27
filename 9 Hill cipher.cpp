#include <stdio.h>
#include <string.h>

#define SIZE 3

void getKeyMatrix(char key[], int keyMatrix[SIZE][SIZE]) {
    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

void encrypt(int cipherMatrix[SIZE][1], int keyMatrix[SIZE][SIZE], int messageVector[SIZE][1]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 1; j++) {
            cipherMatrix[i][j] = 0;
            for (int x = 0; x < SIZE; x++) {
                cipherMatrix[i][j] += keyMatrix[i][x] * messageVector[x][j];
            }
            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
}

void HillCipher(char message[], char key[]) {
    int keyMatrix[SIZE][SIZE];
    getKeyMatrix(key, keyMatrix);

    int messageVector[SIZE][1];
    for (int i = 0; i < SIZE; i++) {
        messageVector[i][0] = (message[i]) % 65;
    }

    int cipherMatrix[SIZE][1];
    encrypt(cipherMatrix, keyMatrix, messageVector);

    char CipherText[SIZE];
    for (int i = 0; i < SIZE; i++) {
        CipherText[i] = cipherMatrix[i][0] + 65;
    }

    printf("Ciphertext: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%c", CipherText[i]);
    }
    printf("\n");
}

int main() {
    char message[SIZE];
    char key[SIZE * SIZE];

    printf("Enter a 3-letter message: ");
    scanf("%s", message);
    printf("Enter a 9-letter key: ");
    scanf("%s", key);

    HillCipher(message, key);

    return 0;
}
