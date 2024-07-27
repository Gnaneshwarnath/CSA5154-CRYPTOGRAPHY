#include <stdio.h>
#include <stdlib.h>

// Function to calculate the modular exponentiation
int mod_exp(int base, int exponent, int modulus) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result = (result * base) % modulus;
    }
    return result;
}

int main() {
    // Public numbers
    int p = 23; // prime number
    int g = 5; // generator

    // Alice's secret number
    int alice_x = 6;

    // Bob's secret number
    int bob_x = 15;

    // Alice sends Bob A = g^x mod p
    int alice_A = mod_exp(g, alice_x, p);

    // Bob sends Alice B = g^x mod p
    int bob_B = mod_exp(g, bob_x, p);

    // Alice calculates the shared secret key
    int alice_key = mod_exp(bob_B, alice_x, p);

    // Bob calculates the shared secret key
    int bob_key = mod_exp(alice_A, bob_x, p);

    printf("Alice's shared secret key: %d\n", alice_key);
    printf("Bob's shared secret key: %d\n", bob_key);

    return 0;
}