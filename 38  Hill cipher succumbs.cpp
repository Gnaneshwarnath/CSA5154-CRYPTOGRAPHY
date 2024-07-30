#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3 // Size of the key matrix

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to calculate the determinant of a matrix
int determinant(int matrix[N][N], int n) {
    int det = 0;
    if (n == 1) {
        return matrix[0][0];
    }
    int temp[N][N];
    int sign = 1;
    for (int f = 0; f < n; f++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == f) {
                    continue;
                }
                temp[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += sign * matrix[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return det;
}

// Function to find the adjoint of a matrix
void adjoint(int matrix[N][N], int adj[N][N]) {
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }
    int sign = 1, temp[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int subi = 0;
            for (int ii = 0; ii < N; ii++) {
                if (ii == i) {
                    continue;
                }
                int subj = 0;
                for (int jj = 0; jj < N; jj++) {
                    if (jj == j) {
                        continue;
                    }
                    temp[subi][subj] = matrix[ii][jj];
                    subj++;
                }
                subi++;
            }
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign * determinant(temp, N - 1));
        }
    }
}

// Function to find the inverse of a matrix
int inverse(int matrix[N][N], int inv[N][N]) {
    int det = determinant(matrix, N);
    int invDet = modInverse(det, 26);
    if (invDet == -1) {
        printf("Inverse doesn't exist\n");
        return 0;
    }
    int adj[N][N];
    adjoint(matrix, adj);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inv[i][j] = (adj[i][j] * invDet) % 26;
            if (inv[i][j] < 0) {
                inv[i][j] += 26;
            }
        }
    }
    return 1;
}

// Function to multiply two matrices
void multiplyMatrices(int a[N][N], int b[N][N], int result[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
            result[i][j] %= 26;
        }
    }
}

// Function to decrypt the ciphertext using the key matrix
void decrypt(int key[N][N], char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    int invKey[N][N];
    if (!inverse(key, invKey)) {
        printf("Key matrix is not invertible\n");
        return;
    }
    for (int i = 0; i < len; i += N) {
        int cipherVec[N][1];
        for (int j = 0; j < N; j++) {
            cipherVec[j][0] = ciphertext[i + j] - 'A';
        }
        int plainVec[N][1];
        multiplyMatrices(invKey, cipherVec, plainVec);
        for (int j = 0; j < N; j++) {
            plaintext[i + j] = plainVec[j][0] + 'A';
        }
    }
    plaintext[len] = '\0';
}

int main() {
    int key[N][N] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    char ciphertext[] = "POH";
    char plaintext[MAX_TEXT_LENGTH];

    decrypt(key, ciphertext, plaintext);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
