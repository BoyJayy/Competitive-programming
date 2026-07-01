# Knapsack

## English

### Idea
For each item decide: take it or skip it. In 0/1 knapsack each item can be used once, so sums are iterated backwards.

### Template
```cpp
vector<int> dp(s + 1);
for (int i = 0; i < n; i++)
    for (int j = s; j >= w[i]; j--)
        dp[j] = max(dp[j], dp[j - w[i]] + cost[i]);
```

### When to use
- choose subset under weight limit;
- subset sum;
- exact or best possible total;
- small total weight or sum.

### Common mistakes
- iterating forward in 0/1 knapsack;
- using `O(n * sum)` when `sum` is huge;
- mixing value and weight dimensions.

Related: [library/cplib/dp.hpp](../library/cplib/dp.hpp)

## Русский

### Идея
Для каждого предмета есть два выбора: взять или не взять. Если предмет можно взять один раз, идем по сумме справа налево, чтобы не использовать его повторно в этом же шаге.

### Когда использовать
- ограничение по весу небольшое;
- нужно набрать сумму;
- нужно максимум стоимости;
- можно оптимизировать память до одного массива.

### Частые ошибки
- идти слева направо в 0/1 варианте;
- перепутать "рюкзак по весу" и "рюкзак по стоимости";
- не проверить лимиты на `sum`.
