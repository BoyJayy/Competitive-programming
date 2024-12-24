#include <bits/stdc++.h>
//#define int long long
#define endl "\n"
#define vec vector
#define ll long long
#define pb(x) push_back(x)
#define INF INT_MAX
#define se second
#define fi first
#define pii pair<int,int>

using namespace std;

vec<int> edges;


void solve() {
    int n; cin >> n;
    vec<vec<int>> a(n, vec<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << ' ';
            }
            cout << endl;
        }
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //int t; cin >> t;
    //for (int i = 0; i < t; ++i)
        solve();
}