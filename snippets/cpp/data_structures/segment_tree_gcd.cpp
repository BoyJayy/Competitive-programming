template <typename T>
struct SegTreeGcd {
    int n;
    vector<T> t;

    SegTreeGcd(const vector<T>& a = {}) {
        if (!a.empty()) build(a);
    }

    void build(const vector<T>& a) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.assign(2 * n, T());
        for (int i = 0; i < (int)a.size(); i++) t[i + n] = a[i];
        for (int i = n - 1; i; i--) t[i] = gcd(t[i << 1], t[i << 1 | 1]);
    }

    void set_val(int pos, T x) {
        pos += n;
        t[pos] = x;
        for (pos >>= 1; pos; pos >>= 1) t[pos] = gcd(t[pos << 1], t[pos << 1 | 1]);
    }

    T get(int l, int r) {
        T ans = T();
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = gcd(ans, t[l++]);
            if (r & 1) ans = gcd(ans, t[--r]);
        }
        return ans;
    }
};
