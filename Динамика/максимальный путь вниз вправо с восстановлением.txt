#include <bits/stdc++.h>
//#define int long long
#define endl "\n"

using namespace std;

void solve() {
	int n, m; cin >> n >> m;
	int a[n][m];
	char pred[n][m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i < m; i++) {
		a[0][i] += a[0][i - 1];
		pred[0][i] = 'R';
	}
	for (int i = 1; i < n; i++)
	{
		a[i][0] = a[i - 1][0] + a[i][0];
		pred[i][0] = 'D';
		for (int j = 1; j < m; j++)
		{
			if (a[i - 1][j] > a[i][j - 1]) {
				a[i][j] = a[i][j] + a[i - 1][j];
				pred[i][j] = 'D';
			}
			else {
				a[i][j] = a[i][j] + a[i][j - 1];
				pred[i][j] = 'R';
			}
		}
	}
	n--; m--;
	cout << a[n][m] << endl;
	int nowi = n, nowj = m;
	vector<char> ans;
	while (nowi > 0 || nowj > 0)
	{
		ans.push_back(pred[nowi][nowj]);
		if (ans.back() == 'D') nowi--;
		else nowj--;
	}
	reverse(ans.begin(), ans.end());
	for (const char& i : ans)
		cout << i << " ";
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}