#include <iostream>
#include <vector>
#include <algorithm>

#define e '\n'
#define int long long

using namespace std;

void solve(vector<int>& a, size_t start, size_t end)
{
	if (end - start < 2)
	{
		return;
	}
	if (end - start == 2)
	{
		if (a[start] > a[start + 1])
			swap(a[start], a[start + 1]);
		return;
	}
	solve(a, start, start + (end - start) / 2);
	solve(a, start + (end - start) / 2, end);
	vector<int> b;
	size_t b1 = start;
	size_t e1 = start + (end - start) / 2;
	size_t  b2 = e1;
	while (b.size() < end - start)
	{
		if (b1 >= e1 || (b2 < end && a[b2] <= a[b1]))
		{
			b.push_back(a[b2]);
			++b2;
		}
		else
		{
			b.push_back(a[b1]);
			++b1;
		}
	}
	for (size_t i = start; i < end; ++i)
		a[i] = b[i - start];
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	solve(a, 0, a.size());
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}