#include "Move.h"


// Движение игрока
void playerMove(Sprite& playerSprite, Vector2f& moveRec, Text& playerText) {
	playerSprite.move(moveRec);

	Vector2f playerPos = playerSprite.getPosition();

	playerText.setString(std::to_string(playerPos.x) + "\n" + std::to_string(playerPos.y));
	playerText.setPosition(playerPos.x, playerPos.y + 80);

	if (playerPos.x > 800) {
		playerSprite.setPosition(800, playerPos.y);
	}
	if (playerPos.x < 10) {
		playerSprite.setPosition(10, playerPos.y);
	}
	if (playerPos.y < 70) {
		playerSprite.setPosition(playerPos.x, 70);
	}
	if (playerPos.y > 510) {
		playerSprite.setPosition(playerPos.x, 510);
	}

	if ((playerPos.x > 800) && (playerPos.y < 510)) {
		playerSprite.setPosition(800, 70);
	}
	if ((playerPos.x > 800) && (playerPos.y > 70)) {
		playerSprite.setPosition(800, 510);
	}
	if ((playerPos.x < 10) && (playerPos.y < 70)) {
		playerSprite.setPosition(10, 70);
	}
	if ((playerPos.x < 10) && (playerPos.y > 510)) {
		playerSprite.setPosition(10, 510);
	}
}

// Движение врага к игроку
void enemy1Move(Sprite& playerSprite, Sprite& enemy1Sprite, Vector2f& moveEnemy1, int& lifes, Text& enemy1Text) {
	float randomX = (float)(rand() % 800) + 800;
	float randomY = (float)(rand() % 500) + 50;

	float playerPosY = playerSprite.getPosition().y;
	float playerPosX = playerSprite.getPosition().x;

	float enemy1PosY = enemy1Sprite.getPosition().y;
	float enemy1PosX = enemy1Sprite.getPosition().x;

	enemy1Text.setString(std::to_string(enemy1PosX) + "\n" + std::to_string(enemy1PosY));
	enemy1Text.setPosition(enemy1PosX, enemy1PosY + 80);

	moveEnemy1.y = (playerPosY - enemy1PosY) / 20;
	moveEnemy1.x = -8;

	enemy1Sprite.move(moveEnemy1);

	// Условие попадания врага по игроку
	if (((playerSprite.getGlobalBounds().left >= enemy1Sprite.getGlobalBounds().left) && (playerPosX <= enemy1PosX - 2))
		|| ((playerSprite.getGlobalBounds().top >= enemy1Sprite.getGlobalBounds().top) && (playerPosY <= enemy1PosY - 2))) {
		enemy1Sprite.setPosition(randomX, randomY);

		// Счётчик жизни
		lifes--;
	}

	// Выход за границы игровой области
	if (enemy1PosX < -200) {
		enemy1Sprite.setPosition(randomX, randomY);
	}
}

// Движение врага к игроку
void enemy2Move(Sprite& playerSprite, Sprite& enemy2Sprite, Vector2f& moveEnemy2, int& lifes, Text& enemy2Text) {
	float randomX = (float)(rand() % 1600) + 600;
	float randomY = (float)(rand() % 500) + 50;

	float playerPosY = playerSprite.getPosition().y;
	float playerPosX = playerSprite.getPosition().x;

	float enemy2PosY = enemy2Sprite.getPosition().y;
	float enemy2PosX = enemy2Sprite.getPosition().x;

	enemy2Text.setString(std::to_string(enemy2PosX) + "\n" + std::to_string(enemy2PosY));
	enemy2Text.setPosition(enemy2PosX, enemy2PosY + 80);

	moveEnemy2.y = (playerPosY - enemy2PosY) / 20;
	moveEnemy2.x = -10;

	enemy2Sprite.move(moveEnemy2);

	// Условие попадания врага по игроку
	if (((playerSprite.getGlobalBounds().left >= enemy2Sprite.getGlobalBounds().left) && (playerPosX <= enemy2PosX - 2))
		|| ((playerSprite.getGlobalBounds().top >= enemy2Sprite.getGlobalBounds().top) && (playerPosY <= enemy2PosY - 2))) {
		enemy2Sprite.setPosition(randomX, randomY);

		// Счётчик жизни
		lifes--;
	}

	// Выход за границы игровой области
	if (enemy2PosX < -400) {
		enemy2Sprite.setPosition(randomX, randomY);
	}
}

// Движение метеорита
void meteorMove(Sprite& meteorSprite, Vector2f& moveMeteor, Text& meteorText) {
	float meteorPosY = meteorSprite.getPosition().y;
	float meteorPosX = meteorSprite.getPosition().x;

	meteorText.setString(std::to_string(meteorPosX) + "\n" + std::to_string(meteorPosY));
	meteorText.setPosition(meteorPosX, meteorPosY + 80);

	moveMeteor.y = 0.5;
	moveMeteor.x = -1.5;

	meteorSprite.move(moveMeteor);

	// Выход за границы игровой области
	if (meteorPosX < -80) {
		meteorSprite.setPosition(900, 80);
	}
}
