using u128 = __uint128_t;
using u64 = uint64_t;

u64 mul_mod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 pow_mod(u64 a, u64 n, u64 mod) {
    u64 ans = 1;
    while (n) {
        if (n & 1) ans = mul_mod(ans, a, mod);
        a = mul_mod(a, a, mod);
        n >>= 1;
    }
    return ans;
}

bool is_prime_u64(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull, 19ull, 23ull, 29ull, 31ull, 37ull}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    auto check = [&](u64 a) {
        if (a % n == 0) return true;
        u64 x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (u64 i = 1; i < s; i++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };
    for (u64 a : {2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull}) {
        if (a >= n) continue;
        if (!check(a)) return false;
    }
    return true;
}

mt19937_64 pollard_rng(chrono::steady_clock::now().time_since_epoch().count());

u64 pollard(u64 n) {
    if ((n & 1) == 0) return 2;
    uniform_int_distribution<u64> dx(2, n - 2), dc(1, n - 1);
    while (true) {
        u64 x = dx(pollard_rng), y = x, c = dc(pollard_rng), d = 1;
        auto f = [&](u64 v) { return (mul_mod(v, v, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = gcd(x > y ? x - y : y - x, n);
        }
        if (d != n) return d;
    }
}

void factor(u64 n, map<u64, int>& mp) {
    if (n == 1) return;
    if (is_prime_u64(n)) {
        mp[n]++;
        return;
    }
    u64 d = pollard(n);
    factor(d, mp);
    factor(n / d, mp);
}
