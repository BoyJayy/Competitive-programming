# Segment Tree

## English

### Idea
A segment tree stores answers for segments. A query splits into `O(log n)` stored pieces, and a point update changes one path from leaf to root.

### When to use
- range sum/min/max queries;
- point updates;
- range updates with lazy propagation;
- searching by prefix or kth zero.

### Minimal shape
```cpp
get(v, l, r, ql, qr);
upd(v, l, r, pos, x);
```

### Common mistakes
- wrong neutral value;
- forgetting to recalc parent after update;
- mixing inclusive and exclusive ranges;
- making lazy propagation before the simple version is correct.

Related: [library/cplib/data_structures.hpp](../library/cplib/data_structures.hpp)

## Русский

### Идея
Дерево отрезков хранит ответ на больших и маленьких кусках массива. Запрос разбивается на несколько таких кусков, поэтому работает за `O(log n)`.

### Когда использовать
- запросы на отрезке;
- изменения элементов;
- нужно быстрее, чем пересчитывать отрезок руками;
- есть ассоциативная операция: сумма, минимум, максимум, gcd.

### Частые ошибки
- нейтральный элемент выбран неверно;
- границы `[l, r]` перепутаны;
- после обновления не пересчитали вершину;
- добавить lazy раньше, чем понятна обычная версия.
