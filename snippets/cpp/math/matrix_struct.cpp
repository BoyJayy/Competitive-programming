template <typename T>
struct Matrix {
    int n, m;
    T mod;
    vector<vector<T>> a;

    Matrix(): n(0), m(0), mod(0) {}
    Matrix(int n, int m, T mod = 0, T diag = 0): n(n), m(m), mod(mod), a(n, vector<T>(m)) {
        for (int i = 0; i < min(n, m); i++) a[i][i] = norm(diag);
    }

    T norm(T x) const {
        if (!mod) return x;
        x %= mod;
        if (x < 0) x += mod;
        return x;
    }

    vector<T>& operator[](int i) { return a[i]; }
    const vector<T>& operator[](int i) const { return a[i]; }

    Matrix operator+(const Matrix& o) const {
        Matrix res(n, m, mod);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) res[i][j] = norm(a[i][j] + o[i][j]);
        }
        return res;
    }

    Matrix operator-(const Matrix& o) const {
        Matrix res(n, m, mod);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) res[i][j] = norm(a[i][j] - o[i][j]);
        }
        return res;
    }

    Matrix operator*(const Matrix& o) const {
        Matrix res(n, o.m, mod);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if (!a[i][k]) continue;
                for (int j = 0; j < o.m; j++) {
                    res[i][j] += a[i][k] * o[k][j];
                    if (mod) res[i][j] %= mod;
                }
            }
        }
        return res;
    }

    Matrix& operator*=(const Matrix& o) {
        return *this = *this * o;
    }

    vector<T> mul_vec(const vector<T>& v) const {
        vector<T> res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i] += a[i][j] * v[j];
                if (mod) res[i] %= mod;
            }
        }
        return res;
    }

    Matrix pow(long long e) const {
        Matrix base = *this;
        Matrix res(n, n, mod, 1);
        while (e) {
            if (e & 1) res *= base;
            base *= base;
            e >>= 1;
        }
        return res;
    }
};

template <typename T>
Matrix<T> identity(int n, T mod = 0) {
    return Matrix<T>(n, n, mod, 1);
}
