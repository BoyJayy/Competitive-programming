template <typename T>
void build_factorials(int n, T mod, vector<T>& fact, vector<T>& inv, vector<T>& invfact) {
    fact.assign(n + 1, 1);
    inv.assign(n + 1, 1);
    invfact.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % mod;
    for (int i = 2; i <= n; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= n; i++) invfact[i] = invfact[i - 1] * inv[i] % mod;
}
