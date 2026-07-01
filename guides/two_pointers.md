# Two Pointers

## English

### Idea
Keep a segment `[l, r]` and move each border only forward. If the segment became bad, move `l` until it is good again.

### When to use
- subarrays with positive numbers;
- longest or shortest segment with a condition;
- distinct elements inside a window;
- merging two sorted arrays.

### Template
```cpp
int l = 0;
long long sum = 0, ans = 0;
for (int r = 0; r < n; r++) {
    sum += a[r];
    while (sum > s) sum -= a[l++];
    ans += r - l + 1;
}
```

### Common mistakes
- using it when negative numbers break monotonicity;
- forgetting that every pointer should move only one way;
- counting segments before restoring the invariant.

Related: [library/cplib/basic.hpp](../library/cplib/basic.hpp)

## Русский

### Идея
Два указателя работают, когда окно можно чинить движением левой границы вправо. Каждый элемент добавляется и удаляется максимум один раз, поэтому получается `O(n)`.

### Когда использовать
- сумма на отрезке с положительными числами;
- максимальное окно без повторов;
- минимальный отрезок, который уже покрывает условие;
- две отсортированные последовательности.

### Частые ошибки
- пытаться применять к суммам с отрицательными числами;
- считать ответ до того, как окно снова стало корректным;
- случайно двигать `l` назад.
