struct SlopeTrick {
    ll addL=0, addR=0;
    priority_queue<ll> L;
    priority_queue<ll, vector<ll>, greater<ll>> R;

    void push_left(ll x){
        if(!L.empty() && x < L.top()){
            L.push(x);
            x = L.top(); L.pop();
        }
        R.push(x);
    }
    void push_right(ll x){
        if(!R.empty() && x > R.top()){
            R.push(x);
            x = R.top(); R.pop();
        }
        L.push(x);
    }

    void add_abs(ll a){
        push_left(a - addL);
        push_right(a - addR);
    }

    void shift_left(ll c){ addL += c; }
    void shift_right(ll c){ addR += c; }

    ll min_f() const { return 0; }

    ll eval(ll x){
        ll res=0;
        priority_queue<ll> Lc=L; 
        priority_queue<ll, vector<ll>, greater<ll>> Rc=R;
        while(!Lc.empty() && Lc.top() + addL > x){ res += Lc.top()+addL - x; Lc.pop(); }
        while(!Rc.empty() && Rc.top() + addR < x){ res += x - (Rc.top()+addR); Rc.pop(); }
        return res;
    }
};
