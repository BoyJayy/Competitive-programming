# Prefix Function

## English

### Idea
`p[i]` is the length of the longest proper prefix of `s[0..i]` that is also a suffix. KMP uses it to continue matching without going back in the text.

### Template
```cpp
vector<int> p(n);
for (int i = 1; i < n; i++) {
    int j = p[i - 1];
    while (j > 0 && s[i] != s[j]) j = p[j - 1];
    if (s[i] == s[j]) j++;
    p[i] = j;
}
```

### When to use
- pattern search;
- borders of a string;
- periods;
- prefix/suffix overlaps.

### Common mistakes
- forgetting "proper" prefix;
- not falling back with `p[j - 1]`;
- wrong answer index after `t + "#" + s`.

Related: [library/cplib/strings.hpp](../library/cplib/strings.hpp)

## Русский

### Идея
Префикс-функция говорит: какой самый длинный префикс уже совпал с суффиксом текущего префикса строки. Если символ не подошёл, мы не начинаем с нуля, а откатываемся к меньшей границе.

### Когда использовать
- поиск подстроки;
- периоды строки;
- задачи на границы;
- склейка строк с максимальным перекрытием.

### Частые ошибки
- считать всю строку префиксом самой себя;
- забыть разделитель между образцом и текстом;
- перепутать индекс найденного вхождения.
