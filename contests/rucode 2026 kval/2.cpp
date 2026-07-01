#include <bits/stdc++.h>
/*#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")
#pragma comment(linker, "/STACK:367772160")*/
using namespace std;
#define all(a) (a).begin(), (a).end()
#define endl "\n"
#define vec vector
#define pii pair<int, int>
#define se second
#define fi first
#define pb push_back
#define maxel(v) *max_element(v.begin(), v.end())
#define minel(v) *min_element(v.begin(), v.end())
#define yes cout << "YES\n";
#define no cout << "NO\n";
typedef __int128 int128;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ll mod = 1e9+7;
const ll mod2 = 1e9 + 9;
const ll mod3 = 998244353;
const double pi = 3.141592653589793238;
const long double EPS = 1e-9;
const int MAXN = 2e5 + 5 ;
const ld inf = 1e200;


bool check(int k, string s) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        int d = s[n-i-1] - '0';
        int r = i;
        if (d >= 1 && d <=3) {
            if(k<2*r+1) return false;
        } else if (d >= 4 &&d<=8) {
            if ((k<2*r+2)) return false;
        } else if (d==9) {
            if (k <2*r+3) return false;
        }
    }
    return true;
}

void solve() {
    int q;
    cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t &1) {
            int k ; cin >> k;
            int m =(k + 1)/2;
            if (k%2) cout << 3 ;
            else cout << 8 ;
            for (int i  =1 ; i < m; i++) {
                cout << 9;
            }
            cout << endl;
        } else {
            string s; cin >> s;
            int n = s.size();
            int l = 1, r = 30005;
            while (l < r) {
                int mid = (l+r) >>1;
                if (check(mid, s)) r= mid;
                else l = mid+1;
            }
            cout << l << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

   // int t;
    //cin >> t;

    //while (t--)
        solve();
}
