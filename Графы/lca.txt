int lca(int a, int b) {
	if(turn[a] == turn[b]) {
		if(dist[a] < dist[b]) return a;
		else return b;
    }
    if(dist[last[a]] > dist[last[b]]) return lca(last[a], b);
    return lca(last[b], a);
}