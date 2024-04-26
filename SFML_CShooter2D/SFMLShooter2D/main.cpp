#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>

using namespace sf;

class Bullet {
public:
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;


	Bullet(float radius = 5.f) : currVelocity(0.f, 0.f), maxSpeed(20.f) {
		this->shape.setPointCount(3);
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Cyan);
	}
};

int main() {
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "SFML 2D Shooter");
	window.setFramerateLimit(60);

	// Счётчик
	int counter = 1;

	// Игрок
	CircleShape player(25.f);
	player.setPointCount(4);
	player.setFillColor(Color::Yellow);
	
	// Враг
	RectangleShape enemy;
	enemy.setFillColor(Color::White);
	enemy.setSize(Vector2f(30.f, 30.f));
	int spawnCounter = 20;

	std::vector<RectangleShape> enemies;

	// Шрифт
	Font font;
	font.loadFromFile("Fonts/Roboto-Bold.ttf");

	// Текст
	Text text("", font, 24);
	text.setFillColor(Color::Green);

	// Пули
	Bullet b1;
	std::vector<Bullet> bullets;

	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) { 
			if (event.type == sf::Event::Closed) { 
				window.close();
			}
		}

		// Добавляем текст с привязкой к позиции игрока
		text.setPosition(player.getPosition().x + 60, player.getPosition().y);

		// Векторы
		playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm = aimDir / (static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2))));

		// Игрок
		if (Keyboard::isKeyPressed(Keyboard::A)) { player.move(-10.f, 0.f); }
		if (Keyboard::isKeyPressed(Keyboard::D)) { player.move(10.f, 0.f); }
		if (Keyboard::isKeyPressed(Keyboard::W)) { player.move(0.f, -10.f); }
		if (Keyboard::isKeyPressed(Keyboard::S)) { player.move(0.f, 10.f); }

		// Враги
		if (spawnCounter < 20) { spawnCounter++; }
		if (spawnCounter >= 20 && enemies.size() < 50) { 
			enemy.setPosition(Vector2f(rand() % window.getSize().x, rand() % window.getSize().x));
			enemies.push_back(RectangleShape(enemy));
			spawnCounter = 0;
		}

		// Выстрелы
		if (Mouse::isButtonPressed(Mouse::Left)) {
			b1.shape.setPosition(playerCenter);
			b1.currVelocity = aimDirNorm * b1.maxSpeed;

			bullets.push_back(Bullet(b1));
		}

		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].shape.move(bullets[i].currVelocity);

			// Выход за границы
			if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
				|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y) {
				bullets.erase(bullets.begin() + i);
			}
			else {
				// Враги
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds())) {
						bullets.erase(bullets.begin() + i);
						enemies.erase(enemies.begin() + k);

						// Счётчик врагов
						std::string str = "Scores : " + std::to_string(counter++);
						text.setString(str);
						break;
					}
				}
			}
		}


		// Отрисовка
		window.clear();

		window.draw(text);

		for (size_t i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i]);
		}

		window.draw(player);

		for (size_t i = 0; i < bullets.size(); i++) {
			window.draw(bullets[i].shape);
		}

		window.display();
	}

	return 0;
}