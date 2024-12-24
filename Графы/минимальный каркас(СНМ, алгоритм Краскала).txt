#include <bits/stdc++.h>
//#define int long long
#define endl "\n"
#define se second
#define fi first
#define vec vector
#define pii pair<int, int>
#define ll long long
 
using namespace std;
 
struct DSU{
    vec<int> leads, sizes;
    DSU(){};
    DSU(int n) {
        for (int i = 0; i < n; i++) {
            leads.push_back(i);
            sizes.push_back(1);
        }
    }
    int get_lead(int x) {
        if (leads[x] == x) return x;
        return leads[x] = get_lead(leads[x]);
    }
    bool check(int x, int y) {
        return get_lead(x) == get_lead(y);
    }
    void unite(int x, int y) {
        x = get_lead(x);
        y = get_lead(y);
        if (sizes[x] < sizes[y]) swap(x, y);
        leads[y] = x;
        sizes[x] += sizes[y];
    }
};
 
void solve() {
    int n, m; cin >> n >> m;
    vec<int> rb[m];
    for (int i = 0; i < m; i++) {
        int s,f,c; cin >> s >> f >> c;
        s--; f--;
        rb[i] = {c, s, f};
    }
    sort(rb, rb + m);
    DSU dsu(n);
    int c = 0;
    for (int i = 0; i < m; i++) {
        if (!dsu.check(rb[i][1], rb[i][2])) {
            dsu.unite(rb[i][1], rb[i][2]);
            c += rb[i][0];
        }
    }
    cout << c;
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //int t; cin >> t;
    //for (int i = 0; i < t; ++i)
    solve();
}