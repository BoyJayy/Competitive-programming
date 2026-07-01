template <typename T>
T fib_naive(int n) {
    if (n < 2) return n;
    return fib_naive<T>(n - 1) + fib_naive<T>(n - 2);
}
