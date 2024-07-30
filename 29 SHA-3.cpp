#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 1024
#define LANE_SIZE 64
#define NUM_LANES (BLOCK_SIZE / LANE_SIZE)
#define CAPACITY_LANES (BLOCK_SIZE / 2 / LANE_SIZE)

void initialize_state(unsigned long long state[NUM_LANES]) {
    // Initialize all lanes to zero
    memset(state, 0, NUM_LANES * sizeof(unsigned long long));
}

void process_block(unsigned long long state[NUM_LANES], unsigned long long block[NUM_LANES]) {
    // XOR the block into the state
    for (int i = 0; i < NUM_LANES; i++) {
        state[i] ^= block[i];
    }
}

int all_capacity_lanes_nonzero(unsigned long long state[NUM_LANES]) {
    for (int i = 0; i < CAPACITY_LANES; i++) {
        if (state[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    unsigned long long state[NUM_LANES];
    unsigned long long block[NUM_LANES];
    int iterations = 0;

    // Initialize the state
    initialize_state(state);

    // Assume each lane in the first message block has at least one nonzero bit
    for (int i = 0; i < NUM_LANES; i++) {
        block[i] = (i + 1); // Example nonzero values
    }

    // Process blocks until all capacity lanes are nonzero
    while (!all_capacity_lanes_nonzero(state)) {
        process_block(state, block);
        iterations++;
    }

    printf("Iterations needed: %d\n", iterations);

    return 0;
}
