#include <stdio.h>
#include <math.h>
#include <mpi.h>

// Function to check if a number is prime
// Returns 1 if prime, 0 otherwise
int is_prime(int n) {
    if (n <= 1) return 0; // 0 and 1 are not considered primes
    if (n <= 3) return 1; // 2 and 3 are primes
    if (n % 2 == 0 || n % 3 == 0) return 0; // Exclude multiples of 2 and 3 quickly
    for (int i = 5; i * i <= n; i += 6) {
        // Check for factors beyond 5 up to the square root of n
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1; // No factors found, n is prime
}

int main(int argc, char **argv) {
    int rank, size;
    int nstart = 2, nfinish = 10000; // Define the range of numbers to search
    int local_start, local_end;
    int range, local_range;

    MPI_Init(&argc, &argv); // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    // Calculate the total range and divide it among processes
    range = nfinish - nstart + 1;
    local_range = range / size;
    local_start = rank * local_range + nstart;
    local_end = (rank + 1) * local_range + nstart - 1;
    if (rank == size - 1) {
        // Ensure the last process covers any remaining range
        local_end = nfinish;
    }

    // Each process prints its assigned range for verification
    printf("Process %d checking range %d to %d\n", rank, local_start, local_end);

    // Each process checks its range for prime numbers
    for (int n = local_start; n <= local_end; n++) {
        if (is_prime(n)) {
            printf("%d is prime\n", n); // Print if n is prime
        }
    }

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}
