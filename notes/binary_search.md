# Binary Search Notes

## English

Binary search is easiest when you stop thinking about "middle element" and start thinking about a border.

Keep an invariant:

- `l` is definitely bad;
- `r` is definitely good;
- the answer is between them.

```cpp
int l = -1, r = n;
while (r - l > 1) {
    int m = (l + r) / 2;
    if (ok(m)) r = m;
    else l = m;
}
```

For arrays:

- first `a[i] >= x` is `lower_bound`;
- first `a[i] > x` is `upper_bound`.

For answers:

- "minimum time", "minimum power", "minimum length" usually means first true;
- "maximum possible value" usually means last true.

Small mental check: before writing the loop, test `ok` on a tiny example and make sure it changes only once.

## Русский

Бинарный поиск проще всего воспринимать как поиск границы.

Не "ищем середину", а держим смысл:

- `l` точно плохой;
- `r` точно хороший;
- ответ где-то между ними.

Если условие не монотонное, бинарный поиск не спасёт. Например, если `ok(x)` бывает `true, false, true`, границы нет.

Для массива:

- `lower_bound` - первая позиция, где `a[i] >= x`;
- `upper_bound` - первая позиция, где `a[i] > x`.

Для ответа:

- "минимальное время, при котором успеваем" - первая правда;
- "максимальное значение, которое можно взять" - последняя правда.

Типичная ошибка - не проверить края. Если ответа может не быть, заранее реши, что должен вернуть код.
