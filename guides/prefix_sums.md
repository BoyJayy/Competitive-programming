# Prefix Sums

## English

### Idea
Precompute sums before every position. Then `sum(l, r)` becomes one subtraction.

### Template
```cpp
vector<long long> pref(n + 1);
for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
long long cur = pref[r + 1] - pref[l];
```

### When to use
- many range sum queries;
- subarray sums;
- 2D rectangle sums;
- DP transitions that need fast segment totals.

### Common mistakes
- mixing 0-indexed `a` and 1-indexed `pref`;
- using `int` for large sums;
- forgetting inclusion-exclusion in 2D.

Related: [library/cplib/basic.hpp](../library/cplib/basic.hpp)

## Русский

### Идея
`pref[i]` хранит сумму первых `i` элементов. Тогда сумма `[l, r]` равна `pref[r + 1] - pref[l]`. Это маленькая идея, которая убирает лишний цикл почти из каждой второй задачи.

### Когда использовать
- много запросов суммы;
- нужно быстро получать сумму подмассива;
- прямоугольники в матрице;
- оптимизация простого DP.

### Частые ошибки
- неверно выбрать, включается ли правая граница;
- хранить сумму в `int`, когда нужен `long long`;
- забыть, что 2D-префикс строится с лишевой нулевой строкой и колонкой.
