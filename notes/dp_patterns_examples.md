# DP Patterns With Examples

## English

### 1D DP
Use when the past can be compressed into one index.

Example: minimum cost to reach `i`, number of ways to make sum `s`.

### 2D DP
Use when one index is not enough: grid position, two strings, item and sum.

Example: edit distance, grid paths, knapsack table.

### Tree DP
Each vertex collects answers from children.

Typical state: `dp[v][0/1]`, subtree size, best answer inside subtree.

### Bitmask DP
Use when `n <= 20` and a subset is the state.

Example: TSP, assignment, SOS DP.

### Digit DP
Use when counting numbers up to `N` with digit restrictions.

State usually contains position, current value, and `tight`.

## Русский

### 1D DP
Один индекс хватает, когда будущее зависит от позиции или суммы.

Примеры: лестница, количество способов набрать сумму.

### 2D DP
Нужно два измерения: клетка в таблице, две строки, предмет и вместимость.

Примеры: расстояние Левенштейна, пути в сетке, классический рюкзак.

### DP на дереве
Вершина собирает ответы из сыновей. Очень часто есть состояния "берём вершину" и "не берём вершину".

### DP по маске
Если `n` маленькое, множество можно хранить битами. Это дорого, но честно: `O(2^n * n)`.

### Digit DP
Считаем числа до `N`, не перебирая их. Флаг `tight` говорит, привязаны ли мы ещё к префиксу числа `N`.

Главный совет: сначала напиши наивную динамику. Оптимизация без понятного состояния почти всегда превращается в шум.
