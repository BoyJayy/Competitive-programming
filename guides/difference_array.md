# Difference Array

## English

### Idea
Range updates can be stored only at borders: add `x` at `l`, subtract `x` after `r`, then restore the array with prefix sums.

### Template
```cpp
diff[l] += x;
diff[r + 1] -= x;
for (int i = 0; i < n; i++) {
    cur += diff[i];
    a[i] += cur;
}
```

### When to use
- many range add operations;
- final array is needed only after all updates;
- offline painting or events.

### Common mistakes
- writing to `r + 1` outside the array;
- using difference array when queries are online;
- forgetting to restore by prefix sum.

Related: [library/cplib/basic.hpp](../library/cplib/basic.hpp)

## Русский

### Идея
Если нужно много раз прибавить число на отрезке, не надо трогать каждый элемент. Достаточно отметить начало и конец изменения, а потом одним проходом собрать настоящий массив.

### Когда использовать
- все изменения известны заранее;
- запросов суммы во время изменений нет;
- нужно быстро применить много `add(l, r, x)`.

### Частые ошибки
- забыть про размер `n + 1`;
- перепутать включительную и полуоткрытую границу;
- ждать, что структура ответит на запрос между обновлениями.
