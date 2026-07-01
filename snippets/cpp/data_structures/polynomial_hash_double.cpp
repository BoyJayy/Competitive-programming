struct Hash2 {
    const int M1 = 1'000'000'007;
    const int M2 = 1'000'000'009;
    int n, B;
    vector<int> p1, p2, h1, h2;

    Hash2() {}
    Hash2(const string& s, int base = 911382323) {
        build(s, base);
    }

    void build(const string& s, int base = 911382323) {
        n = s.size();
        B = base;
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            p1[i] = (long long)p1[i - 1] * B % M1;
            p2[i] = (long long)p2[i - 1] * B % M2;
            h1[i] = ((long long)h1[i - 1] * B + (unsigned char)s[i - 1] + 1) % M1;
            h2[i] = ((long long)h2[i - 1] * B + (unsigned char)s[i - 1] + 1) % M2;
        }
    }

    pair<int, int> get(int l, int r) {
        int x1 = (h1[r + 1] - (long long)h1[l] * p1[r - l + 1]) % M1;
        int x2 = (h2[r + 1] - (long long)h2[l] * p2[r - l + 1]) % M2;
        if (x1 < 0) x1 += M1;
        if (x2 < 0) x2 += M2;
        return {x1, x2};
    }

    pair<int, int> concat(pair<int, int> a, pair<int, int> b, int len) {
        int x1 = ((long long)a.first * p1[len] + b.first) % M1;
        int x2 = ((long long)a.second * p2[len] + b.second) % M2;
        return {x1, x2};
    }

    int lcp(int i, int j) {
        int l = 0, r = min(n - i, n - j);
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (get(i, i + m - 1) == get(j, j + m - 1)) l = m;
            else r = m - 1;
        }
        return l;
    }
};
