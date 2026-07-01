int fib_last_digit(long long n) {
    n %= 60;
    if (n == 0) return 0;
    int a = 0, b = 1;
    for (int i = 1; i < n; i++) {
        int c = (a + b) % 10;
        a = b;
        b = c;
    }
    return b;
}
