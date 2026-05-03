
/*
  _______                   _       _            
 |__   __|                 | |     | |           
    | | ___ _ __ ___  _ __ | | __ _| |_ ___  ___ 
    | |/ _ \ '_ ` _ \| '_ \| |/ _` | __/ _ \/ __|
    | |  __/ | | | | | |_) | | (_| | ||  __/\__ \
    |_|\___|_| |_| |_| .__/|_|\__,_|\__\___||___/
                     | |                         
                     |_|                         
*/
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
const ll mod = 676767677;
const ll mod2 = 1e9 + 9;
const ll mod3 = 998244353;
const double pi = 3.141592653589793238;
const long double EPS = 1e-9;
const int MAXN = 3e5 + 5 ;
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
template <typename T>
ostream& operator<< (ostream &os, pair<T, T>& a){
    return os << a.fi << " " << a.se;
}
template <typename T>
istream& operator>> (istream& in, pair<T, T>& a){
    in >> a.fi >> a.se;
    return in;
}
template <typename T>
ostream& operator<< (ostream &os, vector<T>& a){
    for ( T& x : a) os << x << " ";
    return os;
}template <typename T>
istream& operator>> (istream& in,  vector<T>& a){
    for ( T& x : a) in >> x;
    return in;
}
template <typename T>
ostream& operator<< (ostream &os, set<T>& a){
    for ( T& x : a) os << x << " ";
    return os;
}
template <typename T>
ostream& operator<< (ostream &os, map<T, T>& a){
    for ( auto& x : a) os << x.fi << " " << x.se << endl;
    return os;
}
/*
***********************************************
***********************************************
***********************************************
***********************************************
***********************************************
*/



/*
   _____       _       _   _             
  / ____|     | |     | | (_)            
 | (___   ___ | |_   _| |_ _  ___  _ __  
  \___ \ / _ \| | | | | __| |/ _ \| '_ \ 
  ____) | (_) | | |_| | |_| | (_) | | | |
 |_____/ \___/|_|\__,_|\__|_|\___/|_| |_|             
*/

void solve() {
    int n; cin >> n;
    vec<int> a(n); cin >> a;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t; 
    while (t--) 
        solve();
}
