template <typename T>
pair<T, T> fib_pair(long long n, T mod) {
    if (!n) return {0, 1};
    auto [a, b] = fib_pair(n >> 1, mod);
    T c = a * ((2 * b % mod - a + mod) % mod) % mod;
    T d = (a * a + b * b) % mod;
    if (n & 1) return {d, (c + d) % mod};
    return {c, d};
}
