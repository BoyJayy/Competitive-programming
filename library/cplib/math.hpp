#pragma once

namespace cplib {

long long gcd_ll(long long a, long long b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

long long lcm_ll(long long a, long long b) {
    return a / gcd_ll(a, b) * b;
}

long long ext_gcd(long long a, long long b, long long& x, long long& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

long long binpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

long long binpow_mod(long long a, long long b, long long mod) {
    long long ans = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long long norm(long long x, long long mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

long long inv_prime(long long x, long long mod) {
    return binpow_mod(x, mod - 2, mod);
}

long long inv_any(long long a, long long mod) {
    long long x, y;
    long long g = ext_gcd(a, mod, x, y);
    if (g != 1) return -1;
    return norm(x, mod);
}

std::pair<long long, long long> crt(long long a1, long long m1, long long a2, long long m2) {
    long long x, y;
    long long g = ext_gcd(m1, m2, x, y);
    if ((a2 - a1) % g) return {0, -1};
    long long lcm = m1 / g * m2;
    long long t = norm((a2 - a1) / g * x, m2 / g);
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

std::vector<std::pair<long long, int>> factorize(long long x) {
    std::vector<std::pair<long long, int>> f;
    for (long long p = 2; p * p <= x; p++) {
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

long long phi(long long n) {
    long long ans = n;
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

std::vector<long long> divisors(long long n) {
    std::vector<long long> d;
    for (long long x = 1; x * x <= n; x++) {
        if (n % x) continue;
        d.push_back(x);
        if (x * x != n) d.push_back(n / x);
    }
    std::sort(d.begin(), d.end());
    return d;
}

struct Comb {
    long long mod;
    std::vector<long long> fact, invfact;

    Comb(int n, long long mod): mod(mod), fact(n + 1, 1), invfact(n + 1, 1) {
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % mod;
        invfact[n] = inv_prime(fact[n], mod);
        for (int i = n; i; i--) invfact[i - 1] = invfact[i] * i % mod;
    }

    long long C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % mod * invfact[n - k] % mod;
    }
};

using Matrix = std::vector<std::vector<long long>>;

Matrix mul(Matrix a, Matrix b, long long mod) {
    int n = a.size();
    Matrix c(n, std::vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return c;
}

Matrix mpow(Matrix a, long long b, long long mod) {
    int n = a.size();
    Matrix ans(n, std::vector<long long>(n));
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

void ntt(std::vector<long long>& a, bool inv, long long mod = 998244353, long long root = 3) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = binpow_mod(root, (mod - 1) / len, mod);
        if (inv) wlen = inv_prime(wlen, mod);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = a[i + j + len / 2] * w % mod;
                a[i + j] = (u + v) % mod;
                a[i + j + len / 2] = (u - v + mod) % mod;
                w = w * wlen % mod;
            }
        }
    }
    if (inv) {
        long long ninv = inv_prime(n, mod);
        for (long long& x : a) x = x * ninv % mod;
    }
}

std::vector<long long> convolution_mod(std::vector<long long> a, std::vector<long long> b,
                                       long long mod = 998244353, long long root = 3) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1;
    if (std::min(a.size(), b.size()) < 64) {
        std::vector<long long> c(need);
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

std::vector<long long> poly_inv(const std::vector<long long>& a, int n, long long mod = 998244353, long long root = 3) {
    std::vector<long long> res(1, inv_prime(a[0], mod));
    while ((int)res.size() < n) {
        int m = res.size() * 2;
        std::vector<long long> cur(a.begin(), a.begin() + std::min((int)a.size(), m));
        std::vector<long long> prod = convolution_mod(convolution_mod(res, res, mod, root), cur, mod, root);
        res.resize(m);
        for (int i = 0; i < m; i++) {
            long long val = i < (int)prod.size() ? prod[i] : 0;
            res[i] = norm(2 * res[i] - val, mod);
        }
    }
    res.resize(n);
    return res;
}

long long lagrange(const std::vector<long long>& y, long long x, long long mod) {
    int n = y.size() - 1;
    if (x <= n) return norm(y[x], mod);
    std::vector<long long> pref(n + 2, 1), suf(n + 2, 1), fact(n + 1, 1), invfact(n + 1, 1);
    for (int i = 0; i <= n; i++) fact[i] = (i ? fact[i - 1] * i % mod : 1);
    invfact[n] = inv_prime(fact[n], mod);
    for (int i = n; i; i--) invfact[i - 1] = invfact[i] * i % mod;
    for (int i = 0; i <= n; i++) pref[i + 1] = pref[i] * norm(x - i, mod) % mod;
    for (int i = n; i >= 0; i--) suf[i] = suf[i + 1] * norm(x - i, mod) % mod;
    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        long long num = pref[i] * suf[i + 1] % mod;
        long long den = invfact[i] * invfact[n - i] % mod;
        if ((n - i) & 1) den = mod - den;
        ans = (ans + norm(y[i], mod) * num % mod * den) % mod;
    }
    return ans;
}

}
