template <typename T>
struct SlopeTrick {
    T mn = T();
    priority_queue<T> L;
    priority_queue<T, vector<T>, greater<T>> R;

    void add_x_minus_a(T a) {
        if (!L.empty() && L.top() > a) {
            mn += L.top() - a;
            R.push(L.top());
            L.pop();
            L.push(a);
        }
        else {
            R.push(a);
        }
    }

    void add_a_minus_x(T a) {
        if (!R.empty() && R.top() < a) {
            mn += a - R.top();
            L.push(R.top());
            R.pop();
            R.push(a);
        }
        else {
            L.push(a);
        }
    }

    void add_abs(T a) {
        add_x_minus_a(a);
        add_a_minus_x(a);
    }

    T min_f() {
        return mn;
    }
};
