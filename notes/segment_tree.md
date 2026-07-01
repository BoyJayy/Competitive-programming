# Segment Tree Notes

## English

A segment tree is worth learning once and then reusing forever.

The shape:

- leaf stores one array element;
- internal vertex stores merged answer of two children;
- query either fully takes a vertex, skips it, or goes deeper.

For sum:

```cpp
t[v] = t[v * 2] + t[v * 2 + 1];
```

For minimum:

```cpp
t[v] = min(t[v * 2], t[v * 2 + 1]);
```

The operation must be associative. That is why sum, min, max, gcd work naturally.

## Русский

Дерево отрезков кажется большим, пока не увидеть его форму:

- лист - один элемент;
- вершина - ответ на свой отрезок;
- запрос разбивается на несколько вершин.

Самое важное - не код, а нейтральный элемент:

- сумма: `0`;
- минимум: `INF`;
- максимум: `-INF`;
- gcd: `0`.

Если обычная версия работает, можно добавлять lazy propagation. Если обычная версия ещё плавает по границам, lazy только умножит ошибки.

Частые ошибки:

- забыть пересчитать вершину после обновления;
- неправильно обработать "нет пересечения";
- смешать `[l, r]` и `[l, r)`.
