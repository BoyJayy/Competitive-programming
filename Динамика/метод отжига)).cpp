mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
double rnd(){ return (rng()%1000000)/1000000.0; }

struct SA_MaxCut {
    int n, m;
    vector<pair<int,int>> edges;
    vector<int> side;
    long long cur, best;
    vector<int> best_side;

    SA_MaxCut(int n, const vector<pair<int,int>>& E): n(n), m((int)E.size()), edges(E){
        side.assign(n,0);
        for(int i=0;i<n;i++) side[i]=rng()&1;
        cur = score(side);
        best = cur; best_side = side;
    }

    long long score(const vector<int>& s){
        long long val=0;
        for(auto [u,v]: edges) if(s[u]!=s[v]) val++;
        return val;
    }

    long long delta_flip(int v){
        long long d=0;
        for(auto [u,w]: edges){
            if(u==v) d += (side[u]==side[w]? +1 : -1);
            else if(w==v) d += (side[u]==side[w]? +1 : -1);
        }
        return d;
    }

    void run(double T0=1.0, double Tend=1e-4, double alpha=0.995, int iters=200000){
        double T=T0;
        for(int it=0; it<iters; it++){
            int v = rng()%n;
            long long d = delta_flip(v);
            if(d>=0 || exp(d/T) > rnd()){
                side[v]^=1;
                cur += d;
                if(cur>best){ best=cur; best_side=side; }
            }
            T*=alpha;
            if(T<Tend) T=T0;
        }
    }
};
