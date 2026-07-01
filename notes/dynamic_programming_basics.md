# Dynamic Programming Basics

## English

DP starts with a sentence, not with a formula.

Good:

`dp[i]` is the minimum cost to reach position `i`.

Bad:

`dp[i] = min(dp[i - 1], dp[i - 2]) + a[i]`, written before understanding what `dp[i]` means.

The usual checklist:

1. What does the state mean?
2. What are the base cases?
3. From which smaller states can we come here?
4. In what order should states be processed?
5. Where is the answer stored?

Tiny example:

```cpp
dp[0] = 0;
for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1] + cost[i];
    if (i > 1) dp[i] = min(dp[i], dp[i - 2] + cost[i]);
}
```

If the transition is too slow, look for prefix sums, monotonic queue, divide and conquer optimization, or another state.

## Русский

Динамика начинается не с формулы, а со смысла.

Хорошее состояние звучит как обычная фраза:

`dp[i]` - минимальная стоимость добраться до позиции `i`.

После этого переход обычно сам просится: в `i` можно прийти из `i - 1` или `i - 2`.

Мини-чеклист:

1. Что означает состояние?
2. Какие базовые значения?
3. Откуда можно перейти?
4. В каком порядке считать?
5. Где лежит ответ?

Если решение получается `O(n^3)`, не паникуй. Часто оно сначала и должно быть таким. Потом смотри, что именно повторяется: сумма на отрезке, минимум на окне, лучший `j`, переход по маске.

Самая частая ошибка - хранить в состоянии слишком мало информации. Вторая по частоте - хранить слишком много и убить память.
