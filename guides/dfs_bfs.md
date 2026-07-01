# DFS and BFS

## English

### Idea
DFS dives deep and is great for structure. BFS expands by layers and gives shortest paths in an unweighted graph.

### DFS
```cpp
void dfs(int v) {
    used[v] = true;
    for (int to : g[v])
        if (!used[to]) dfs(to);
}
```

### BFS
```cpp
queue<int> q;
dist[s] = 0;
q.push(s);
while (!q.empty()) {
    int v = q.front(); q.pop();
    for (int to : g[v])
        if (dist[to] == INF) dist[to] = dist[v] + 1, q.push(to);
}
```

### Common mistakes
- recursion depth on a long chain;
- not clearing global arrays between tests;
- using BFS for weighted edges.

Related: [library/cplib/graph.hpp](../library/cplib/graph.hpp), [library/cplib/graph.hpp](../library/cplib/graph.hpp)

## Русский

### Идея
DFS удобен, когда нужно понять форму графа: компоненты, циклы, мосты, точки сочленения. BFS идет слоями, поэтому в невзвешенном графе сразу дает минимальное число ребер.

### Когда использовать
- DFS: компоненты, дерево обхода, времена входа;
- BFS: кратчайший путь без весов, расстояния от старта;
- оба: базовая проверка достижимости.

### Частые ошибки
- не обнулить `used`, `dist`, `timer`;
- забыть про 0/1-индексацию;
- пустить рекурсивный DFS на слишком глубокий граф без осторожности.
