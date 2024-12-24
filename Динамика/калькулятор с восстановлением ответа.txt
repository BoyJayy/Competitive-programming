#include <bits/stdc++.h>
//#define int long long
#define endl "\n"

using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> dp(n + 1, 1e6);
	dp[0] = 0; dp[1] = 0;
	vector<int> pred(n + 1, -1);
	for (int i = 2; i <= n; i++)
	{
		//cout << "NOW " << i << ' ';
		dp[i] = dp[i - 1] + 1;
		pred[i] = i - 1;
		if ((i % 2 == 0) && (dp[i] > dp[i / 2] + 1))
		{
			dp[i] = min(dp[i], dp[i / 2] + 1);
			pred[i] = i / 2;
		}
		if ((i % 3 == 0) && (dp[i] > dp[i / 3] + 1))
		{
			dp[i] = min(dp[i], dp[i / 3] + 1);
			pred[i] = i / 3;
		}
		//cout << dp[i] << ' ' << pred[i] << endl;
	}
	int now = n;
	vector<int> ans;
	while (now != -1)
	{
		ans.push_back(now);
		now = pred[now];
	}
	reverse(ans.begin(), ans.end());
	for (int i = 0; i + 1 < ans.size(); i++)
	{
		if (ans[i + 1] == ans[i] * 3)
			cout << 3;
		else if (ans[i + 1] == ans[i] * 2)
			cout << 2;
		else cout << 1;
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}