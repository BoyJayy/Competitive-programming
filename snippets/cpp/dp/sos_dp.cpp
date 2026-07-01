template <typename T>
void sos_sum(vector<T>& f, int k) {
    for (int b = 0; b < k; b++) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (mask >> b & 1) f[mask] += f[mask ^ (1 << b)];
        }
    }
}
