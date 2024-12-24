struct fenwx {
    vc<int> t;
 
    fenwx(int n) : t(n + 5, -2e9 - 2) {
    }
 
    void upd(int i, int x) { for (++i; i < t.size(); i += i & -i) t[i] = max(t[i], x); }
 
    int get(int i) {
        int ans = -2e9;
        for (++i; i; i -= i & -i) ans = max(ans, t[i]);
        return ans;
    }
};