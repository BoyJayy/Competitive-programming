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
void solve() {
    int n; cin >> n;
    ll cur = 0, f = 0, ans = 0;
    while (n --) {
        int s,t; cin >> t >> s;
        if (s > cur) {
            int d = s - cur;
            ans += d * t / 100ll+60ll*f;
            cur = s;
            f = 0;
            //debug(cur, ans);
        }else {
            f++;
        }
    }
    cout << cur << ' ' << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //int t;
    //cin >> t;
    //while (t--)
        solve();
}
