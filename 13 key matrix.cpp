#include <stdio.h>

// Function to find the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to solve the system of linear equations
void solveSystem(int P[2][2], int C[2][2], int K[2][2]) {
    int det = P[0][0] * P[1][1] - P[0][1] * P[1][0];
    int det_inv = modInverse(det, 26);

    int adj[2][2] = {
        {P[1][1], -P[0][1]},
        {-P[1][0], P[0][0]}
    };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            adj[i][j] = (adj[i][j] * det_inv) % 26;
            if (adj[i][j] < 0) adj[i][j] += 26;
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            K[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                K[i][j] = (K[i][j] + adj[i][k] * C[k][j]) % 26;
            }
        }
    }
}

int main() {
    int P[2][2] = {{7, 8}, {1, 24}};
    int C[2][2] = {{12, 15}, {5, 13}};
    int K[2][2];

    solveSystem(P, C, K);

    printf("Key matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", K[i][j]);
        }
        printf("\n");
    }

    return 0;
}
