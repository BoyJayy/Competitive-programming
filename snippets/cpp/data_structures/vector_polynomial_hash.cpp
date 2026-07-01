template <typename T>
struct VecHash {
    const int MOD = 1'000'000'007;
    int n, B;
    vector<int> p, h;

    VecHash() {}
    VecHash(const vector<T>& a, int base = 911382323) {
        build(a, base);
    }

    void build(const vector<T>& a, int base = 911382323) {
        n = a.size();
        B = base;
        p.assign(n + 1, 1);
        h.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            p[i] = (long long)p[i - 1] * B % MOD;
            int val = (a[i - 1] % MOD + MOD) % MOD;
            h[i] = ((long long)h[i - 1] * B + val + 1) % MOD;
        }
    }

    int get(int l, int r) {
        int x = (h[r + 1] - (long long)h[l] * p[r - l + 1]) % MOD;
        if (x < 0) x += MOD;
        return x;
    }

    int concat(int left, int right, int len) {
        return ((long long)left * p[len] + right) % MOD;
    }
};
