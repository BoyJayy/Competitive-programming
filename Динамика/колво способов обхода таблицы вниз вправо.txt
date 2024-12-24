#include <bits/stdc++.h>
//#define int long long
#define endl "\n"
using namespace std;

void solve()
{
	int n, m; cin >> n >> m;
	vector <vector<int>> a(n, vector<int>(m));
	for (int i = 0; i < m; i++)
		a[0][i] = 1;
	for (int i = 1; i < n; i++)
	{
		a[i][0] = 1;
		for (int j = 1; j < m; j++)
			a[i][j] = a[i - 1][j] + a[i][j - 1];
	}
	n--; m--;
	cout << a[n][m];
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}