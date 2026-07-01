template <typename T>
struct Point {
    T x, y;

    Point(T x = 0, T y = 0): x(x), y(y) {}

    Point operator+(Point other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(Point other) const {
        return {x - other.x, y - other.y};
    }

    Point operator*(T k) const {
        return {x * k, y * k};
    }

    T dot(Point other) const {
        return x * other.x + y * other.y;
    }

    T cross(Point other) const {
        return x * other.y - y * other.x;
    }

    long double len() const {
        return sqrt((long double)dot(*this));
    }

    long double dist(Point other) const {
        long double dx = x - other.x;
        long double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
};
