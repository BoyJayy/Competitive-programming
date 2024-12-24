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

void dfs(int now, bool* visited, vec<int>* rb) {
	visited[now] = 1;
	edges.pb(now);
	for (int ne : rb[now]) {
		if (!visited[ne]) {
			dfs(ne, visited, rb);
		}
	}
}

void solve() {
	int n, m; cin >> n >> m;
	vec<int> rb[n];
	for (int i = 0; i < m; i++) {
		int s, f; cin >> s >> f;
		s--; f--;
		rb[s].pb(f);
		rb[f].pb(s);
	}
	bool visited[n]{};
	vec<vec<int>> ans;
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			dfs(i, visited, rb);
			ans.pb(edges);
			edges.clear();
		}
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].size() << endl;
		for (int j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j] + 1 << " ";
		}
		cout << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//int t; cin >> t;
	//for (int i = 0; i < t; ++i)
	solve();
}