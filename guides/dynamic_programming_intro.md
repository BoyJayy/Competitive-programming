# Dynamic Programming Intro

## English

### Idea
DP is remembering answers for smaller states. A good state has enough information to continue, but not extra baggage.

### How to build it
1. Define `dp[state]`.
2. Pick base states.
3. Write transition.
4. Choose iteration order.
5. Read the answer.

### Tiny example
```cpp
dp[0] = 1;
for (int s = 0; s <= sum; s++)
    for (int x : a)
        if (s + x <= sum) dp[s + x] += dp[s];
```

### Common mistakes
- state misses important information;
- transition uses not-yet-ready values;
- base case is absent;
- memory is too big for constraints.

Related: [library/cplib/dp.hpp](../library/cplib/dp.hpp)

## Русский

### Идея
Динамика - это когда мы не пересчитываем одно и то же. Нужно придумать состояние, которое описывает "где мы сейчас" и содержит все, что понадобится дальше.

### Как думать
Сначала напиши смысл `dp`, не формулу. Например: `dp[i]` - минимальная цена дойти до ступеньки `i`. После этого переход обычно становится заметно проще.

### Частые ошибки
- начать с формулы, не понимая смысла состояния;
- забыть базу;
- обновлять `dp` в неправильном порядке;
- сделать состояние слишком большим.
