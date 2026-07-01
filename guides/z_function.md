# Z-Function

## English

### Idea
`z[i]` is the longest prefix of the whole string that starts at `i`. The algorithm keeps the rightmost matched segment and reuses it.

### Template
```cpp
int l = 0, r = 0;
for (int i = 1; i < n; i++) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
}
```

### When to use
- pattern matching;
- prefix matches from all positions;
- string periods;
- compression-like tasks.

### Common mistakes
- forgetting that `z[0]` is usually `0`;
- wrong separator in `pattern + "#" + text`;
- off-by-one when updating `r`.

Related: [library/cplib/strings.hpp](../library/cplib/strings.hpp)

## Русский

### Идея
`z[i]` показывает, сколько символов начиная с `i` совпадает с началом строки. Это удобно, когда нужно быстро знать все совпадения с префиксом.

### Когда использовать
- найти все вхождения строки;
- проверить период;
- сравнить префикс со всеми суффиксами;
- иногда проще, чем префикс-функция.

### Частые ошибки
- считать `z[0] = n`, когда остальной код ждет `0`;
- неверно обновить границы `[l, r]`;
- забыть вычесть длину образца при ответе.
