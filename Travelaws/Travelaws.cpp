// Travelaws.cpp : Ce fichier contient la fonction 'main'
//

#pragma region includes
#include "imgui-SFML.h"
#include "imgui.h"
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
#include "WindRule.hpp"

#pragma endregion includes

Game::Game(int width, int height, std::string title) {
  gameData.player = Player();
  gameData.map = tmx::Map();
  window.create(sf::VideoMode(width, height),
                "Travelaws 0.0.0.0.1 alpha dx+ TEST RELEASE");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);
  loadLevel(1);
  mainLoop();
  ImGui::SFML::Shutdown();
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

  rules.push_back(std::make_unique<GravityRule>());
  rules.push_back(std::make_unique<WindRule>());
  rules.push_back(std::make_unique<CollisionRule>(
      platformsLayer));  //!\\ Collision has to be last !

  float fpsCount = 0, switchFPS = 100, fpsSpeed = 500;

  sf::Clock clock;

  while (window.isOpen()) {
      while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::EventType::Closed) window.close();
      }
      ImGui::SFML::Update(window, clock.restart());

      // GAME LOOP
      // INPUTS
      inputManager.manageInputs(gameData.player);

      // PHYSICS UPDATE
      for (auto& rule : rules) {
        if (rule.get()->active) rule.get()->physicsUpdate(gameData);
      }

      // POSITION UPDATE
      gameData.player.updatePosition();

      // RULES UPDATE
      for (auto& rule : rules) {
        if (rule.get()->active) rule.get()->update(gameData);
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
      ImGui::SFML::Render(window);
      window.display();
    }
}

int main(int argc, char** argv) {
  Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Game alpha");
  return EXIT_SUCCESS;
}