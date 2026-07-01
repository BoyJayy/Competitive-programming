template <typename T>
struct Fenw {
    int n;
    vector<T> t;

    Fenw(int n = 0): n(n), t(n + 1) {}

    void add(int i, T x) {
        for (++i; i <= n; i += i & -i) t[i] += x;
    }

    T sum(int i) {
        T ans = 0;
        for (++i; i > 0; i -= i & -i) ans += t[i];
        return ans;
    }

    T query(int l, int r) {
        return sum(r) - (l ? sum(l - 1) : 0);
    }
};
