#include <iostream>
#include <vector>

#define e '\n'
#define int long long

using namespace std;

int solve(vector<int>& a)
{
	int c = 0;
	int n = a.size();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				c++;
			}
		}
	return c;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cout << solve(a);
}