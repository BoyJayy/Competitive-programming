#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<int> dp(n + 1, 1e9);
	dp[0] = 0;
	for (int i = 0; i < n + 1; i++)
	{
		if (i + 1 <= n)
			dp[i + 1] = min(dp[i] + a[i], dp[i + 1]);
		if (i + 2 <= n)
			dp[i + 2] = min(dp[i] + a[i + 1], dp[i + 2]);
	}
	cout << dp[n];
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}