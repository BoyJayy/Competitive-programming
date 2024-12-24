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
 
void solve() {
    int n, m, s; cin >> n >> m >> s;
    vec<pii> rb[n];
    for (int i = 0; i < m; i++) {
        int s, t, c; cin >> s >> t >> c;
        //s--; t--;
        rb[s].push_back({t, c});
        rb[t].push_back({s, c});
    }
    int dist[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    set<pii> st; dist[s] = 0;
    st.insert({0, s});
    while (!st.empty()) {
        auto it = st.begin();
        int v = (*it).se;
        st.erase(it);
        for (pii p: rb[v]) {
            int ne = p.first;
            int c = p.second;
            if (dist[ne] > dist[v] + c) {
                dist[ne] = dist[v] + c;
                st.insert({dist[ne], ne});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << (dist[i] == INF ? 2009000999 : dist[i]) << " ";
    }
    cout << endl;
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //int t; cin >> t;
    //for (int i = 0; i < t; ++i)
        solve();
}