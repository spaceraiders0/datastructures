typedef enum primeError {
    P_IS_PRIME,
    P_HAS_DIVISOR,
    P_EVEN_NUMBER,
    P_LESS_THAN_TWO,
} primeError;

char* errPrime(int errCode);
int isPrime(int x);
int getNextPrime(int start);
