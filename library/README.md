# CP Library

## English

This is now a real header-only CP library.

The rule is simple:

- `library/cplib.hpp` is the only all-in-one entry point.
- `library/cplib/*.hpp` are topic headers.
- Topic headers contain only algorithms and data structures inside `namespace cplib`.
- Topic headers do not contain `#include`, `#define`, global template macros, or `using namespace std`.
- Graph algorithms use normal CP containers like `vector<vector<int>>`, `vector<pair<int,long long>>`, and `tuple` instead of decorative `Edge` structs.

### Quick start

From the repository root:

```cpp
#include "library/cplib.hpp"

int main() {
    std::vector<int> a = {1, 3, 3, 7};
    int pos = cplib::lower_pos(a, 3);
}
```

If you copy only one topic header into a contest file, include the standard library yourself before it:

```cpp
#include <bits/stdc++.h>
#include "library/cplib/graph.hpp"

using namespace std;

int main() {
    vector<vector<pair<int, long long>>> g(n);
    auto dist = cplib::dijkstra(0, g);
}
```

### Header map

- `cplib/basic.hpp` - binary search, two pointers, prefix sums, difference array, compression, submasks, greedy helpers.
- `cplib/data_structures.hpp` - DSU, rollback DSU, Fenwick, range Fenwick, segment trees, lazy segtree, sparse tables, kth zero, Li Chao, monotonic helpers.
- `cplib/graph.hpp` - DFS/BFS, 0-1 BFS, components, topo sort, directed cycle, bipartite check, Dijkstra, Bellman-Ford, Floyd, Kruskal, Prim, bridges, articulation points, SCC, Hopcroft-Karp, TwoSAT, Euler path.
- `cplib/dp.hpp` - 1D/2D DP helpers, knapsack, subset sum, LIS/count LIS, edit distance, SOS DP, digit DP, divide-and-conquer layer, CHT, slope trick.
- `cplib/math.hpp` - gcd/lcm, extended gcd, CRT, modular helpers, sieve, phi, mobius, factorization, Miller-Rabin, combinations, matrix exponentiation, NTT convolution, polynomial inverse, Lagrange interpolation.
- `cplib/strings.hpp` - prefix function, KMP, Z-function, hash, trie, Manacher, suffix array, LCP array, Aho-Corasick.
- `cplib/geometry.hpp` - points, dot/cross, distances, segment intersection, polygon area, convex hull, point in polygon.
- `cplib/flows.hpp` - Dinic and min-cost max-flow.
- `cplib/trees.hpp` - LCA, kth ancestor, tree distance, Euler tour, subtree sizes, diameter, reroot distance sums, HLD, centroid decomposition.

### Style contract

Library headers are cleaner than snippets:

- no forced author template;
- no `#define vec vector`;
- no `inline`/`static` unless there is a real reason;
- no long comments inside algorithms;
- no classes where a function is enough;
- no standalone `main`.

### Compile check

```bash
cat > /tmp/check.cpp <<'CPP'
#include "library/cplib.hpp"
int main() {
    std::vector<int> a = {1, 2, 4};
    return cplib::lower_pos(a, 2) == 1 ? 0 : 1;
}
CPP
g++ -std=c++17 -O2 -I. /tmp/check.cpp
```

## Русский

Теперь `library/` - это нормальная подключаемая header-only библиотека, а не набор отдельных `.cpp`.

### Как подключать

Самый простой вариант:

```cpp
#include "library/cplib.hpp"
```

И дальше:

```cpp
auto dist = cplib::dijkstra(0, g);
cplib::DSU dsu(n);
```

Если нужен только один раздел:

```cpp
#include <bits/stdc++.h>
#include "library/cplib/data_structures.hpp"
```

Компонентные хедеры специально не содержат `#include`: так их удобно копировать в свой шаблон, где `bits/stdc++.h` уже есть.

### Важная идея

Библиотека - подключаемая и аккуратная. Сниппеты - быстрые голые фрагменты для копирования. Контестные решения - отдельно, их не надо превращать в библиотеку.

### Как добавлять новый алгоритм

1. Положи его в подходящий `library/cplib/*.hpp`.
2. Оберни в `namespace cplib`.
3. Не добавляй `#include`, `#define`, `main`, общий шаблон.
4. Если структура не нужна - пиши функцию.
5. Для графовых рёбер используй `pair`/`tuple`, если отдельный тип ничего не упрощает.
6. Добавь объяснение в `guides/`, если алгоритм не очевидный.
