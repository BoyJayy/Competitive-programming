using V1 = vector<long long>;
using V2 = vector<V1>;
using V3 = vector<V2>;
using V4 = vector<V3>;
using V5 = vector<V4>;

V5 make_5d(int a, int b, int c, int d, int e, long long val = 0) {
    return V5(a, V4(b, V3(c, V2(d, V1(e, val)))));
}

void build_5d_prefix(const V5& a, V5& pref, int n1, int n2, int n3, int n4, int n5) {
    for (int i1 = 0; i1 < n1; i1++)
        for (int i2 = 0; i2 < n2; i2++)
            for (int i3 = 0; i3 < n3; i3++)
                for (int i4 = 0; i4 < n4; i4++)
                    for (int i5 = 0; i5 < n5; i5++)
                        pref[i1 + 1][i2 + 1][i3 + 1][i4 + 1][i5 + 1] = a[i1][i2][i3][i4][i5];

    for (int i1 = 1; i1 <= n1; i1++)
        for (int i2 = 1; i2 <= n2; i2++)
            for (int i3 = 1; i3 <= n3; i3++)
                for (int i4 = 1; i4 <= n4; i4++)
                    for (int i5 = 1; i5 <= n5; i5++)
                        pref[i1][i2][i3][i4][i5] += pref[i1 - 1][i2][i3][i4][i5];

    for (int i1 = 1; i1 <= n1; i1++)
        for (int i2 = 1; i2 <= n2; i2++)
            for (int i3 = 1; i3 <= n3; i3++)
                for (int i4 = 1; i4 <= n4; i4++)
                    for (int i5 = 1; i5 <= n5; i5++)
                        pref[i1][i2][i3][i4][i5] += pref[i1][i2 - 1][i3][i4][i5];

    for (int i1 = 1; i1 <= n1; i1++)
        for (int i2 = 1; i2 <= n2; i2++)
            for (int i3 = 1; i3 <= n3; i3++)
                for (int i4 = 1; i4 <= n4; i4++)
                    for (int i5 = 1; i5 <= n5; i5++)
                        pref[i1][i2][i3][i4][i5] += pref[i1][i2][i3 - 1][i4][i5];

    for (int i1 = 1; i1 <= n1; i1++)
        for (int i2 = 1; i2 <= n2; i2++)
            for (int i3 = 1; i3 <= n3; i3++)
                for (int i4 = 1; i4 <= n4; i4++)
                    for (int i5 = 1; i5 <= n5; i5++)
                        pref[i1][i2][i3][i4][i5] += pref[i1][i2][i3][i4 - 1][i5];

    for (int i1 = 1; i1 <= n1; i1++)
        for (int i2 = 1; i2 <= n2; i2++)
            for (int i3 = 1; i3 <= n3; i3++)
                for (int i4 = 1; i4 <= n4; i4++)
                    for (int i5 = 1; i5 <= n5; i5++)
                        pref[i1][i2][i3][i4][i5] += pref[i1][i2][i3][i4][i5 - 1];
}

long long sum_5d(const V5& pref, int l1, int l2, int l3, int l4, int l5,
                 int r1, int r2, int r3, int r4, int r5) {
    long long ans = 0;
    for (int mask = 0; mask < 32; mask++) {
        int i1 = (mask & 1) ? l1 : r1 + 1;
        int i2 = (mask & 2) ? l2 : r2 + 1;
        int i3 = (mask & 4) ? l3 : r3 + 1;
        int i4 = (mask & 8) ? l4 : r4 + 1;
        int i5 = (mask & 16) ? l5 : r5 + 1;
        if (__builtin_popcount((unsigned)mask) % 2 == 0) ans += pref[i1][i2][i3][i4][i5];
        else ans -= pref[i1][i2][i3][i4][i5];
    }
    return ans;
}
