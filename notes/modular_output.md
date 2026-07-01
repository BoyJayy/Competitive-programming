# Modular Output

## English

Modulo is friendly until subtraction appears.

Use a small normalizer:

```cpp
long long norm(long long x) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}
```

Then write:

```cpp
ans = norm(a - b);
ans = (ans + c) % mod;
```

For multiplication, promote to `long long` before multiplying if values may be `int`.

Division under prime modulo:

```cpp
a / b == a * binpow(b, mod - 2) % mod
```

Only when `b` and `mod` are coprime.

## Русский

Главная ловушка модуля - отрицательный остаток.

В C++ выражение `(-3) % 5` не станет `2`. Поэтому после вычитания лучше нормализовать:

```cpp
ans = (a - b + mod) % mod;
```

Если вычитаний много, удобнее функция `norm`.

Деление по модулю - это не `/`. Под простым модулем делим через обратный элемент:

```cpp
ans = a * binpow(b, mod - 2) % mod;
```

Типичные ошибки:

- забыть `+ mod` после вычитания;
- умножить два `int` и получить переполнение до взятия модуля;
- взять обратный элемент от числа, не взаимно простого с модулем.
