#include "Game.h"
#include "GameState.h"
#include "DEBUG.h"

Game::Game(int width, int height) : _stateMachine(_gameData) {
  _gameData.window.create(sf::VideoMode(width, height),
                          "Travelaws 0.0.0.0.1 alpha dx+ TEST RELEASE");
  _gameData.window.setFramerateLimit(60);
  _gameData.window.setView(_view);
#ifdef DEBUG
  ImGui::SFML::Init(_gameData.window);
#endif
  _stateMachine.addState(InGame, make_unique<GameState>(_gameData, _stateMachine));
}

void Game::run() {
  sf::Event event;
  sf::Clock clock;

  _stateMachine.requestState(InGame);
  _stateMachine.processStateSwitch();

  while (_gameData.window.isOpen()) {
    // EVENTS
    while (_gameData.window.pollEvent(event)) {
#ifdef DEBUG
      ImGui::SFML::ProcessEvent(event);
#endif
      _stateMachine.processEvent(event);
      if (event.type == sf::Event::EventType::Closed) _gameData.window.close();
    }
#ifdef DEBUG
    ImGui::SFML::Update(_gameData.window, clock.restart());
#endif
    _stateMachine.update();

#ifdef DEBUG
    ImGui::SFML::Render(_gameData.window);
#endif

    _gameData.window.display();
    _stateMachine.processStateSwitch();
  }

#ifdef DEBUG
  ImGui::SFML::Shutdown();
#endif
}