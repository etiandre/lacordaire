#include "pch.h"
// Travelaws.cpp : Ce fichier contient la fonction 'main'
//

#pragma region includes
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <tmxlite/Map.hpp>
#include "CollisionRule.h"
#include "DEFINITIONS.h"
#include "GravityRule.hpp"
#include "InputManager.hpp"
#include "Player.h"
#include "SFMLOrthogonalLayer.hpp"
#include "Travelaws.h"
#include "GravityRule.hpp"
#include "InputManager.hpp"
#include "CollisionRule.h"
#include "WindRule.hpp"
#include "VisionRule.hpp"
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
  if (!gameData.map.load("assets/levels/level" + std::to_string(levelID) +
                         ".tmx")) {
    std::cout << "cannot load level !" << std::endl;
    exit(1);
  }
}

void Game::mainLoop() {
	sf::Event event;
	InputManager inputManager;

	MapLayer backgroundLayer(gameData.map, 0);
	MapLayer platformsLayer(gameData.map, 2);

	rules.push_back(std::make_unique<CollisionRule>(platformsLayer));
	rules.push_back(std::make_unique<GravityRule>());
	rules.push_back(std::make_unique<WindRule>());
	rules.push_back(std::make_unique<VisionRule>());

  float fpsCount = 0, switchFPS = 100, fpsSpeed = 500;

	sf::Clock time;
	float newTime, frameTime;
	float currentTime = time.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

  while (window.isOpen()) {
    float currentTime = time.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (accumulator >= 1 / 60)  // 60 fps
    {
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::EventType::Closed) window.close();
      }

      newTime = time.getElapsedTime().asSeconds();
      frameTime = newTime - currentTime;

      // Envisager cas limite des frames trop longues ?
      currentTime = newTime;
      accumulator += frameTime;

			// GAME LOOP
			// INPUTS
      inputManager.manageInputs(gameData.player);

			// PHYSICS UPDATE
      for (auto& rule : rules) {
        if (rule.get()->active)
					rule.get()->physicsUpdate(gameData);
			}

			// POSITION UPDATE
      gameData.player.updatePosition();

      // RULES UPDATE
      for (auto& rule : rules) {
        if (rule.get()->active)
					rule.get()->update(gameData);
      }

      // VIEW
      view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
      sf::Vector2f position(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
      position.x =
          gameData.player.getPosition().x + BLOCK_SIZE / 2 - SCREEN_WIDTH / 2;
      if (position.x < 0) position.x = 0;
      if (position.y < 0) position.y = 0;

      view.reset(sf::FloatRect(position.x, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
      window.setView(view);
			

		// DRAW
      gameData.player.updateAnimation();
      window.clear();
      window.draw(backgroundLayer);
      window.draw(platformsLayer);
      window.draw(gameData.player.playerSprite);

	  // RULES DRAW
	  for (auto& rule : rules) {
		  if (rule.get()->active)
			  rule.get()->draw(window);
	  }
      window.display();
    }
    accumulator -= 1 / 60;
  }
}

int main(int argc, char** argv) {
  Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Game alpha");
  return EXIT_SUCCESS;
}