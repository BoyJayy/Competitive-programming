void dfs(int v, int* visited, vec<int>* rb, int pred, vec<int>& ch) {
    visited[v] = 1;
    for (auto& u: rb[v]) {
        if (!visited[u]) {
            ch.push_back(u);
            dfs(u, visited, rb, v, ch);
            ch.pop_back();
        }
        if (visited[u] == 1 && u != pred) {
            cout << "YES" << endl;
            for (int i = u; i < ch.size(); i++) {
                cout << ch[i] + 1 << ' ';
            }
            exit(0);
        }
    }
    visited[v] = 2;
}

void solve() {
    int n, m; cin >> n >> m;
    vec<int> rb [n];
    for (int i = 0; i < m; i++) {
            int s, f; cin >> s >> f;
            s--; f--;
            rb[s].push_back(f);
    }
    int visited[n]{};
    vec<int> ch;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            ch = {i};
            dfs(i, visited, rb, -1, ch);
        }
    }
    cout << "NO";
}
