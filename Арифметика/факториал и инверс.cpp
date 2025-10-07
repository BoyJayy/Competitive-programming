vector<int> fact(n + 1), inv(n + 1), invfact(n + 1);

fact[0] = 1;
for (int i = 1; i <= n; ++i) fact[i] = (long long)fact[i - 1] * i % MOD;

inv[1] = 1;
for (int i = 2; i <= n; ++i) inv[i] = (int)(MOD - (long long)(MOD / i) * inv[MOD % i] % MOD);

invfact[0] = 1;
for (int i = 1; i <= n; ++i) invfact[i] = (long long)invfact[i - 1] * inv[i] % MOD;
