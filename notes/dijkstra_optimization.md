# Dijkstra Optimization Notes

## English

The slow version searches the minimum unused vertex by scanning all vertices: `O(n^2)`.

The contest version uses a priority queue:

```cpp
priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
q.push({0, s});
while (!q.empty()) {
    auto [d, v] = q.top();
    q.pop();
    if (d != dist[v]) continue;
}
```

Why the `continue` matters: the heap can contain old distances. We do not delete them immediately; we just ignore stale states.

Use:

- `O(m log n)` for sparse graphs;
- `long long` for distances;
- only non-negative weights.

## Русский

Обычная Дейкстра за `O(n^2)` каждый раз ищет ближайшую вершину полным проходом. На разреженном графе это жалко: рёбер мало, а мы всё равно сканируем всё.

Поэтому берём `priority_queue`. Когда расстояние улучшается, просто кладём новую пару `(dist, v)`.

Старые пары остаются в очереди, поэтому нужна строка:

```cpp
if (d != dist[v]) continue;
```

Она говорит: "это уже не актуальная версия вершины".

Частые ошибки:

- запустить на отрицательных рёбрах;
- хранить `dist` в `int`;
- забыть, что для неориентированного графа ребро добавляется в обе стороны.
