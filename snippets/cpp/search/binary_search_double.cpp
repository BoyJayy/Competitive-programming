template<class F>
double binsearch_double(double lo, double hi, F ok, int iters = 80) {
    for (int i = 0; i < iters; i++) {
        double mid = (lo + hi) * 0.5;
        if (ok(mid)) hi = mid;
        else lo = mid;
    }
    return (lo + hi) * 0.5;
}
