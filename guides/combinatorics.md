# Combinatorics

## English

### Idea
Most CP combinatorics starts from factorials. If `mod` is prime, precompute `fact` and `invfact`, then `C(n, k)` is `O(1)`.

### Formula
```cpp
C(n, k) = fact[n] * invfact[k] % mod * invfact[n - k] % mod;
```

### When to use
- choose positions;
- count strings or paths;
- stars and bars;
- probability under modulo.

### Common mistakes
- forgetting `k < 0 || k > n`;
- using inverse factorials with non-prime mod;
- precomputing too small limit;
- double-counting symmetric objects.

Related: [library/cplib/math.hpp](../library/cplib/math.hpp)

## Русский

### Идея
Комбинаторика в контестах часто сводится к "выбрать места". Для биномиальных коэффициентов под простым модулем заранее считаем факториалы и обратные факториалы.

### Когда использовать
- количество путей в сетке;
- выбор подмножества;
- распределение объектов;
- строки с ограничениями.

### Частые ошибки
- не обработать `k > n`;
- забыть, что модуль должен быть простым для `pow(x, mod - 2)`;
- посчитать один и тот же объект несколько раз.
