#include <stdio.h>
#include <math.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Function to calculate the approximate power of 2
double log2_approx(unsigned long long n) {
    return log2((double)n);
}

int main() {
    int n = 25;
    unsigned long long fact = factorial(n);
    double power_of_2 = log2_approx(fact);

    printf("%d! = %llu\n", n, fact);
    printf("Approximate power of 2: 2^%.2f\n", power_of_2);

    return 0;
}
