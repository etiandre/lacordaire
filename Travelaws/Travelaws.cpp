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
#include "InputManager.hpp"
#include "CollisionRule.h"
#include "WindRule.hpp"
#pragma endregion includes

Game::Game(int width, int height, std::string title) {
	gameData.player = Player();
	gameData.map = tmx::Map();
	window.create(sf::VideoMode(width, height),
		"Travelaws 0.0.0.0.1 alpha dx+ TEST RELEASE");
	window.setFramerateLimit(60);
	loadLevel(1);
	mainLoop();
}

void Game::loadLevel(int levelID) {
	if (!gameData.map.load("assets/levels/level" + std::to_string(levelID) + ".tmx")) {
		std::cout << "cannot load level !" << std::endl;
		exit(1);
	}
}

void Game::mainLoop() {
	int windowHeight = 1080;
	int windowWidth = 1920;

	sf::Event event;
	InputManager inputManager;
	GravityRule gravity;
	WindRule wind;

	MapLayer backgroundLayer(gameData.map, 0);
	MapLayer platformsLayer(gameData.map, 2);

	rules.push_back(std::make_unique<CollisionRule>(platformsLayer));
	rules.push_back(std::make_unique <GravityRule>(gravity));
	rules.push_back(std::make_unique<WindRule>(wind));

	float fpsCount = 0, switchFPS = 100, fpsSpeed = 500;

	sf::Clock time;
	float newTime, frameTime;
	float currentTime = time.getElapsedTime().asSeconds();
	float accumulator = 0.0f;


	//gameData.player.playerSprite.setTexture(gameData.player.playerTexture);

	while (window.isOpen()) {

		float newTime, frameTime;
		float currentTime = time.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (accumulator >= 1 / 60) // 60 fps
		{
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::EventType::Closed) window.close();
			}

			newTime = time.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			//Envisager cas limite des frames trop longues ?
			currentTime = newTime;
			accumulator += frameTime;





			inputManager.manageInputs(gameData.player);
			gravity.update(gameData);
			wind.update(gameData);


			gameData.player.updatePosition();
			gameData.player.updateAnimation();




			// Partie graph

			for (auto& rule : rules) {
				rule.get()->update(gameData);
			}

			// Création et gestion de la vue:
			view.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
			sf::Vector2f position(windowWidth / 2, windowHeight / 2);
			position.x =
				gameData.player.getPosition().x + BLOCK_SIZE / 2 - windowWidth / 2;
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
		accumulator -= 1 / 60;
	}
}

int main(int argc, char** argv) {
	Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Game alpha");
	return EXIT_SUCCESS;
}