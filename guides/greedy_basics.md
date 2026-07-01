# Greedy Basics

## English

### Idea
Greedy means making a local choice and proving it never hurts. The proof usually comes from exchange: take an optimal answer and replace one piece with the greedy choice.

### Classic patterns
- sort by ending time;
- take the smallest available resource;
- process events from left to right;
- keep the best current candidate in a heap.

### Common mistakes
- believing the first nice idea without proof;
- sorting by the wrong key;
- ignoring tie-breaks;
- using greedy where DP is needed.

Related: [library/cplib/basic.hpp](../library/cplib/basic.hpp)

## Русский

### Идея
Жадность - это не "берем максимум и молимся". Это выбор, который можно доказать: если оптимальное решение выбрало что-то другое, мы заменим его на наш выбор и не ухудшим ответ.

### Когда использовать
- интервалы и расписания;
- минимизация ожидания;
- задачи с ресурсами и очередью;
- когда есть ясный порядок обработки.

### Частые ошибки
- не доказать локальный выбор;
- сортировать по началу вместо конца;
- забыть, что равные элементы тоже требуют аккуратного порядка.
