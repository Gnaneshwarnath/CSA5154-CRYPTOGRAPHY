#include <stdio.h>
#include <math.h>

// Function to check if a number is prime
int isPrime(int num) {
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return 0; // Not prime
        }
    }
    return 1; // Prime
}

// Function to find the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to calculate the private key (d)
int calculatePrivateKey(int e, int phi) {
    int d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }
    return d;
}

int main() {
    int p = 3; // Prime number
    int q = 11; // Prime number
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 31; // Public key
    int d = calculatePrivateKey(e, phi);

    printf("Public key (n, e): (%d, %d)\n", n, e);
    printf("Private key (d): %d\n", d);

    // Example: Encrypt "HI"
    int plaintext = 8 * 100 + 9; // Convert letters to numbers
    int encrypted = fmod(pow(plaintext, e), n);
    printf("Encrypted data: %d\n", encrypted);

    // Example: Decrypt
    int decrypted = fmod(pow(encrypted, d), n);
    printf("Decrypted data: %d\n", decrypted);

    return 0;
}
