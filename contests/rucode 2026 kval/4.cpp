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
const int MAXN = 1e6 + 5 ;
const ld inf = 1e200;

// ill first implement O(n^2) solv after try to nlogn
//n^2 :
//in that version we just calc by k and c(char 0 or 1 with what we start) and after that we check
//if we have enough chars to make k and they are valid
int n;
string s;
int calc(int k , int c) {
    int cnt = 0;
    int cur = 0;
    for (int i =0; i < n; i++) {
        if (s[i]-'0' == c) {
            cur++;
            if (cur == k) {
                cnt ++;
                cur = 0;
                c^=1;
            }
        }
    }
    if (cnt < 2) return 0;
    else return cnt  *k;
}
void solven2() {
    cin >>  n>> s;
    int z =0, o =0;
    for (auto & c: s) {
        if  (c == '0') z++;
        else o++;
    }
    int ans = 0;
    int best = 1;
    for (int i = 1; i < min(z,o); i++) {
        int cur = max(calc(i,0), calc(i,1));
        if (cur > ans) {
            ans = cur;
            best = i;
        }
    }
    cout << ans << ' '  << best << endl;
}

//nlogn:
/* ill implement func get() - will return next consecutive numbers of 0 or 1 in s
 * p - stores indexes of all 0 and 1 */
//for instance if we have s = 0011100 so the p[0] = 1 2 6 7 etc
vec<int> p[2];
//pref - how much of c numbers have been from 1 to i
int pref[2][MAXN];
int sz[2];
int get(int x, int c, int k) {
    //x - pos in what we stay now
    int id = pref[c][x] + k -1;
    // 3 4 5 => id = 0 + 2 - 1 for get(2,1,2)
    if (id >= sz[c]) return -67; //sixseven
    return p[c][id];
}
int calcsmart(int k , int c) {
    int x= 0;
    int cnt = 0;
    while(1) {
        x = get(x,c,k);
        if (x == -67) break;
        cnt++;
        c^=1;

    }
    if (cnt < 2) return 0;
    return cnt*k;
}
void solve(){
    cin >> n >> s;
    s = " " + s;
    for (int i = 1; i <= n; i++) {
        pref[0][i] = pref[0][i-1];
        pref[1][i] = pref[1][i-1];
        int c =s[i]-'0';
        p[c].pb(i);
        pref[c][i]++;
    }
    sz[0] = p[0].size();
    sz[1] = p[1].size();
    int ans = 0;
    int best = 1;
    for (int  k = 1; k <= min(sz[0],sz[1]); k++) {
        int cur = max(calcsmart(k,0), calcsmart(k,1));
        if (cur > ans) {
            ans = cur;
            best = k;
        }
    }
    cout << ans << ' '  << best << endl;
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

