# Competitive Programming Library

A personal CP base: algorithms, snippets, notes, guides, templates, and contest solutions in one clean place.

This repository is written in CP style, not production C++. The code is short, copyable, and close to what you would actually type during Codeforces, ICPC, AtCoder, or school olympiad practice.

## English

### What is inside

- `library/` - includeable header-only CP library.
- `snippets/` - old and quick copy-paste snippets, including Sublime snippets.
- `guides/` - bilingual explanations with intuition, templates, mistakes, and links.
- `notes/` - more personal, human notes for revision.
- `contests/` - contest solutions kept separate from the library.
- `templates/` - base C++ contest templates.

### Repository map

```text
Competitive-programming/
├── library/
│   ├── cplib.hpp
│   └── cplib/
│       ├── basic.hpp
│       ├── data_structures.hpp
│       ├── graph.hpp
│       ├── dp.hpp
│       ├── math.hpp
│       ├── strings.hpp
│       ├── geometry.hpp
│       ├── flows.hpp
│       └── trees.hpp
├── guides/
├── notes/
├── snippets/
│   ├── cpp/
│   ├── python/
│   └── sublime/
├── contests/
└── templates/
```

### Code style

The style is intentionally compact:

```cpp
#define all(a) (a).begin(), (a).end()
#define endl "\n"
#define vec vector
#define pii pair<int, int>
#define se second
#define fi first
#define pb push_back

typedef long long ll;
typedef long double ld;
```

Short names like `n`, `m`, `ans`, `cur`, `g`, `used`, `tin`, `dist`, `dp`, `pref`, `get`, `unite`, `dfs`, and `bfs` are preferred. This is a contest notebook, so the code avoids production-heavy architecture.

### How to use

For a full local include:

```cpp
#include "library/cplib.hpp"
```

For a single topic:

```cpp
#include <bits/stdc++.h>
#include "library/cplib/graph.hpp"
```

The algorithm headers live inside `namespace cplib`. Use `snippets/cpp/` only when you want a raw contest fragment to paste by hand.

Compile a solution:

```bash
g++ -std=c++17 -O2 -pipe -Wall -Wextra -o main main.cpp
```

On macOS, Apple clang may not support `bits/stdc++.h` or GNU PBDS. For contest-like compilation, use GNU g++.

### Added topics

Basic techniques, graph traversal, shortest paths, 0-1 BFS, MST, bridges, articulation points, SCC, TwoSAT, Euler paths, bipartite matching, DSU, rollback DSU, Fenwick tree, segment trees, lazy segtree, sparse table, Li Chao tree, monotonic stack, DP patterns, knapsack, LIS/count LIS, edit distance, digit DP, CHT, slope trick, modular arithmetic, CRT, combinatorics, sieve, mobius, factorization, Miller-Rabin, NTT convolution, matrix exponentiation, string matching, hashing, trie, Aho-Corasick, suffix array, Manacher, geometry basics, convex hull, flows, LCA, HLD, centroid decomposition, and tree rerooting.

### Roadmap

- Add tested examples for every `library/cplib/*.hpp` section.
- Add more advanced guides: SCC, bridges, LCA, flows, hashing collisions, DP optimizations.
- Gradually polish old snippets without changing their behavior.
- Add small input/output samples for popular algorithms.

## Русский

### Что это

Это личная база по спортивному программированию: библиотека алгоритмов, быстрые сниппеты, конспекты, гайды, шаблоны и решения контестов.

Код здесь написан в CP-стиле, а не в production-стиле. Он короткий, живой и рассчитан на быстрое копирование в задачу.

### Что внутри

- `library/` - подключаемая header-only CP-library.
- `snippets/` - быстрые заготовки и старые авторские куски кода.
- `guides/` - понятные bilingual-гайды с идеей и типичными ошибками.
- `notes/` - очеловеченные конспекты для повторения.
- `contests/` - решения задач, отдельно от библиотеки.
- `templates/` - базовые C++ шаблоны.

### Как пользоваться

Если нужна библиотека - подключай:

```cpp
#include "library/cplib.hpp"
```

Если нужен только один раздел:

```cpp
#include <bits/stdc++.h>
#include "library/cplib/data_structures.hpp"
```

Если нужен короткий кусок "прямо сейчас" - смотри `snippets/cpp/` или `snippets/sublime/`. Если забыл идею - открой `guides/` или `notes/`.

Компиляция:

```bash
g++ -std=c++17 -O2 -pipe -Wall -Wextra -o main main.cpp
```

На macOS стандартный `g++` часто является Apple clang и может не знать `bits/stdc++.h` и PBDS. Для контестного окружения лучше использовать GNU g++.

### Стиль

В решениях и сниппетах стиль короткий и авторский. В `library/cplib` стиль чуть чище: без `#define`, без `main`, без лишних `Edge`-структур, всё лежит в `namespace cplib` и подключается как обычная библиотека.

### Навигация

- Library index: [library/README.md](library/README.md)
- Guides index: [guides/README.md](guides/README.md)
- Notes index: [notes/README.md](notes/README.md)
- Snippets guide: [snippets/README.md](snippets/README.md)
- Template: [templates/cp_template.cpp](templates/cp_template.cpp)
