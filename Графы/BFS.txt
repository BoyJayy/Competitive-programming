#include <bits/stdc++.h>
//#define int long long
#define endl "\n"
#define vec vector
#define ll long long
#define pb(x) push_back(x)
#define INF INT_MAX

using namespace std;

const int MAXN = 100;
int matr[MAXN][MAXN];

void solve() {
    int n; cin >> n;
    vec<int> rb[MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matr[i][j];
            if (matr[i][j] == 1) { 
                rb[i].push_back(j);
            }
        }
    }
    int s, f; cin >> s >> f;
    s--; f--;
    int dist[MAXN];
    vec<int> now = {s}, next;
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    
    while (!now.empty() && !next.empty()) {
        for (int i = 0; i < now.size(); i++) {
            int v = now[i];
            for (int j = 0; j < rb[v].size(); j++) {
                int u = rb[v][j];
                if (dist[u] == INF) {
                    next.pb(u);
                    dist[u] = dist[v] + 1;
                }
            }
        }
        now = next;
        next.clear();
    }
    cout << dist[f] << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //int t; cin >> t;
    //for (int i = 0; i < t; ++i)
    solve();
}     