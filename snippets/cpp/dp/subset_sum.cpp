int n, S;
cin >> n >> S;
vector<int> a(n);
for (int &x : a) cin >> x;

vector<unsigned long long> bs((S + 64) / 64);
auto setbit = [&](int pos) { bs[pos >> 6] |= 1ULL << (pos & 63); };
auto testbit = [&](int pos) -> bool { return (bs[pos >> 6] >> (pos & 63)) & 1ULL; };

setbit(0);
for (int x : a) {
    int shift = x >> 6, off = x & 63;
    for (int i = (int)bs.size() - 1; i >= shift; --i) {
        unsigned long long val = bs[i - shift] << off;
        if (off && i - shift - 1 >= 0) val |= bs[i - shift - 1] >> (64 - off);
        bs[i] |= val;
    }
}

int best = S;
while (best >= 0 && !testbit(best)) best--;
cout << best << "\n";
