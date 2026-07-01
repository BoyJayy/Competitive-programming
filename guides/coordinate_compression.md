# Coordinate Compression

## English

### Idea
Replace large values with their order among all used values. The relative order stays the same, but indices become small.

### Template
```cpp
vector<int> b = a;
sort(b.begin(), b.end());
b.erase(unique(b.begin(), b.end()), b.end());
for (int& x : a) x = lower_bound(b.begin(), b.end(), x) - b.begin();
```

### When to use
- Fenwick or segment tree over huge coordinates;
- offline queries;
- sweep line;
- values up to `1e9`, but only `n` of them matter.

### Common mistakes
- compressing online values that appear later;
- losing original values when they are still needed;
- forgetting duplicates before `lower_bound`.

Related: [library/cplib/basic.hpp](../library/cplib/basic.hpp)

## Русский

### Идея
Если координаты огромные, но разных значений мало, заменяем каждое значение на его номер в отсортированном списке уникальных значений.

### Когда использовать
- Фенвик по координатам до `1e9`;
- дерево отрезков по сжатым точкам;
- sweep line;
- offline-запросы.

### Частые ошибки
- удалить исходные значения, хотя они еще нужны;
- забыть `unique`;
- сжать только часть координат.
