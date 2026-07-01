# Snippets

## English

Snippets are quick contest fragments, not a formal library.

The intended shape of a snippet:

- only the algorithm or small helper;
- no full template;
- no decorative comments;
- no unnecessary `inline` or `static`;
- no `main`, unless the snippet is explicitly a full example;
- short CP names are fine.
- use `template <typename T>` when the same snippet should work for `int`, `long long`, `double`, or another value type.

Use `library/` when you want a clean includeable header. Use `snippets/` when you want to paste one known trick fast.

### Current folders

- `cpp/` - old author snippets, now with English filenames.
- `python/` - small Python snippets kept separate from C++.
- `sublime/` - editor snippets/triggers.

### Cleanup rule

When touching an old snippet, trim it toward the pure form:

```cpp
template <typename T, typename E>
T binpow_mod(T a, E b, T mod) {
    T ans = 1 % mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
```

## Русский

Сниппеты - это быстрые куски для вставки в задачу. Не библиотека, не шаблон, не отдельная программа.

Хороший сниппет:

- содержит сам алгоритм;
- не тащит `#include` и весь template без нужды;
- не содержит `main`, если это не пример;
- не использует `inline/static` просто по привычке;
- использует `template <typename T>`, если алгоритм естественно работает с разными типами значений;
- короткий и легко копируется.

Если нужен аккуратный подключаемый код - бери `library/cplib.hpp`. Если нужен фрагмент на скорость - бери `snippets/cpp/` или `snippets/python/`.
