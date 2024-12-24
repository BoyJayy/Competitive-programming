#include <bits/stdc++.h>
//#define int long long
#define endl "\n"
#define vec vector
#define ll long long
//#define pb(x) push_back(x)
#define INF INT_MAX
#define se second
#define fi first
#define pii pair<int,int>

using namespace std;

struct Tree {
    vec<int> nodes;
    int size = 1;
    Tree(){};
    Tree (vec<int>& a) {
        while (size < a.size()) size *= 2;
        nodes.resize(size * 2, 0);
        for (int i = 0; i < a.size(); i++) {
            nodes[i + size] = a[i];
        }
        for (int i = size - 1; i >= 1; i--) {
            nodes[i] = nodes[i * 2] + nodes[i * 2 + 1];
        }
    }
    int get_sum(int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            return nodes[now];
        }
        if (l >= rq || r <= lq) {
            return 0;
        }
        int r_s = get_sum(now * 2 + 1, (l + r) / 2, r, lq, rq);
        int l_s = get_sum(now * 2, l, (l + r) / 2, lq, rq);
        return r_s + l_s;
    }
    void update(int num, int now, int l, int r, int lq, int rq) {
        if (lq <= l && rq >= r) {
            nodes[now] = num;
            return;
        }
        if (l >= rq || r <= lq) {
            return;
        }
        update(num, now * 2 + 1, (l + r) / 2, r, lq, rq);
        update(num, now * 2, l, (l + r) / 2, lq, rq);
        nodes[now] = nodes[now * 2] + nodes[now * 2 + 1];
    }
};

void solve() {
    int n; cin >> n;
    vec<int> a(n);
    for (auto& it: a) cin >> it;
    Tree tree(a);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //int t; cin >> t;
    //for (int i = 0; i < t; ++i)
    solve();
}