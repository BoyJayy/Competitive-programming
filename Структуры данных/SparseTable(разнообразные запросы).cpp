struct ST {
    int n;
    vec<vec<ll>> stMin, stMax, stGcd, stAnd, stOr;
    vec<int> lg;
    ST(const vec<ll>& a) {
        n = a.size();
        lg.resize(n + 1);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        int K = lg[n] + 1;
        stMin.assign(n, vec<ll>(K));
        stMax.assign(n, vec<ll>(K));
        stGcd.assign(n, vec<ll>(K));
        stAnd.assign(n, vec<ll>(K));
        stOr.assign(n, vec<ll>(K));
        for (int i = 0; i < n; i++){
            stMin[i][0] = a[i];
            stMax[i][0] = a[i];
            stGcd[i][0] = a[i];
            stAnd[i][0] = a[i];
            stOr[i][0] = a[i];
        }
        for (int j = 1; j < K; j++)
            for (int i = 0; i + (1 << j) <= n; i++){
                stMin[i][j] = min(stMin[i][j - 1], stMin[i + (1 << (j - 1))][j - 1]);
                stMax[i][j] = max(stMax[i][j - 1], stMax[i + (1 << (j - 1))][j - 1]);
                stGcd[i][j] = gcd(stGcd[i][j - 1], stGcd[i + (1 << (j - 1))][j - 1]);
                stAnd[i][j] = stAnd[i][j - 1] & stAnd[i + (1 << (j - 1))][j - 1];
                stOr[i][j] = stOr[i][j - 1] | stOr[i + (1 << (j - 1))][j - 1];
            }
    }
    ll getmin(int L, int R) {
        int j = lg[R - L + 1];
        return min(stMin[L][j], stMin[R - (1 << j) + 1][j]);
    }
    ll getmax(int L, int R) {
        int j = lg[R - L + 1];
        return max(stMax[L][j], stMax[R - (1 << j) + 1][j]);
    }
    ll getgcd(int L, int R) {
        int j = lg[R - L + 1];
        return gcd(stGcd[L][j], stGcd[R - (1 << j) + 1][j]);
    }
    ll getand(int L, int R) {
        int j = lg[R - L + 1];
        return stAnd[L][j] & stAnd[R - (1 << j) + 1][j];
    }
    ll getor(int L, int R) {
        int j = lg[R - L + 1];
        return stOr[L][j] | stOr[R - (1 << j) + 1][j];
    }
};
