# Binary Search

## English

### Idea
Binary search is not only "find x in sorted array". The stronger idea is: if answers are split into a bad part and a good part, jump to the border in `O(log n)`.

### When to use
- sorted arrays;
- "minimum x such that condition is true";
- "maximum x such that condition is true";
- answer search with a monotonic predicate.

### Template
```cpp
int l = -1, r = n;
while (r - l > 1) {
    int m = (l + r) / 2;
    if (ok(m)) r = m;
    else l = m;
}
```

### Common mistakes
- `ok` is not monotonic;
- forgetting whether `r` or `l` is the answer;
- overflow in `(l + r) / 2` for huge numbers;
- off-by-one on empty answer.

Related: [library/cplib/basic.hpp](../library/cplib/basic.hpp)

## Русский

### Идея
Бинарный поиск - это поиск границы. Слева могут лежать плохие значения, справа хорошие, и нам нужна первая хорошая позиция. Поэтому важно не "угадывать середину", а правильно написать `ok`.

### Когда использовать
- массив отсортирован;
- нужно первое число, при котором условие выполняется;
- нужно последнее число, при котором условие еще выполняется;
- ответ можно проверить за `O(f(n))`, а сам ответ монотонный.

### Частые ошибки
- условие `ok` на самом деле не монотонное;
- перепутаны левая и правая границы;
- `l`, `r` выбраны так, что инвариант не держится;
- вещественный бинпоиск крутится без фиксированного числа итераций.
