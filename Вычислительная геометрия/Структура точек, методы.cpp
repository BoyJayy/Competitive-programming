struct point {
    long double x, y;
    point() {
        x = 0.0, y = 0.0;
    }
    point(ll x_, ll y_) {
        x = x_, y = y_;
    }
    point operator +(point other) {
        return point(x + other.x, y + other.y);
    }
    point operator -(point other) {
        return point(x - other.x, y - other.y);
    }
    ll operator *(point other) {
        return x * other.x + y * other.y;
    }
    ll operator %(point other) {
        return x * other.y - y * other.x;
    }
    long double len() {
        return sqrt(x * x + y * y);
    }
    point operator*(long double l) {
        return point(x * l, y * l);
    }
    point operator /(long double l) {
        return point(x / l, y / l);
    }
    long double dist(point other) {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};
istream& operator >> (istream& in, point &a) {
    in >> a.x >> a.y;
    return in;
}
ostream& operator << (ostream& os, point &b) {
    os << b.x << ' ' << b.y << '\n';
    return os;
}
