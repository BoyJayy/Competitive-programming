#pragma once

namespace cplib {

long long min_stair_cost(const std::vector<int>& a) {
    int n = a.size();
    std::vector<long long> dp(n + 1, (long long)4e18);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        dp[i + 1] = std::min(dp[i + 1], dp[i] + a[i]);
        if (i + 2 <= n) dp[i + 2] = std::min(dp[i + 2], dp[i] + a[i + 1]);
    }
    return dp[n];
}

int knapsack_01(const std::vector<int>& w, const std::vector<int>& cost, int s) {
    int n = w.size();
    std::vector<int> dp(s + 1);
    for (int i = 0; i < n; i++) {
        for (int j = s; j >= w[i]; j--) {
            dp[j] = std::max(dp[j], dp[j - w[i]] + cost[i]);
        }
    }
    return *std::max_element(dp.begin(), dp.end());
}

int subset_sum_best(const std::vector<int>& a, int s) {
    std::vector<char> dp(s + 1);
    dp[0] = true;
    for (int x : a) {
        for (int j = s; j >= x; j--) dp[j] |= dp[j - x];
    }
    for (int j = s; j >= 0; j--) {
        if (dp[j]) return j;
    }
    return 0;
}

int lis_len(const std::vector<int>& a) {
    std::vector<int> dp;
    for (int x : a) {
        auto it = std::lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    return dp.size();
}

std::pair<int, int> lis_count(const std::vector<int>& a, int mod) {
    int n = a.size();
    std::vector<int> dp(n, 1), cnt(n, 1);
    int len = 0, ways = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if (dp[j] + 1 == dp[i]) {
                    cnt[i] += cnt[j];
                    if (cnt[i] >= mod) cnt[i] -= mod;
                }
            }
        }
        if (dp[i] > len) {
            len = dp[i];
            ways = cnt[i];
        }
        else if (dp[i] == len) {
            ways += cnt[i];
            ways %= mod;
        }
    }
    return {len, ways};
}

std::vector<int> lis_restore(const std::vector<int>& a) {
    int n = a.size();
    std::vector<int> dp, id, p(n, -1);
    for (int i = 0; i < n; i++) {
        int pos = std::lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        int len = dp.size();
        if (pos == len) {
            dp.push_back(a[i]);
            id.push_back(i);
        }
        else {
            dp[pos] = a[i];
            id[pos] = i;
        }
        if (pos) p[i] = id[pos - 1];
    }
    std::vector<int> ans;
    for (int v = id.back(); v != -1; v = p[v]) ans.push_back(a[v]);
    std::reverse(ans.begin(), ans.end());
    return ans;
}

long long min_grid_path(const std::vector<std::vector<int>>& a) {
    int n = a.size(), m = a[0].size();
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(m, (long long)4e18));
    dp[0][0] = a[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i) dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + a[i][j]);
            if (j) dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + a[i][j]);
        }
    }
    return dp[n - 1][m - 1];
}

int edit_distance(const std::string& a, const std::string& b) {
    int n = a.size(), m = b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = std::min({dp[i - 1][j] + 1,
                                 dp[i][j - 1] + 1,
                                 dp[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
        }
    }
    return dp[n][m];
}

void sos_sum(std::vector<long long>& f, int k) {
    for (int b = 0; b < k; b++) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (mask >> b & 1) f[mask] += f[mask ^ (1 << b)];
        }
    }
}

long long count_digit_sum(long long n, int need) {
    std::string s = std::to_string(n);
    int len = s.size();
    std::vector dp(len + 1, std::vector(need + 1, std::vector<long long>(2, -1)));
    std::function<long long(int, int, int)> go = [&](int pos, int sum, int tight) {
        if (sum < 0) return 0LL;
        if (pos == len) return sum == 0 ? 1LL : 0LL;
        long long& res = dp[pos][sum][tight];
        if (res != -1) return res;
        res = 0;
        int up = tight ? s[pos] - '0' : 9;
        for (int d = 0; d <= up; d++) {
            res += go(pos + 1, sum - d, tight && d == up);
        }
        return res;
    };
    return go(0, need, 1);
}

void divide_conquer_layer(int l, int r, int optl, int optr,
                          const std::vector<long long>& prev,
                          std::vector<long long>& cur,
                          const std::function<long long(int, int)>& cost) {
    if (l > r) return;
    int mid = (l + r) / 2;
    long long best = (long long)4e18;
    int opt = optl;
    for (int j = optl; j <= std::min(mid, optr); j++) {
        long long val = prev[j] + cost(j, mid);
        if (val < best) {
            best = val;
            opt = j;
        }
    }
    cur[mid] = best;
    divide_conquer_layer(l, mid - 1, optl, opt, prev, cur, cost);
    divide_conquer_layer(mid + 1, r, opt, optr, prev, cur, cost);
}

struct CHTMax {
    struct Line {
        long long k, b;
        long double x;
    };

    std::deque<Line> q;

    long double cross_x(Line a, Line b) {
        return (long double)(b.b - a.b) / (a.k - b.k);
    }

    void add(long long k, long long b) {
        Line cur{k, b, -1e30};
        while (!q.empty() && q.back().k == k && q.back().b <= b) q.pop_back();
        if (!q.empty() && q.back().k == k) return;
        while ((int)q.size() >= 2) {
            cur.x = cross_x(q.back(), cur);
            if (cur.x <= q.back().x) q.pop_back();
            else break;
        }
        if (!q.empty()) cur.x = cross_x(q.back(), cur);
        q.push_back(cur);
    }

    long long get(long long x) {
        while ((int)q.size() >= 2 && q[1].x <= x) q.pop_front();
        return q.front().k * x + q.front().b;
    }
};

struct SlopeTrick {
    long long mn = 0;
    std::priority_queue<long long> L;
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> R;

    void add_x_minus_a(long long a) {
        if (!L.empty() && L.top() > a) {
            mn += L.top() - a;
            R.push(L.top());
            L.pop();
            L.push(a);
        }
        else {
            R.push(a);
        }
    }

    void add_a_minus_x(long long a) {
        if (!R.empty() && R.top() < a) {
            mn += a - R.top();
            L.push(R.top());
            R.pop();
            R.push(a);
        }
        else {
            L.push(a);
        }
    }

    void add_abs(long long a) {
        add_x_minus_a(a);
        add_a_minus_x(a);
    }

    long long min_f() {
        return mn;
    }
};

}
