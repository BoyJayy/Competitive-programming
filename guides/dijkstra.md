# Dijkstra

## English

### Idea
Dijkstra takes the not-yet-processed vertex with the smallest known distance. It works only with non-negative edge weights.

### Template
```cpp
priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
dist[s] = 0;
q.push({0, s});
while (!q.empty()) {
    auto [d, v] = q.top(); q.pop();
    if (d != dist[v]) continue;
    for (auto [to, w] : g[v])
        if (dist[to] > d + w) dist[to] = d + w, q.push({dist[to], to});
}
```

### Common mistakes
- negative edges;
- `int` overflow in distances;
- not skipping stale heap states;
- building an undirected graph as directed by accident.

Related: [library/cplib/graph.hpp](../library/cplib/graph.hpp)

## Русский

### Идея
Мы всегда берем вершину с минимальной текущей дистанцией. Если веса неотрицательные, эта дистанция уже окончательная: более короткий путь позже не появится.

### Когда использовать
- кратчайшие пути из одной вершины;
- веса ребер неотрицательные;
- граф разреженный, хочется `O(m log n)`.

### Частые ошибки
- запустить на отрицательных ребрах;
- хранить расстояния в `int`;
- забыть `if (d != dist[v]) continue;`.
