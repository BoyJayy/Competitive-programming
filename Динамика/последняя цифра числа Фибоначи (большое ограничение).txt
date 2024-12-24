#include <iostream>
#include <vector>
#define int long long
#define e '\n'
using namespace std;

signed main()
{
	int n;
	cin >> n;
	vector<int> fib(n + 1);
	fib[0] = 1;
	fib[1] = 1;
	for (int i = 2; i < n + 1; ++i)
	{
		fib[i] = fib[i - 1] % 10 + fib[i - 2] % 10;
	}
	cout << fib[n] % 10;
}