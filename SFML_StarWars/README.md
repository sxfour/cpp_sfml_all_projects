# ![icon](https://github.com/sxfour/SFMLStarWars/assets/112577182/687545bf-3155-4d0d-9a89-7bf236690239) SFMLStarWars
# Первая из моих игр с использованием библиотеки SFML и ООП на C++ #1

https://github.com/sxfour/SFMLStarWars/assets/112577182/b82f9d6a-a812-4ffb-965f-400dd10e84f4

* Враги используют Follow Player из разницы координат игрока и врага.
* Верхняя панель сердечек использует переменную для счёта и переключает на другую (в случае поражение игрока).
![panel1](https://github.com/sxfour/SFMLStarWars/assets/112577182/404bf21c-5bea-44b6-a5fd-537a00f5b60e)

* Background parallax.
* Простая анимация персонажей.

![player](https://github.com/sxfour/SFMLStarWars/assets/112577182/21ddf6c0-d9fd-4735-9414-482a58abcec2)


# Эффект движения заднего фона (background parallax)
* Для достижение данного эффекта, я решил использовать базовый шейдер через загрузку в память SFML
  т.к использование двух фонов одновременно и смена их по координатам приводила к появлению полос.
  
![tempsnip](https://github.com/sxfour/SFMLStarWars/assets/112577182/a0445b55-991f-4d0f-a0d5-3dacf1a2efcf)

# Анимация персонажей
* Создано через простое условие в основном цикле программы.
* Смена происходит каждую секунду - через специальную переменную подсчёта псевдоигрового времени.

![изображение](https://github.com/sxfour/SFMLStarWars/assets/112577182/87a683fb-497d-410f-b073-ccc9c59177b3)

* frameTimer конвертируем offset заднего фона * 15 и % 2 получаем на выходе 0 или 1 каждую секунду (чётность)

![изображение](https://github.com/sxfour/SFMLStarWars/assets/112577182/62026f44-3d5c-4253-88f9-8eb83d374aa6)

# Изменение скорости врагов, зайти -> Moves.cpp
![изображение](https://github.com/sxfour/SFMLStarWars/assets/112577182/26a53b3a-f6ab-487d-acc9-d6c1bd246b50)

# Движение врагов в сторону игрока (follow player)
* Для реализации этого действия, достаточно вычислить разницу координат между игроком и врагом, задав скорость движения.

![изображение](https://github.com/sxfour/SFMLStarWars/assets/112577182/610f296e-dad8-4863-9342-dde80d26d356)

# Управление и пауза
https://github.com/sxfour/SFMLStarWars/assets/112577182/ec788ca5-acba-4978-9b93-225685cc4955
