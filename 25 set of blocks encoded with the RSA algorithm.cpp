#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to calculate the modular inverse
int mod_inverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1) return 0;

    while (a > 1) {
        int q = a / m;
        int t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;

    return x;
}

int main() {
    // Given values
    int n = 323; // n = pq
    int e = 5;   // public key
    int c = 181; // ciphertext block with a common factor with n

    // Find the common factor (p or q)
    int p = gcd(c, n);
    printf("Common factor (p or q): %d\n", p);

    // Calculate q
    int q = n / p;
    printf("q: %d\n", q);

    // Calculate phi(n) = (p-1)(q-1)
    int phi_n = (p - 1) * (q - 1);
    printf("phi(n): %d\n", phi_n);

    // Calculate the private key (d)
    int d = mod_inverse(e, phi_n);
    printf("Private key (d): %d\n", d);

    // Decrypt the ciphertext block
    int m = 1;
    for (int i = 0; i < d; i++) {
        m = (m * c) % n;
    }
    printf("Decrypted plaintext block: %d\n", m);

    return 0;
}