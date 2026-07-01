# Fenwick Tree

## English

### Idea
Fenwick tree keeps prefix sums in a compact binary form. It is shorter than a segment tree when you only need prefix/range sums with point updates.

### Template
```cpp
void add(int i, long long x) {
    for (++i; i <= n; i += i & -i) t[i] += x;
}

long long sum(int i) {
    long long res = 0;
    for (++i; i > 0; i -= i & -i) res += t[i];
    return res;
}
```

### Common mistakes
- forgetting internal 1-indexing;
- calling `sum(l, r)` without subtracting prefix;
- using Fenwick for non-invertible operations.

Related: [library/cplib/data_structures.hpp](../library/cplib/data_structures.hpp)

## Русский

### Идея
Фенвик - короткая структура для префиксных сумм. Снаружи можно жить в 0-индексации, а внутри делать `++i`.

### Когда использовать
- точечное обновление;
- сумма на префиксе или отрезке;
- инверсии;
- динамические частоты.

### Частые ошибки
- забыть перейти к 1-индексации;
- пытаться хранить минимум без ограничений;
- перепутать направление `i += i & -i` и `i -= i & -i`.
