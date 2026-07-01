def bellman_ford(n, edges, s):
    inf = 10 ** 100
    dist = [inf] * n
    dist[s] = 0
    for _ in range(n - 1):
        any_relaxed = False
        for v, to, w in edges:
            if dist[v] != inf and dist[to] > dist[v] + w:
                dist[to] = dist[v] + w
                any_relaxed = True
        if not any_relaxed:
            break
    return dist
