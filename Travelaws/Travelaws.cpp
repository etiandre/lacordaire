// Travelaws.cpp : Ce fichier contient la fonction 'main'
//

#pragma region includes
#include "Travelaws.h"
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
#include "VisionRule.hpp"
#include "WindRule.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#pragma endregion includes

Game::Game(int width, int height, std::string title) {
  gameData.player = Player();
  gameData.map = tmx::Map();
  view = sf::View(sf::FloatRect(0, 0, width/4, height/4));
  window.create(sf::VideoMode(width, height),
                "Travelaws 0.0.0.0.1 alpha dx+ TEST RELEASE");
  window.setFramerateLimit(60);
  window.setView(view);
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
  MapLayer platformsLayer(gameData.map, 1);

  rules.push_back(std::make_unique<GravityRule>());
  //rules.push_back(std::make_unique<WindRule>());
  //rules.push_back(std::make_unique<VisionRule>());
  rules.push_back(std::make_unique<CollisionRule>(
      platformsLayer));  //!\\ Collision has to be last !

  sf::Clock clock;

  while (window.isOpen()) {
    // EVENTS
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
      if (rule.get()->active) rule.get()->update(gameData);
    }

    // POSITION UPDATE
    gameData.player.update();

    // RULES UPDATE
    for (auto& rule : rules) {
      if (rule.get()->active) rule.get()->update(gameData);
    }

    // VIEW
    // view.setCenter(sf::Vector2f(gameData.player.getPosition().x + 16,
    // gameData.player.getPosition().y + 16)); window.setView(view);

    // GUI
    ImGui::Begin("Rules");
    for (auto& rule : rules) {
      ImGui::Checkbox(rule.get()->getName(), &rule.get()->active);
    }
    ImGui::End();  // Rules

    ImGui::Begin("Debug");
    ImGui::Text("position : x=%d y=%d", gameData.player.getPosition().x,
                gameData.player.getPosition().y);
    ImGui::Text("vitesse : x=%0.3f y=%0.3f", gameData.player.velocity.x,
                gameData.player.velocity.y);
    ImGui::End();  // Debug

    // DRAW
    gameData.player.updateAnimation();
    window.clear();
    window.draw(backgroundLayer);
    window.draw(platformsLayer);
    gameData.player.draw(window);
    // RULES DRAW
    for (auto& rule : rules) {
      if (rule.get()->active) rule.get()->draw(window);
    }
    ImGui::SFML::Render(window);
    window.display();
  }
}

int main(int argc, char** argv) {
  Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Game alpha");
  return EXIT_SUCCESS;
}