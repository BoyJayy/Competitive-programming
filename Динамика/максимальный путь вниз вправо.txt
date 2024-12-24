#include <bits/stdc++.h>
//#define int long long
#define endl "\n"
using namespace std;

void solve()
{
	int n, m; cin >> n >> m;
	vector <vector<int>> a(n, vector<int>(m));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];
	for (int i = 1; i < m; i++)
		a[0][i] = a[0][i - 1] + a[0][i];
	for (int i = 1; i < n; i++) {
		a[i][0] = a[i - 1][0] + a[i][0];
		for (int j = 1; j < m; j++)
			a[i][j] = a[i][j] + max(a[i][j - 1], a[i - 1][j]);
	}
	n--; m--;
	cout << a[n][m];
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}