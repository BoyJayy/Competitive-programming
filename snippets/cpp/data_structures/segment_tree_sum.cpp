struct SegTreeSum {
    int n = 1;
    vector<long long> t;

    SegTreeSum() {}

    SegTreeSum(const vector<long long>& a) {
        build(a);
    }

    void build(const vector<long long>& a) {
        while (n < a.size()) n <<= 1;
        t.assign(2 * n, 0);
        for (int i = 0; i < a.size(); i++) t[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }

    void set_val(int pos, long long val) {
        pos += n;
        t[pos] = val;
        for (pos >>= 1; pos; pos >>= 1) t[pos] = t[pos << 1] + t[pos << 1 | 1];
    }

    long long sum(int l, int r) {
        long long ans = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += t[l++];
            if (r & 1) ans += t[--r];
        }
        return ans;
    }
};
