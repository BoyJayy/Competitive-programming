#pragma once

namespace cplib {

template <typename T, typename U>
int lower_pos(const std::vector<T>& a, U x) {
    int l = -1, r = a.size();
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m] >= x) r = m;
        else l = m;
    }
    return r;
}

template <typename T, typename U>
int upper_pos(const std::vector<T>& a, U x) {
    int l = -1, r = a.size();
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m] > x) r = m;
        else l = m;
    }
    return r;
}

template <typename T, typename F>
T last_true(T l, T r, F ok) {
    while (r - l > 1) {
        T m = (l + r) / 2;
        if (ok(m)) l = m;
        else r = m;
    }
    return l;
}

template <typename T, typename U>
long long subarrays_sum_at_most(const std::vector<T>& a, U s) {
    int n = a.size(), l = 0;
    long long ans = 0;
    T sum = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum > s) sum -= a[l++];
        ans += r - l + 1;
    }
    return ans;
}

template <typename T>
std::vector<T> pref_sum(const std::vector<T>& a) {
    int n = a.size();
    std::vector<T> pref(n + 1);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    return pref;
}

template <typename T>
T sum_on(const std::vector<T>& pref, int l, int r) {
    return pref[r + 1] - pref[l];
}

template <typename T = long long>
struct Diff {
    int n;
    std::vector<T> d;

    Diff(int n): n(n), d(n + 1) {}

    void add(int l, int r, T x) {
        d[l] += x;
        if (r + 1 < n) d[r + 1] -= x;
    }

    std::vector<T> get() {
        std::vector<T> a(n);
        T cur = 0;
        for (int i = 0; i < n; i++) {
            cur += d[i];
            a[i] = cur;
        }
        return a;
    }
};

template <typename T>
std::vector<int> compress(const std::vector<T>& a) {
    std::vector<T> b = a;
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    std::vector<int> res(a.size());
    int n = a.size();
    for (int i = 0; i < n; i++) {
        res[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }
    return res;
}

std::vector<int> submasks(int mask) {
    std::vector<int> res;
    for (int sub = mask; sub; sub = (sub - 1) & mask) res.push_back(sub);
    res.push_back(0);
    return res;
}

template <typename T>
int max_non_overlapping(std::vector<std::pair<T, T>> seg) {
    std::sort(seg.begin(), seg.end(), [](auto a, auto b) {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    });
    int ans = 0;
    T last{};
    bool have = false;
    for (auto [l, r] : seg) {
        if (!have || l >= last) {
            ans++;
            last = r;
            have = true;
        }
    }
    return ans;
}

template <typename T>
void uniq(std::vector<T>& a) {
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
}

}
