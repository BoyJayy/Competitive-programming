long long fib_naive(int n) {
    if (n < 2) return n;
    return fib_naive(n - 1) + fib_naive(n - 2);
}
