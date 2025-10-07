struct DSU{
    int n; vector<int> p, sz;
    DSU(int n=0){ if(n) init(n); }
    void init(int n_){ n=n_; p.resize(n); sz.assign(n,1); iota(p.begin(),p.end(),0); }
    int f(int x){ return p[x]==x?x:p[x]=f(p[x]); }
    bool uni(int a,int b){ a=f(a); b=f(b); if(a==b) return false; if(sz[a]<sz[b]) swap(a,b); p[b]=a; sz[a]+=sz[b]; return true; }
    bool same(int a,int b){ return f(a)==f(b); }
};

struct Edge{ int u,v,c; };

struct MI_Graph_Partition{
    int n, m, C;
    vector<Edge> e;
    vector<int> lim;
    vector<int> in, cnt;

    MI_Graph_Partition(int n,int m,int C): n(n), m(m), C(C), e(m), lim(C,0) {}

    vector<vector<int>> build_adj(){
        vector<vector<int>> adj(n);
        for(int i=0;i<m;i++) if(in[i]){
            adj[e[i].u].push_back(i);
            adj[e[i].v].push_back(i);
        }
        return adj;
    }

    bool graphic_can_add(int id){
        DSU dsu(n);
        for(int i=0;i<m;i++) if(in[i] && i!=id) dsu.uni(e[i].u, e[i].v);
        return !dsu.same(e[id].u, e[id].v);
    }

    vector<int> graphic_exchange_set(int id){
        vector<vector<int>> adjV(n);
        for(int i=0;i<m;i++) if(in[i]){
            int u=e[i].u, v=e[i].v;
            adjV[u].push_back(i);
            adjV[v].push_back(i);
        }
        int s=e[id].u, t=e[id].v;
        vector<int> pe(n,-1), peEdge(n,-1);
        queue<int> q;
        q.push(s); pe[s]=-2;
        while(!q.empty() && pe[t]==-1){
            int v=q.front(); q.pop();
            for(int eid: adjV[v]){
                int u = e[eid].u ^ e[eid].v ^ v;
                if(pe[u]!=-1) continue;
                pe[u]=v; peEdge[u]=eid;
                q.push(u);
            }
        }
        vector<int> cyc;
        if(pe[t]==-1) return cyc;
        int v=t;
        while(v!=s){
            cyc.push_back(peEdge[v]);
            v=pe[v];
        }
        return cyc;
    }

    bool partition_can_add(int id){
        return cnt[e[id].c] < lim[e[id].c];
    }

    vector<int> partition_exchange_to(int id){
        vector<int> out;
        int col=e[id].c;
        if(cnt[col] < lim[col]) return out;
        for(int i=0;i<m;i++) if(in[i] && e[i].c==col) out.push_back(i);
        return out;
    }

    vector<int> solve(){
        in.assign(m,0);
        cnt.assign(C,0);
        bool improved=true;
        while(improved){
            improved=false;
            const int S = m, T = m+1, N = m+2;
            vector<vector<int>> G(N);
            for(int v=0; v<m; v++) if(!in[v]){
                if(graphic_can_add(v)) G[S].push_back(v);
            }
            for(int v=0; v<m; v++) if(!in[v]){
                if(partition_can_add(v)) G[v].push_back(T);
            }
            for(int u=0; u<m; u++) if(in[u]){
                for(int v=0; v<m; v++) if(!in[v]){
                    auto cyc = graphic_exchange_set(v);
                    for(int x:cyc) if(x==u) G[u].push_back(v);
                }
            }
            for(int v=0; v<m; v++) if(!in[v]){
                auto ex = partition_exchange_to(v);
                for(int u:ex) G[v].push_back(u);
            }
            vector<int> par(N,-1);
            queue<int> q;
            q.push(S); par[S]=-2;
            while(!q.empty() && par[T]==-1){
                int x=q.front(); q.pop();
                for(int y:G[x]) if(par[y]==-1){
                    par[y]=x; q.push(y);
                }
            }
            if(par[T]==-1) break;
            vector<int> path;
            int cur=T;
            while(cur!=S){ path.push_back(cur); cur=par[cur]; }
            reverse(path.begin(), path.end());
            int state=0;
            for(int node: path){
                if(node==T) break;
                if(state==0){ in[node]^=1; cnt[e[node].c]+= in[node]? +1 : -1; state=1; }
                else{ in[node]^=1; cnt[e[node].c]+= in[node]? +1 : -1; state=0; }
            }
            improved=true;
        }
        vector<int> res;
        for(int i=0;i<m;i++) if(in[i]) res.push_back(i);
        return res;
    }
};
