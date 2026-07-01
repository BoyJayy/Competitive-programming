template <typename T>
T phi(T n) {
    T ans = n;
    for (T p = 2; p * p <= n; p++) {
        if (n % p) continue;
        while (n % p == 0) n /= p;
        ans -= ans / p;
    }
    if (n > 1) ans -= ans / n;
    return ans;
}
