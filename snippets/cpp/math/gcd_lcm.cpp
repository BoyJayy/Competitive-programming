template <typename T>
T gcd_val(T a, T b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

template <typename T>
T lcm_val(T a, T b) {
    return a / gcd_val(a, b) * b;
}
