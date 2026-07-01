# Geometry Basics

## English

### Idea
Geometry becomes much calmer when points are vectors. Dot product answers "projection/angle", cross product answers "turn/area".

### Core formulas
```cpp
dot(a, b) = a.x * b.x + a.y * b.y;
cross(a, b) = a.x * b.y - a.y * b.x;
```

### When to use
- orientation of three points;
- segment intersection;
- polygon area;
- distances and projections.

### Common mistakes
- using floating point when integer cross product is enough;
- wrong sign of cross product;
- forgetting collinear cases in segment intersection;
- too small or too large `EPS`.

Related: [library/cplib/geometry.hpp](../library/cplib/geometry.hpp)

## Русский

### Идея
Точку удобно воспринимать как вектор. Скалярное произведение говорит про угол и проекцию, векторное - про поворот, площадь и ориентацию.

### Когда использовать
- понять, слева или справа точка от отрезка;
- пересечение отрезков;
- площадь многоугольника;
- расстояния.

### Частые ошибки
- не разобрать случай, когда точки лежат на одной прямой;
- сравнивать `double` через `==`;
- перепутать порядок точек в `cross`.
