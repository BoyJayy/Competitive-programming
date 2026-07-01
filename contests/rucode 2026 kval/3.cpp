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
const ld inf = 1e9 + 5;
#define DEBUG 1
#if DEBUG
#define del cout << '\n'
#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
template <class X, class Y>
ostream& operator<<(ostream& os, pair<X, Y> const& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template <class Ch, class Tr, class Container>
basic_ostream<Ch, Tr>& operator<<(basic_ostream<Ch, Tr>& os, Container const& x) {
    int i = 0, n = (int)distance(x.begin(), x.end());
    os << "{ ";
    for (const auto& y : x) os << y << (++i < n ? ", " : "");
    return os << " }";
}
template <typename... Args>
void _debug(const char* s, Args&&... args) {
    cout << "{ ";
    size_t i = 0, cnt = 0, n = sizeof...(args);
    auto next = [&]() {
        while (s[i] && (s[i] == ' ' || s[i] == ',')) ++i;
        size_t st = i;
        while (s[i] && s[i] != ',') ++i;
        return string(s + st, i - st);
    };
    auto dummy = {(cout << next() << ": " << args << (++cnt < n ? ", " : ""), 0)...};
    (void)dummy;
    cout << " }" << '\n';
}
#else
#define del
#define debug(...)
#endif
//pr = 5 => 2^5 = 32
vec<string>  p = {
    "MWSOctapi",
    "MWSAI",
    "MWSTables",
    "MWSData",
    "MWSCloudPlatform"
};
int id(char c) {
    if (c>='a'&&c<='z') return c-'a';
    return c-'A'+26;
}
/*
 * Rucode
 * R u c o d e cant for MWSAI etc*/

/* we need to understand that we just need to find count of words we can recreate with letters we have in query*/
int a[6][100];
void solve() {
    int n; cin >> n;
    //we have 32 (1<<5) vars so need to brute them all and check thats all
    while (n--) {
        string s; cin >> s;
        int cnt[100] = {};
        for (auto& c: s) cnt[id(c)]++;
        int k = 0, ways = 0;
        int k1 = 0, cmin =inf;
        for (int mask = 0; mask < (1<<5); mask++) {
            int need[100] = {};
            int b = 0;
            for (int i = 0; i < 5;i++) {

                if (mask & (1<<i)) {
                    b++;
                    for (int j = 0; j < 52; j++) {
                        need[j] += a[i][j];
                    }
                }

            }
            //debug(k,ways,k1,cmin);
            bool ok =1;
            //check if we have enough letters
            for (int j = 0; j < 52; j++) {
                if (need[j] > cnt[j]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                if (b >  k) {
                    k = b;
                    ways =1;
                } else if (b==k) {
                    ways++;
                }
            }
            ok = 1;
            //debug(k,ways,k1,cmin);
            int cur = 0;
            for (int j = 0; j < 26; j++) {
                int l = cnt[j];
                int u = cnt[j+26];
                int nl = need[j];
                int nu = need[j+26];
                if (nl + nu > l + u) {
                    ok = 0;
                    break;
                }
                cur += max(0, nl-l);
                cur += max(0, nu-u);

            }
            //debug(k,ways,k1,cmin);
            if (ok) {
                if (b > k1) {
                    k1 = b;
                    cmin = cur;
                } else if (b==k1)  {
                    cmin = min(cmin, cur);
                }
            }
            //debug(k,ways,k1,cmin);
        }
        cout << k << ' ' << ways << ' ' << k1 << ' ' << cmin << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //int t;
    //cin >> t;
    for (int i = 0; i < 5; i++) {
        for (auto& c : p[i]) {
            a[i][id(c)]++;
        }
    }
    //while (t--)
        solve();
}

