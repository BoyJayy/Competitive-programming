#pragma once

namespace cplib {

std::vector<int> prefix_function(const std::string& s) {
    int n = s.size();
    std::vector<int> p(n);
    for (int i = 1; i < n; i++) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}

std::vector<int> kmp_find(const std::string& s, const std::string& t) {
    std::string cur = t + "#" + s;
    std::vector<int> p = prefix_function(cur), ans;
    int nt = t.size(), n = cur.size();
    for (int i = nt + 1; i < n; i++) {
        if (p[i] == nt) ans.push_back(i - 2 * nt);
    }
    return ans;
}

std::vector<int> z_function(const std::string& s) {
    int n = s.size();
    std::vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

struct Hash {
    long long mod, base;
    std::vector<long long> h, pw;

    Hash(const std::string& s, long long mod = 1000000007, long long base = 911382323): mod(mod), base(base) {
        int n = s.size();
        h.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = (h[i] * base + s[i]) % mod;
            pw[i + 1] = pw[i] * base % mod;
        }
    }

    long long get(int l, int r) {
        return (h[r + 1] - h[l] * pw[r - l + 1] % mod + mod) % mod;
    }
};

struct Trie {
    std::vector<std::array<int, 26>> to;
    std::vector<int> term;

    Trie() {
        to.push_back({});
        term.push_back(0);
    }

    void add(const std::string& s) {
        int v = 0;
        for (char c : s) {
            int x = c - 'a';
            if (!to[v][x]) {
                to[v][x] = to.size();
                to.push_back({});
                term.push_back(0);
            }
            v = to[v][x];
        }
        term[v]++;
    }

    bool find(const std::string& s) {
        int v = 0;
        for (char c : s) {
            int x = c - 'a';
            if (!to[v][x]) return false;
            v = to[v][x];
        }
        return term[v] > 0;
    }
};

std::vector<int> manacher_odd(const std::string& s) {
    int n = s.size();
    std::vector<int> d(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = i > r ? 1 : std::min(d[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return d;
}

std::vector<int> manacher_even(const std::string& s) {
    int n = s.size();
    std::vector<int> d(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = i > r ? 0 : std::min(d[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
    return d;
}

std::vector<int> suffix_array(std::string s) {
    s.push_back(0);
    int n = s.size();
    std::vector<int> p(n), c(n);
    std::vector<std::pair<char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        std::vector<int> cnt(n), pos(n), pn(n), cn(n);
        for (int x : c) cnt[x]++;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int x : p) pn[pos[c[x]]++] = x;
        p = pn;
        for (int i = 1; i < n; i++) {
            std::pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            std::pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            cn[p[i]] = cn[p[i - 1]] + (cur != prev);
        }
        c = cn;
    }
    p.erase(p.begin());
    return p;
}

std::vector<int> lcp_array(const std::string& s, const std::vector<int>& p) {
    int n = s.size();
    std::vector<int> r(n), lcp(n - 1);
    for (int i = 0; i < n; i++) r[p[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[r[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[r[i]] = k;
        if (k) k--;
    }
    return lcp;
}

struct AhoCorasick {
    std::vector<std::array<int, 26>> to;
    std::vector<int> link, out;

    AhoCorasick() {
        to.push_back({});
        link.push_back(0);
        out.push_back(0);
    }

    int add(const std::string& s) {
        int v = 0;
        for (char c : s) {
            int x = c - 'a';
            if (!to[v][x]) {
                to[v][x] = to.size();
                to.push_back({});
                link.push_back(0);
                out.push_back(0);
            }
            v = to[v][x];
        }
        out[v]++;
        return v;
    }

    void build() {
        std::queue<int> q;
        for (int c = 0; c < 26; c++) {
            if (to[0][c]) q.push(to[0][c]);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            out[v] += out[link[v]];
            for (int c = 0; c < 26; c++) {
                if (to[v][c]) {
                    link[to[v][c]] = to[link[v]][c];
                    q.push(to[v][c]);
                }
                else {
                    to[v][c] = to[link[v]][c];
                }
            }
        }
    }

    int next(int v, char c) {
        return to[v][c - 'a'];
    }
};

}
