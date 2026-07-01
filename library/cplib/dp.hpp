#pragma once

namespace cplib {

template <typename T = long long>
T min_stair_cost(const std::vector<T>& a) {
    int n = a.size();
    std::vector<T> dp(n + 1, std::numeric_limits<T>::max() / 4);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        dp[i + 1] = std::min(dp[i + 1], dp[i] + a[i]);
        if (i + 2 <= n) dp[i + 2] = std::min(dp[i + 2], dp[i] + a[i + 1]);
    }
    return dp[n];
}

template <typename T = int>
T knapsack_01(const std::vector<int>& w, const std::vector<T>& cost, int s) {
    int n = w.size();
    std::vector<T> dp(s + 1);
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

template <typename T>
int lis_len(const std::vector<T>& a) {
    std::vector<T> dp;
    for (T x : a) {
        auto it = std::lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    return dp.size();
}

template <typename T>
std::pair<int, int> lis_count(const std::vector<T>& a, int mod) {
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

template <typename T>
std::vector<T> lis_restore(const std::vector<T>& a) {
    int n = a.size();
    std::vector<T> dp;
    std::vector<int> id, p(n, -1);
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
    std::vector<T> ans;
    for (int v = id.back(); v != -1; v = p[v]) ans.push_back(a[v]);
    std::reverse(ans.begin(), ans.end());
    return ans;
}

template <typename T = long long>
T min_grid_path(const std::vector<std::vector<T>>& a) {
    int n = a.size(), m = a[0].size();
    std::vector<std::vector<T>> dp(n, std::vector<T>(m, std::numeric_limits<T>::max() / 4));
    dp[0][0] = a[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i) dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + a[i][j]);
            if (j) dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + a[i][j]);
        }
    }
    return dp[n - 1][m - 1];
}

template <typename T = int>
T edit_distance(const std::string& a, const std::string& b, T ins = 1, T del = 1, T sub = 1) {
    int n = a.size(), m = b.size();
    std::vector<std::vector<T>> dp(n + 1, std::vector<T>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i * del;
    for (int j = 0; j <= m; j++) dp[0][j] = j * ins;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
                dp[i][j] = std::min({dp[i - 1][j] + del,
                                 dp[i][j - 1] + ins,
                                 dp[i - 1][j - 1] + (a[i - 1] != b[j - 1] ? sub : T())});
        }
    }
    return dp[n][m];
}

template <typename T>
void sos_sum(std::vector<T>& f, int k) {
    for (int b = 0; b < k; b++) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (mask >> b & 1) f[mask] += f[mask ^ (1 << b)];
        }
    }
}

template <typename T = long long>
T count_digit_sum(long long n, int need) {
    std::string s = std::to_string(n);
    int len = s.size();
    std::vector dp(len + 1, std::vector(need + 1, std::vector<T>(2, -1)));
    std::function<T(int, int, int)> go = [&](int pos, int sum, int tight) {
        if (sum < 0) return T();
        if (pos == len) return sum == 0 ? (T)1 : T();
        T& res = dp[pos][sum][tight];
        if (res != (T)-1) return res;
        res = T();
        int up = tight ? s[pos] - '0' : 9;
        for (int d = 0; d <= up; d++) {
            res += go(pos + 1, sum - d, tight && d == up);
        }
        return res;
    };
    return go(0, need, 1);
}

template <typename T = long long, typename F = std::function<T(int, int)>>
void divide_conquer_layer(int l, int r, int optl, int optr,
                          const std::vector<T>& prev,
                          std::vector<T>& cur,
                          const F& cost) {
    if (l > r) return;
    int mid = (l + r) / 2;
    T best = std::numeric_limits<T>::max() / 4;
    int opt = optl;
    for (int j = optl; j <= std::min(mid, optr); j++) {
        T val = prev[j] + cost(j, mid);
        if (val < best) {
            best = val;
            opt = j;
        }
    }
    cur[mid] = best;
    divide_conquer_layer(l, mid - 1, optl, opt, prev, cur, cost);
    divide_conquer_layer(mid + 1, r, opt, optr, prev, cur, cost);
}

template <typename T = long long>
struct CHTMax {
    struct Line {
        T k, b;
        long double x;
    };

    std::deque<Line> q;

    long double cross_x(Line a, Line b) {
        return (long double)(b.b - a.b) / (a.k - b.k);
    }

    void add(T k, T b) {
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

    T get(T x) {
        while ((int)q.size() >= 2 && q[1].x <= x) q.pop_front();
        return q.front().k * x + q.front().b;
    }
};

template <typename T = long long>
struct SlopeTrick {
    T mn = 0;
    std::priority_queue<T> L;
    std::priority_queue<T, std::vector<T>, std::greater<T>> R;

    void add_x_minus_a(T a) {
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

    void add_a_minus_x(T a) {
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

    void add_abs(T a) {
        add_x_minus_a(a);
        add_a_minus_x(a);
    }

    T min_f() {
        return mn;
    }
};

}
