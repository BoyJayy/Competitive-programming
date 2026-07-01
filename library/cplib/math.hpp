#pragma once

namespace cplib {

template <typename T>
T gcd_ll(T a, T b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

template <typename T>
T lcm_ll(T a, T b) {
    return a / gcd_ll(a, b) * b;
}

template <typename T>
T ext_gcd(T a, T b, T& x, T& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    T x1, y1;
    T g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

template <typename T, typename E>
T binpow(T a, E b) {
    T ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

template <typename T, typename E>
T binpow_mod(T a, E b, T mod) {
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
T norm(T x, T mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

template <typename T>
T inv_prime(T x, T mod) {
    return binpow_mod(x, mod - 2, mod);
}

template <typename T>
T inv_any(T a, T mod) {
    T x, y;
    T g = ext_gcd(a, mod, x, y);
    if (g != 1) return -1;
    return norm(x, mod);
}

template <typename T>
std::pair<T, T> crt(T a1, T m1, T a2, T m2) {
    T x, y;
    T g = ext_gcd(m1, m2, x, y);
    if ((a2 - a1) % g) return {0, -1};
    T lcm = m1 / g * m2;
    T t = norm((a2 - a1) / g * x, m2 / g);
    return {norm(a1 + m1 * t, lcm), lcm};
}

std::vector<int> sieve(int n) {
    std::vector<int> primes, lp(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!lp[i]) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > lp[i] || i * p > n) break;
            lp[i * p] = p;
        }
    }
    return primes;
}

template <typename T = long long>
std::vector<std::pair<T, int>> factorize(T x) {
    std::vector<std::pair<T, int>> f;
    for (T p = 2; p * p <= x; p++) {
        if (x % p) continue;
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        f.push_back({p, cnt});
    }
    if (x > 1) f.push_back({x, 1});
    return f;
}

template <typename T = long long>
T phi(T n) {
    T ans = n;
    for (auto [p, cnt] : factorize(n)) {
        ans = ans / p * (p - 1);
    }
    return ans;
}

std::vector<int> mobius(int n) {
    std::vector<int> mu(n + 1), primes, lp(n + 1);
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!lp[i]) {
            lp[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (p > lp[i] || i * p > n) break;
            lp[i * p] = p;
            if (p == lp[i]) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

template <typename T = long long>
std::vector<T> divisors(T n) {
    std::vector<T> d;
    for (T x = 1; x * x <= n; x++) {
        if (n % x) continue;
        d.push_back(x);
        if (x * x != n) d.push_back(n / x);
    }
    std::sort(d.begin(), d.end());
    return d;
}

template <typename T = long long>
struct Comb {
    T mod;
    std::vector<T> fact, invfact;

    Comb(int n, T mod): mod(mod), fact(n + 1, 1), invfact(n + 1, 1) {
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % mod;
        invfact[n] = inv_prime(fact[n], mod);
        for (int i = n; i; i--) invfact[i - 1] = invfact[i] * i % mod;
    }

    T C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % mod * invfact[n - k] % mod;
    }
};

template <typename T = long long>
using Matrix = std::vector<std::vector<T>>;

template <typename T = long long>
Matrix<T> mul(Matrix<T> a, Matrix<T> b, T mod) {
    int n = a.size();
    Matrix<T> c(n, std::vector<T>(n));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return c;
}

template <typename T = long long, typename E = long long>
Matrix<T> mpow(Matrix<T> a, E b, T mod) {
    int n = a.size();
    Matrix<T> ans(n, std::vector<T>(n));
    for (int i = 0; i < n; i++) ans[i][i] = 1;
    while (b) {
        if (b & 1) ans = mul(ans, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return ans;
}

long long mul_mod_ll(long long a, long long b, long long mod) {
    return (long long)((__int128)a * b % mod);
}

bool miller_check(long long n, long long a, long long d, int s) {
    long long x = binpow_mod(a % n, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 1; i < s; i++) {
        x = mul_mod_ll(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}

bool is_prime_ll(long long n) {
    if (n < 2) return false;
    for (long long p : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (n % p == 0) return n == p;
    }
    long long d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (long long a : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (a % n == 0) continue;
        if (!miller_check(n, a, d, s)) return false;
    }
    return true;
}

template <typename T = long long>
void ntt(std::vector<T>& a, bool inv, T mod = 998244353, T root = 3) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        T wlen = binpow_mod(root, (mod - 1) / len, mod);
        if (inv) wlen = inv_prime(wlen, mod);
        for (int i = 0; i < n; i += len) {
            T w = 1;
            for (int j = 0; j < len / 2; j++) {
                T u = a[i + j];
                T v = a[i + j + len / 2] * w % mod;
                a[i + j] = (u + v) % mod;
                a[i + j + len / 2] = (u - v + mod) % mod;
                w = w * wlen % mod;
            }
        }
    }
    if (inv) {
        T ninv = inv_prime((T)n, mod);
        for (T& x : a) x = x * ninv % mod;
    }
}

template <typename T = long long>
std::vector<T> convolution_mod(std::vector<T> a, std::vector<T> b, T mod = 998244353, T root = 3) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1;
    if (std::min(a.size(), b.size()) < 64) {
        std::vector<T> c(need);
        for (int i = 0; i < (int)a.size(); i++) {
            for (int j = 0; j < (int)b.size(); j++) {
                c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
            }
        }
        return c;
    }
    int n = 1;
    while (n < need) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false, mod, root);
    ntt(b, false, mod, root);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;
    ntt(a, true, mod, root);
    a.resize(need);
    return a;
}

template <typename T = long long>
std::vector<T> poly_inv(const std::vector<T>& a, int n, T mod = 998244353, T root = 3) {
    std::vector<T> res(1, inv_prime(a[0], mod));
    while ((int)res.size() < n) {
        int m = res.size() * 2;
        std::vector<T> cur(a.begin(), a.begin() + std::min((int)a.size(), m));
        std::vector<T> prod = convolution_mod(convolution_mod(res, res, mod, root), cur, mod, root);
        res.resize(m);
        for (int i = 0; i < m; i++) {
            T val = i < (int)prod.size() ? prod[i] : 0;
            res[i] = norm((T)2 * res[i] - val, mod);
        }
    }
    res.resize(n);
    return res;
}

template <typename T = long long>
T lagrange(const std::vector<T>& y, long long x, T mod) {
    int n = y.size() - 1;
    if (x <= n) return norm(y[x], mod);
    std::vector<T> pref(n + 2, 1), suf(n + 2, 1), fact(n + 1, 1), invfact(n + 1, 1);
    for (int i = 0; i <= n; i++) fact[i] = (i ? fact[i - 1] * i % mod : 1);
    invfact[n] = inv_prime(fact[n], mod);
    for (int i = n; i; i--) invfact[i - 1] = invfact[i] * i % mod;
    for (int i = 0; i <= n; i++) pref[i + 1] = pref[i] * norm(x - i, mod) % mod;
    for (int i = n; i >= 0; i--) suf[i] = suf[i + 1] * norm(x - i, mod) % mod;
    T ans = 0;
    for (int i = 0; i <= n; i++) {
        T num = pref[i] * suf[i + 1] % mod;
        T den = invfact[i] * invfact[n - i] % mod;
        if ((n - i) & 1) den = mod - den;
        ans = (ans + norm(y[i], mod) * num % mod * den) % mod;
    }
    return ans;
}

}
