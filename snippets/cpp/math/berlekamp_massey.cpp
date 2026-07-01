template <typename T, typename E>
T fpowmod(T a, E b, T mod) {
    T ans = 1 % mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

template <typename T>
vector<T> berlekamp_massey(const vector<T>& s, T mod) {
    vector<T> C{1}, B{1};
    T b = 1;
    int L = 0, m = 1;
    for (int n = 0; n < (int)s.size(); n++) {
        T d = T();
        for (int i = 0; i <= L; i++) d = (d + C[i] * s[n - i]) % mod;
        if (!d) {
            m++;
            continue;
        }
        vector<T> old = C;
        T coef = d * fpowmod(b, mod - 2, mod) % mod;
        if ((int)C.size() < (int)B.size() + m) C.resize(B.size() + m);
        for (int i = 0; i < (int)B.size(); i++) {
            C[i + m] = (C[i + m] - coef * B[i]) % mod;
            if (C[i + m] < 0) C[i + m] += mod;
        }
        if (2 * L <= n) {
            L = n + 1 - L;
            B = old;
            b = d;
            m = 1;
        }
        else {
            m++;
        }
    }
    C.erase(C.begin());
    for (T& x : C) x = (mod - x) % mod;
    return C;
}
