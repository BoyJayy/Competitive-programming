template <typename T, typename E>
T fpowmod(T a, E b, T mod) {
    T ans = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

template <typename T>
T lagrange_equidistant(const vector<T>& y, long long x, T mod) {
    int n = y.size() - 1;
    auto norm = [&](T v) {
        v %= mod;
        if (v < 0) v += mod;
        return v;
    };
    auto inv = [&](T v) {
        return fpowmod(norm(v), mod - 2, mod);
    };
    if (x <= n) return norm(y[x]);

    vector<T> fact(n + 2, 1), invfact(n + 2, 1);
    for (int i = 1; i <= n + 1; i++) fact[i] = fact[i - 1] * i % mod;
    invfact[n + 1] = inv(fact[n + 1]);
    for (int i = n; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % mod;

    vector<T> pref(n + 2, 1), suf(n + 2, 1);
    for (int i = 0; i <= n; i++) pref[i + 1] = pref[i] * norm(x - i) % mod;
    for (int i = n; i >= 0; i--) suf[i] = suf[i + 1] * norm(x - i) % mod;

    T ans = T();
    for (int i = 0; i <= n; i++) {
        T num = pref[i] * suf[i + 1] % mod;
        T den = invfact[i] * invfact[n - i] % mod;
        if ((n - i) & 1) den = mod - den;
        ans = (ans + norm(y[i]) * num % mod * den) % mod;
    }
    return ans;
}
