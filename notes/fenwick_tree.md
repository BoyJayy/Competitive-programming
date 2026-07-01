# Fenwick Tree Notes

## English

Fenwick tree is the small, fast friend of prefix sums. It supports:

- add value at one position;
- get prefix sum;
- get range sum by subtracting two prefixes.

The only trick is `i & -i`: it gives the size of the block controlled by index `i`.

```cpp
for (++i; i <= n; i += i & -i) t[i] += x;
for (++i; i > 0; i -= i & -i) res += t[i];
```

Fenwick is perfect for inversions: scan numbers, count how many previous values are greater, then add current value.

## Русский

Фенвик - это префиксные суммы, которые можно обновлять.

Снаружи удобно использовать 0-индексацию, но внутри структура живёт в 1-индексации:

- `add`: идём вверх `i += i & -i`;
- `sum`: идём вниз `i -= i & -i`.

Когда брать Фенвик:

- сумма на отрезке + точечные изменения;
- частоты значений;
- количество инверсий;
- `lower_bound` по префиксной сумме, если все значения неотрицательные.

Когда не брать:

- нужен минимум на отрезке с произвольными обновлениями;
- нужны сложные массовые изменения;
- операция не умеет "вычитаться".
