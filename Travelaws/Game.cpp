#include "Game.h"
#include "DEFINITIONS.h"
#include "GameState.h"
#include "imgui-SFML.h"
#include "imgui.h"


Game::Game(int width, int height) {
  _gameData.window.create(sf::VideoMode(width, height),
                          "Travelaws 0.0.0.0.1 alpha dx+ TEST RELEASE");
  _gameData.window.setFramerateLimit(60);
  _gameData.window.setView(_view);
  ImGui::SFML::Init(_gameData.window);
}

void Game::run() {
  GameState state = GameState(_gameData);
  sf::Event event;
  sf::Clock clock;

  while (_gameData.window.isOpen()) {
    // EVENTS
    while (_gameData.window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);
      if (event.type == sf::Event::EventType::Closed) _gameData.window.close();
    }
    ImGui::SFML::Update(_gameData.window, clock.restart());

    state.update();

    ImGui::SFML::Render(_gameData.window);
    _gameData.window.display();
  }

  ImGui::SFML::Shutdown();
}