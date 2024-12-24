#include <iostream>
#include <vector>

#define e '\n'
#define int long long

using namespace std;

pair<int, int> bin_s_l(int x, vector<int>& arr)
{
	int n = arr.size();
	int r = n - 1; int l = -1;
	while (r - l > 1)
	{
		int mid = (r + l) / 2;
		if (arr[mid] >= x)
			r = mid;
		else
			l = mid;
	}
	return { r, l };
}

pair<int, int> bin_s_r(int x, vector<int>& arr)
{
	int n = arr.size();
	int r = n; int l = 0;
	while (r - l > 1)
	{
		int mid = (r + l) / 2;
		if (arr[mid] > x)
			r = mid;
		else
			l = mid;
	}
	return { r, l };
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> arr1(n);
	vector<int> arr2(m);
	for (int i = 0; i < n; i++)
		cin >> arr1[i];
	for (int i = 0; i < m; i++)
		cin >> arr2[i];
	for (int i = 0; i < m; i++)
	{
		pair<int, int> temp1, temp2;
		temp1.first = bin_s_l(arr2[i], arr1).first;
		temp1.second = bin_s_l(arr2[i], arr1).second;
		temp2.first = bin_s_r(arr2[i], arr1).first;
		temp2.second = bin_s_r(arr2[i], arr1).second;
		if (arr1[temp1.first] != arr2[i])
		{
			cout << 0 << e;
			continue;
		}
		else
			cout << temp1.first + 1 << " " << temp2.second + 1 << e;
	}
}