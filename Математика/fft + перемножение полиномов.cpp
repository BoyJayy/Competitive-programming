void fft(vector<complex<double>>& a, bool invert) {
    int n = (int)a.size();
    static vector<int> rev;
    static vector<complex<double>> roots{0, 1};
    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n);
        rev.assign(n, 0);
        for (int i = 0; i < n; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    }
    if ((int)roots.size() < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            double ang = 2 * M_PI / (1 << (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                double a = ang * (2 * i + 1 - (1 << k));
                roots[2 * i + 1] = complex<double>(cos(a), sin(a));
            }
            k++;
        }
    }
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len] * roots[len + j];
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
