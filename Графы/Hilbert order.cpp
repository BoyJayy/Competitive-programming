static inline long long hilbert_order_ll(long long x, long long y, int pow, int rot = 0) {
    if (pow == 0) return 0;
    long long h = 1LL << (pow - 1);
    int seg = (x < h) ? ((y < h) ? 0 : 3) : ((y < h) ? 1 : 2);
    seg = (seg + rot) & 3;
    static const int rotateDelta[4] = {1, 0, 0, 3};
    long long nx = x & (x ^ h), ny = y & (y ^ h);
    int nrot = (rot + rotateDelta[seg]) & 3;
    long long sub = 1LL << (2 * pow - 2);
    long long ord = seg * sub;
    long long add = hilbert_order_ll(nx, ny, pow - 1, nrot);
    if (seg == 1 || seg == 2) ord += add;
    else ord += sub - add - 1;
    return ord;
}
