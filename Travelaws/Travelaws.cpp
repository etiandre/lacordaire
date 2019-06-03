#include "pch.h"
// Travelaws.cpp : Ce fichier contient la fonction 'main'
//

#pragma region includes
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <tmxlite/Map.hpp>
#include "DEFINITIONS.h"
#include "Player.h"
#include "SFMLOrthogonalLayer.hpp"
#include "Travelaws.h"
#include "GravityRule.hpp"
#pragma endregion includes

Game::Game(int width, int height, std::string title) {
	window.create(sf::VideoMode(width, height),
		"Travelaws 0.0.0.0.1 alpha dx+ TEST RELEASE");
	window.setFramerateLimit(60);
	loadLevel(1);
	mainLoop();
}

void Game::loadLevel(int levelID) {
	if (!map.load("assets/levels/level" + std::to_string(levelID) + ".tmx")) {
		std::cout << "cannot load level !" << std::endl;
		exit(1);
	}
}

void Game::mainLoop() {
	int windowHeight = 1080;
	int windowWidth = 1920;

	int speed = 0.1;
	sf::Texture slimeTexture;
	sf::Sprite slimeSprite;
	int blockSize = 64;

	sf::Event event;

	MapLayer backgroundLayer(map, 0);
	MapLayer platformsLayer(map, 2);

	gameData = {};
	gameData.player = Player();

	float fpsCount = 0, switchFPS = 100, fpsSpeed = 500;

	sf::Clock time;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed) window.close();
		}
		// CLAVIER
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			gameData.player.move(-1, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			gameData.player.move(1, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			gameData.player.move(0, -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			gameData.player.move(0, 1);
		}

		GravityRule gravity;
		gravity.update(gameData);

		gameData.player.updatePosition();

		// Création et gestion de la vue:
		view.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
		sf::Vector2f position(windowWidth / 2, windowHeight / 2);
		position.x =
			gameData.player.getPosition().x + blockSize / 2 - windowWidth / 2;
		if (position.x < 0) position.x = 0;
		if (position.y < 0) position.y = 0;

		view.reset(sf::FloatRect(position.x, 0, windowWidth, windowHeight));
		window.setView(view);

		window.clear();
		window.draw(backgroundLayer);
		window.draw(platformsLayer);
		window.draw(gameData.player.playerSprite);
		window.display();
	}
}

int main(int argc, char** argv) {
	Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Travelaws alpha");
	return EXIT_SUCCESS;
}