const int MAXS = 10000000;
bitset<MAXS + 1> subset_dp;

int subset_sum_best_bitset(const vector<int>& a, int sum) {
    subset_dp.reset();
    subset_dp[0] = 1;
    for (int x : a) subset_dp |= subset_dp << x;
    for (int s = sum; s >= 0; s--) {
        if (subset_dp[s]) return s;
    }
    return 0;
}
