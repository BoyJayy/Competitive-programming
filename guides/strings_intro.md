# Strings Intro

## English

### Idea
String algorithms usually avoid comparing substrings character by character. They precompute structure: prefix matches, Z-values, hashes, trie edges.

### Main tools
- prefix function and KMP for pattern search;
- Z-function for prefix matches from every position;
- hashing for fast substring comparison;
- trie for many words;
- Manacher for palindromes.

### Common mistakes
- 0-index offsets in pattern search;
- hash collisions without a plan;
- using `substr` inside loops;
- forgetting that `char` values affect hashing.

Related: [library/cplib/strings.hpp](../library/cplib/strings.hpp)

## Русский

### Идея
Строковые алгоритмы нужны, чтобы не сравнивать подстроки руками каждый раз. Мы заранее считаем информацию о совпадениях, а потом отвечаем быстро.

### Когда что брать
- найти образец в тексте: KMP или Z;
- сравнивать много подстрок: хэши;
- хранить много слов: trie;
- палиндромы: Manacher.

### Частые ошибки
- сдвиг ответа после склейки `pattern + "#" + text`;
- `substr` в цикле дает лишнюю асимптотику;
- один хэш может столкнуться, если задача строгая.
