template <typename T>
struct FactTable {
    int n;
    T mod;
    vector<T> fact, inv, invfact;

    FactTable(int n, T mod): n(n), mod(mod), fact(n + 1), inv(n + 1), invfact(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % mod;
        inv[1] = 1;
        for (int i = 2; i <= n; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
        invfact[0] = 1;
        for (int i = 1; i <= n; i++) invfact[i] = invfact[i - 1] * inv[i] % mod;
    }

    T C(int n, int k) {
        if (k < 0 || k > n) return T();
        return fact[n] * invfact[k] % mod * invfact[n - k] % mod;
    }
};
