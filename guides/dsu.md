# DSU

## English

### Idea
DSU keeps disjoint sets and answers "are these vertices already in the same component?" almost instantly.

### Template
```cpp
int get(int v) {
    return p[v] == v ? v : p[v] = get(p[v]);
}

bool unite(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return true;
}
```

### When to use
- Kruskal MST;
- dynamic connectivity with only additions;
- grouping equal objects;
- offline queries.

### Common mistakes
- forgetting path compression;
- updating size of the wrong root;
- trying to delete edges without rollback/offline trick.

Related: [library/cplib/data_structures.hpp](../library/cplib/data_structures.hpp)

## Русский

### Идея
СНМ хранит компоненты связности. `get(v)` возвращает лидера компоненты, а `unite(a, b)` склеивает две компоненты, если они разные.

### Когда использовать
- минимальное остовное дерево;
- добавление ребер и проверка связности;
- задачи "склеить элементы по условию";
- offline-решения с откатами.

### Частые ошибки
- склеивать не лидеров, а исходные вершины;
- забыть `sz/rank`;
- ждать поддержки удаления ребра от обычного DSU.
