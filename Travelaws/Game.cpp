#include "Game.h"
#include "CollisionRule.h"
#include "DEBUG.h"
#include "GameOverState.hpp"
#include "GameState.h"
#include "GravityRule.hpp"
#include "SFML/Audio.hpp"
#include "SplashscreenState.hpp"
#include "VictoryState.hpp"
#include "PreGameState.h"

Game::Game(int width, int height) : _stateMachine(_gameData) {
  _gameData.window.create(sf::VideoMode(width, height),
                          "L.A.W.S. 0.9 alpha dx+ TEST RELEASE");
  _gameData.window.setFramerateLimit(60);
  _gameData.window.setView(_view);
  _gameData.window.setKeyRepeatEnabled(false);
#ifdef DEBUG
  ImGui::SFML::Init(_gameData.window);
#endif

  _gameData.player = Player();
  _gameData.world = World();

  //!\\ Collision has to be last !
  _gameData.rules.push_back(std::make_unique<GravityRule>());
  // rules.push_back(std::make_unique<WindRule>());
  // rules.push_back(std::make_unique<VisionRule>());
  _gameData.rules.push_back(std::make_unique<CollisionRule>());

  _gameData.currentLevel = 1;

  _stateMachine.addState(
      Splash, make_unique<SplashscreenState>(_gameData, _stateMachine));
  _stateMachine.addState(PreGame,
                         make_unique<PreGameState>(_gameData, _stateMachine));
  _stateMachine.addState(InGame,
                         make_unique<GameState>(_gameData, _stateMachine));
  _stateMachine.addState(Victory,
                         make_unique<VictoryState>(_gameData, _stateMachine));
  _stateMachine.addState(GameOver,
                         make_unique<GameOverState>(_gameData, _stateMachine));
}

void Game::run() {
  sf::Event event;
  sf::Clock clock;
  sf::Time dt;

  _stateMachine.requestState(Splash);
  _stateMachine.processStateSwitch();

  ////////////////////// AUDIO ///////////////////
  sf::Music music;
  if (!music.openFromFile("assets/music.ogg")) exit(-1);
  music.play();

  while (_gameData.window.isOpen()) {
    dt = clock.restart();

    while (_gameData.window.pollEvent(event)) {
#ifdef DEBUG
      ImGui::SFML::ProcessEvent(event);
#endif
      _stateMachine.processEvent(event);
      if (event.type == sf::Event::EventType::Closed) _gameData.window.close();
    }
#ifdef DEBUG
    ImGui::SFML::Update(_gameData.window, dt);
#endif
    _stateMachine.update(dt);

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