///////////////////////////MACRO///////////////////////////////////////
#include <bits/stdc++.h>
#define all(a) (a).begin(), (a).end()
//#define endl "\n"
#define vec vector
//#define int long long
#define pii pair<int, int>
#define se second
#define fi first
#define pb push_back
#define maxel(v) *max_element(v.begin(), v.end())
#define minel(v) *min_element(v.begin(), v.end())
#define yes cout << "YES\n";
#define m1 cout << "-1\n";
#define no cout << "NO\n";
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
///////////////////////////MACRO///////////////////////////////////////
///////////////////////////GLOBAL VARIABLES///////////////////////////////////////
const ll INF = (1LL<<62);
const ll MOD = 1e9 + 7;
const ll MOD2 = 1e9 + 9;
const ll MOD3 = 998244353;
const string spi = "3.141592653589793238";
const ld pi = acos(-1);
const long double EPS = 1e-9;
const int MAXN = 100;
const int LOGN = __lg(MAXN) + 1;
vec<int> depth(MAXN, 0);
vec<pii> directions() { return {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; } //Top Right Bottom Left
vec<pii> directions2() { return {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1}}; } //8 directions
vec<pii> directions3() { return {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}}; } // Diagonals only
int up[LOGN][MAXN];
vector<int> tin(MAXN, -1), tout(MAXN, -1);
int t = 0;
vector<int> rb[MAXN];
///////////////////////////GLOBAL VARIABLES///////////////////////////////////////
///////////////////////////TEMPLATES///////////////////////////////////////
template <typename T>
void printa(const vec<T> a) {
    for (auto& p: a) {
        cout << p << ' ';
    }
    cout << endl;
}
template<typename T1, typename T2>
ostream& operator << (ostream& out, const pair<T1, T2>& p){
    return out << "(" << p.first << ", " << p.second << ")";
}

template<typename T>
ostream& operator << (ostream& out, const vector<T>& v){
    out << "[";
    for (int i = 0; i < v.size(); i++){
        if (i) out << ", ";
        out << v[i];
    }
    out << "]";
    return out;
}

template<typename T1, typename T2>
istream& operator >> (istream& in, pair<T1, T2>& p){
    in >> p.first;
    in >> p.second;
    return in;
}

template<typename T>
istream& operator >> (istream& in, vector<T>& v){
    for (auto& e : v) in >> e;
    return in;
}
template <typename T>
void printrb(vector<T>* rb, int n) {
    for (int u = 0; u < n; ++u) {
        for (const T& v : rb[u]) {
            cout << u << " -> " << v << '\n';
        }
    }
}
template <typename T>
void print2d(const vec<vec<T>> &vec) {
    for (const auto &row : vec) {
        for (const auto &i : row) {
            cout << i << " ";
        }
        cout << endl;
    }
}
///////////////////////////TEMPLATES///////////////////////////////////////
///////////////////////////FUNCS///////////////////////////////////////
bool pr(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}
ll gcd(ll a, ll b){ return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b) * b); }
ll modpow(ll x, ll y, ll p) {
    ll res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0) {
        if (y & 1) res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
vector<int> sieve(int n) {
    int *arr = new int[n + 1]();
    vector<int> vect;
    for (int i = 2; i <= n; i++)
        if (arr[i] == 0) {
            vect.push_back(i);
            for (int j = 2 * i; j <= n; j += i)
                arr[j] = 1;
        }
    return vect;
}
bool ances(int u, int v) {
    return tin[u] <= tin[v] && tin[v] < tout[u];
}
void dfsUPS(int v) { //offline
    for (int i = 1; i < LOGN; i++) {
        if (up[v][i - 1] != -1 && up[up[v][i - 1]][i - 1] != -1)
            up[v][i] = up[up[v][i - 1]][i - 1];
    }
    tin[v] = t++;
    for (auto& u: rb[v]) {
        if (u == up[v][0]) continue;
        up[u][0] = v;
        dfsUPS(u);
    }
    tout[v] = t;
}

int lca1(int u, int v) { //offline lca method
    if (ances(u, v)) return u;
    if (ances(v, u)) return v;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (up[v][i] != -1 && !ances(up[v][i], u)) {
            v = up[v][i];
        }
    }
    return up[v][0];
}
void binup(int v, int pred) {
    up[0][v] = pred;
    for (int i = 1; i < LOGN; i++) {
        if (up[i-1][v] != -1 && up[i-1][up[i-1][v]] != -1)
            up[i][v] = up[i-1][up[i-1][v]];
    }
    depth[v] = depth[pred] + 1;
}

int lca(int u, int v) { //Online lca method
    if (depth[u] < depth[v]) swap(u, v);
    // depth[u] >= depth[v]
    for (int i = LOGN - 1; i >= 0; i--) {
        if (up[i][u] != -1 && depth[v] <= depth[up[i][u]]) {
            u = up[i][u];
        }
    }
    if (u == v) return v;
    for (int i = LOGN - 1; i >= 0; i--) {
        int dx = up[i][u];
        int dy = up[i][v];
        if (dx == dy) continue;
        u = dx;
        v = dy;
    }
    return up[0][u];
}
void clearbase() {
    for (int i = 0; i < MAXN; i++) {
        rb[i].clear();
        depth[i] = 0;
    }
    tin.assign(MAXN, -1), tout.assign(MAXN, -1);
}
void yn(bool condition) {
    if (condition) {
        yes;
    } else {
        no;
    }
}
string toLower(const string &s) {string res = s;transform(res.begin(), res.end(), res.begin(), ::tolower);return res;}
string toUpper(const string &s) {string res = s;transform(res.begin(), res.end(), res.begin(), ::toupper);return res;}
///////////////////////////FUNCS///////////////////////////////////////
///////////////////////////STRUCTS///////////////////////////////////////
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

struct ST {
	int n;
	vec<vec<ll>> stMin, stMax, stGcd, stAnd, stOr;
	vec<int> lg;
	ST(const vec<ll>& a) {
		n = a.size();
		lg.resize(n + 1);
		for (int i = 2; i <= n; i++)
			lg[i] = lg[i / 2] + 1;
		int K = lg[n] + 1;
		stMin.assign(n, vec<ll>(K));
		stMax.assign(n, vec<ll>(K));
		stGcd.assign(n, vec<ll>(K));
		stAnd.assign(n, vec<ll>(K));
		stOr.assign(n, vec<ll>(K));
		for (int i = 0; i < n; i++){
			stMin[i][0] = a[i];
			stMax[i][0] = a[i];
			stGcd[i][0] = a[i];
			stAnd[i][0] = a[i];
			stOr[i][0] = a[i];
		}
		for (int j = 1; j < K; j++)
			for (int i = 0; i + (1 << j) <= n; i++){
				stMin[i][j] = min(stMin[i][j - 1], stMin[i + (1 << (j - 1))][j - 1]);
				stMax[i][j] = max(stMax[i][j - 1], stMax[i + (1 << (j - 1))][j - 1]);
				stGcd[i][j] = gcd(stGcd[i][j - 1], stGcd[i + (1 << (j - 1))][j - 1]);
				stAnd[i][j] = stAnd[i][j - 1] & stAnd[i + (1 << (j - 1))][j - 1];
				stOr[i][j] = stOr[i][j - 1] | stOr[i + (1 << (j - 1))][j - 1];
			}
	}
	ll getmin(int L, int R) {
		int j = lg[R - L + 1];
		return min(stMin[L][j], stMin[R - (1 << j) + 1][j]);
	}
	ll getmax(int L, int R) {
		int j = lg[R - L + 1];
		return max(stMax[L][j], stMax[R - (1 << j) + 1][j]);
	}
	ll getgcd(int L, int R) {
		int j = lg[R - L + 1];
		return gcd(stGcd[L][j], stGcd[R - (1 << j) + 1][j]);
	}
	ll getand(int L, int R) {
		int j = lg[R - L + 1];
		return stAnd[L][j] & stAnd[R - (1 << j) + 1][j];
	}
	ll getor(int L, int R) {
		int j = lg[R - L + 1];
		return stOr[L][j] | stOr[R - (1 << j) + 1][j];
	}
};
///////////////////////////STRUCTS///////////////////////////////////////
void solve() {
    vec<vec<int>> a(2, vec<int>(2));
    cin >> a;
    cout << a;
}
signed main() {
    //ll inv2 = modexp(2, MOD - 2), inv4 = (inv2 * inv2) % MOD;
    #ifdef LOCAL
        freopen("lca.in", "r", stdin);
        freopen("lca.out", "w", stdout);
    #endif // LOCAL
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //int tests; cin >> tests;
    //for (int i = 0; i < tests; ++i)
    solve();
}
