/*
 * Functions for finding prime numbers.
*/

#include <math.h>
#include <stdio.h>
#include "primes.h"

/*
 * Returns the error message associated with each error code.
 * @param errCode: the error code
 * @return: the error message
*/
char* errPrime(int errCode) {
    switch(errCode) {
        case P_IS_PRIME: {
            return "No error.\n";
        };
        case P_HAS_DIVISOR: {
            return "The number has a divisor other than 1 or itself.\n";
        };
        case P_LESS_THAN_TWO: {
            return "Primes must be greater, or equal to two.\n";
        };
        case P_EVEN_NUMBER: {
            return "Two is the only even prime number.\n";
        };
    }

    return "Invalid error code.\n";
}

int isPrime(int x) {
    // A prime must me greater or equal to two.
    if (x <= 1) {
        return P_LESS_THAN_TWO;
    }

    for (int i = 3; i < (int) sqrt(x); i += 2) {
        // Has a divisor other than 1, and itself
        if (x % i == 0) {
            return P_HAS_DIVISOR;
        }
    }

    // All primes > 2 are uneven
    if (x % 2 == 0 && x != 2) {
        return P_EVEN_NUMBER;
    }

    return P_IS_PRIME;
}
