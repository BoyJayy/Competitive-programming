#include <iostream>
#define e '\n'
#define int long long

using namespace std;

int fib(int n)
{
	if (n < 2) return n;
	else return fib(n - 1) + fib(n - 2);
}

void solve()
{
	int n; cin >> n;
	int t = fib(n);
	cout << t;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}