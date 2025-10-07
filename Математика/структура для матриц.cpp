struct Matrix {
    int n, m;
    long long mod;
    vector<vector<long long>> a;

    Matrix(): n(0), m(0), mod(0) {}
    Matrix(int n_, int m_, long long mod_=0, long long fill_=0): n(n_), m(m_), mod(mod_), a(n_, vector<long long>(m_, 0)) {
        if (fill_ != 0) {
            for (int i = 0; i < min(n, m); ++i) a[i][i] = norm(fill_);
        }
    }

    static Matrix zeros(int n, int m, long long mod=0) { return Matrix(n, m, mod, 0); }
    static Matrix identity(int n, long long mod=0) { return Matrix(n, n, mod, 1); }

    long long norm(long long x) const {
        if (!mod) return x;
        x %= mod;
        if (x < 0) x += mod;
        return x;
    }

    vector<long long>& operator[](int i){ return a[i]; }
    const vector<long long>& operator[](int i) const { return a[i]; }

    Matrix operator+(const Matrix& o) const {
        Matrix r(n, m, mod);
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) r.a[i][j] = norm(a[i][j] + o.a[i][j]);
        return r;
    }

    Matrix operator-(const Matrix& o) const {
        Matrix r(n, m, mod);
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) r.a[i][j] = norm(a[i][j] - o.a[i][j]);
        return r;
    }

    Matrix operator*(const Matrix& o) const {
        Matrix r(n, o.m, mod);
        int K = m;
        if (!mod) {
            for (int i = 0; i < n; ++i) {
                for (int k = 0; k < K; ++k) if (a[i][k]) {
                    long long aik = a[i][k];
                    for (int j = 0; j < o.m; ++j) r.a[i][j] += aik * o.a[k][j];
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                for (int k = 0; k < K; ++k) if (a[i][k]) {
                    long long aik = a[i][k];
                    for (int j = 0; j < o.m; ++j) {
                        long long v = r.a[i][j] + (__int128)aik * o.a[k][j] % mod;
                        if (v >= mod) v -= mod;
                        r.a[i][j] = v;
                    }
                }
            }
        }
        return r;
    }

    Matrix& operator*=(const Matrix& o){ return *this = (*this) * o; }

    vector<long long> mul_vec(const vector<long long>& v) const {
        vector<long long> res(n, 0);
        if (!mod) {
            for (int i = 0; i < n; ++i) {
                long long s = 0;
                for (int j = 0; j < m; ++j) s += a[i][j] * v[j];
                res[i] = s;
            }
        } else {
            for (int i = 0; i < n; ++i) {
                __int128 s = 0;
                for (int j = 0; j < m; ++j) s += (__int128)a[i][j] * v[j] % mod;
                res[i] = (long long)(s % mod);
            }
        }
        return res;
    }

    Matrix transpose() const {
        Matrix r(m, n, mod);
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) r.a[j][i] = a[i][j];
        return r;
    }

    Matrix pow(long long e) const {
        Matrix base = *this;
        Matrix r = identity(n, mod);
        while (e > 0) {
            if (e & 1) r *= base;
            base *= base;
            e >>= 1;
        }
        return r;
    }
};
