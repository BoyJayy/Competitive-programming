# Modular Arithmetic

## English

### Idea
Modulo keeps numbers small, but subtraction and division need care. Addition and multiplication are simple; division means multiplying by inverse when it exists.

### Template
```cpp
const long long mod = 1e9 + 7;

long long norm(long long x) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}
```

### Common mistakes
- negative value after subtraction;
- using `/` instead of modular inverse;
- multiplying two `int` values before casting;
- assuming inverse exists when `gcd(x, mod) != 1`.

Related: [library/cplib/math.hpp](../library/cplib/math.hpp)

## Русский

### Идея
Модульная арифметика нужна, чтобы числа не разрастались. Но `a - b` может стать отрицательным, а деление по модулю не является обычным делением.

### Когда использовать
- количество способов;
- комбинаторика;
- хэши;
- большие степени.

### Частые ошибки
- вывести отрицательный остаток;
- делить через `/`;
- забыть `long long` в умножении;
- брать обратный элемент при составном модуле без проверки.
