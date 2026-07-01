vector<int> fft_rev;
vector<complex<double>> fft_roots{0, 1};

void fft(vector<complex<double>>& a, bool invert) {
    int n = (int)a.size();
    if ((int)fft_rev.size() != n) {
        int k = __builtin_ctz(n);
        fft_rev.assign(n, 0);
        for (int i = 0; i < n; i++) fft_rev[i] = (fft_rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    }
    if ((int)fft_roots.size() < n) {
        int k = __builtin_ctz(fft_roots.size());
        fft_roots.resize(n);
        while ((1 << k) < n) {
            double ang = 2 * M_PI / (1 << (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                fft_roots[2 * i] = fft_roots[i];
                double a = ang * (2 * i + 1 - (1 << k));
                fft_roots[2 * i + 1] = complex<double>(cos(a), sin(a));
            }
            k++;
        }
    }
    for (int i = 0; i < n; i++) if (i < fft_rev[i]) swap(a[i], a[fft_rev[i]]);
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len] * fft_roots[len + j];
                a[i + j] = u + v;
                a[i + j + len] = u - v;
            }
        }
    }
    if (invert) {
        reverse(a.begin() + 1, a.end());
        for (auto& x : a) x /= n;
    }
}

vector<long long> convolution(const vector<int>& A, const vector<int>& B) {
    int n1 = (int)A.size(), n2 = (int)B.size();
    int n = 1;
    while (n < n1 + n2 - 1) n <<= 1;
    vector<complex<double>> fa(n), fb(n);
    for (int i = 0; i < n1; i++) fa[i] = complex<double>(A[i], 0);
    for (int i = 0; i < n2; i++) fb[i] = complex<double>(B[i], 0);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<long long> res(n1 + n2 - 1);
    for (int i = 0; i < (int)res.size(); i++) res[i] = llround(fa[i].real());
    return res;
}
