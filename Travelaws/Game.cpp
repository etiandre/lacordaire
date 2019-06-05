// Travelaws.cpp : Ce fichier contient la fonction 'main'
//

#pragma region includes
#include "Game.h"
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
#include "World.h"
#pragma endregion includes

Game::Game(int width, int height) {
  gameData.player = Player();
  gameData.world = World(1);
  view = sf::View(
      sf::FloatRect(0, 0, width / SCALE_FACTOR, height / SCALE_FACTOR));
  gameData.window.create(sf::VideoMode(width, height),
                "Travelaws 0.0.0.0.1 alpha dx+ TEST RELEASE");
  gameData.window.setFramerateLimit(60);
  gameData.window.setView(view);
  ImGui::SFML::Init(gameData.window);

  mainLoop();
  ImGui::SFML::Shutdown();
}

void Game::mainLoop() {
  sf::Event event;
  InputManager inputManager;

  rules.push_back(std::make_unique<GravityRule>());
  // rules.push_back(std::make_unique<WindRule>());
  // rules.push_back(std::make_unique<VisionRule>());
  rules.push_back(std::make_unique<CollisionRule>());  //!\\ Collision has to be last !

  sf::Clock clock;

  while (gameData.window.isOpen()) {
    // EVENTS
    while (gameData.window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);
      if (event.type == sf::Event::EventType::Closed) gameData.window.close();
    }

    ImGui::SFML::Update(gameData.window, clock.restart());

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
        auto cameraPos = sf::Vector2f(gameData.player.getPosition().x + 16,
                                      SCREEN_HEIGHT / SCALE_FACTOR / 2);
        if (cameraPos.x < 0) cameraPos.x = 0;
        if (cameraPos.y < 0) cameraPos.y = 0;

        view.setCenter(cameraPos);
        gameData.window.setView(view);

        // GUI
        ImGui::Begin("Rules");
        for (auto& rule : rules) {
          ImGui::Checkbox(rule.get()->getName(), &rule.get()->active);
        }
        ImGui::End();  // Rules

        ImGui::Begin("Player Debug");
        ImGui::Text("position : x=%d y=%d", gameData.player.getPosition().x,
                    gameData.player.getPosition().y);
        ImGui::Text("vitesse : x=%0.3f y=%0.3f", gameData.player.velocity.x,
                    gameData.player.velocity.y);
        ImGui::Text("onGround : %d", gameData.player.onGround);
        ImGui::End();  // Debug

        // DRAW
        gameData.player.updateAnimation();
        gameData.window.clear();
        gameData.world.draw(gameData.window);
        gameData.player.draw(gameData.window);
        // RULES DRAW
        for (auto& rule : rules) {
          if (rule.get()->active) rule.get()->draw(gameData.window);
        }

    ImGui::SFML::Render(gameData.window);
    gameData.window.display();
  }
}
