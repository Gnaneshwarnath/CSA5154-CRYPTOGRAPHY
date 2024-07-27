#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to perform the RSA encryption
int rsa_encrypt(int plaintext, int e, int n) {
    int ciphertext = 1;
    for (int i = 0; i < e; i++) {
        ciphertext = (ciphertext * plaintext) % n;
    }
    return ciphertext;
}

// Function to perform the RSA decryption
int rsa_decrypt(int ciphertext, int d, int n) {
    int plaintext = 1;
    for (int i = 0; i < d; i++) {
        plaintext = (plaintext * ciphertext) % n;
    }
    return plaintext;
}

// Function to calculate the modular inverse
int mod_inverse(int a, int m) {
    int x, y;
    int g = gcd(a, m);
    if (g != 1) return -1;
    x = 1;
    y = 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    return x;
}

int main() {
    // Original public and private keys
    int n = 323; // modulus (n = pq)
    int e = 17; // public key
    int d = 275; // private key (leaked)

    // Leaked private key allows Eve to factorize n
    int p = 17; // factor of n
    int q = 19; // factor of n

    // Bob generates new public and private keys without changing n
    int new_e = 23; // new public key
    int new_d = mod_inverse(new_e, (p - 1) * (q - 1)); // new private key

    // Eve can still decrypt messages using the leaked private key
    int ciphertext = rsa_encrypt(123, new_e, n);
    int plaintext = rsa_decrypt(ciphertext, d, n);
    printf("Eve can still decrypt messages: %d\n", plaintext);

    return 0;
}