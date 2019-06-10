#include "Game.h"
#include "CollisionRule.h"
#include "DEBUG.h"
#include "GameOverState.hpp"
#include "GameState.h"
#include "GravityRule.hpp"
#include "PreGameState.h"
#include "SFML/Audio.hpp"
#include "SplashscreenState.hpp"
#include "VictoryState.hpp"
#include "VisionRule.hpp"
#include "WindRule.hpp"

Game::Game(int width, int height) : _stateMachine(_gameData) {
  _gameData.window.create(sf::VideoMode(width, height),
                          "L.A.W.S. 0.9 alpha dx+ TEST RELEASE");
  _gameData.window.setFramerateLimit(60);
  _gameData.window.setView(_view);
  _gameData.window.setKeyRepeatEnabled(false);
#ifdef DEBUG
  ImGui::SFML::Init(_gameData.window);
#endif
  // initialize gameData
  _gameData.player = Player();
  _gameData.world = World();

  // add rules
  //!\\ Collision has to be last !
  _gameData.rules.push_back(std::make_unique<GravityRule>());
  _gameData.rules.push_back(std::make_unique<WindRule>());
  _gameData.rules.push_back(std::make_unique<VisionRule>());
  _gameData.rules.push_back(std::make_unique<CollisionRule>());

  _gameData.currentLevel = 1;

  // initialize stateMachine
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
  if (!music.openFromFile("assets/sounds/music.ogg")) exit(-1);
  music.play();
  music.setLoop(true);

  // main window loop
  while (_gameData.window.isOpen()) {
    dt = clock.restart();

    // process events
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
    // update current state and draw screen
    _stateMachine.update(dt);

#ifdef DEBUG
    ImGui::SFML::Render(_gameData.window);
#endif
    // display screen
    _gameData.window.display();

    // switch state if it has been requested
    _stateMachine.processStateSwitch();
  }

#ifdef DEBUG
  ImGui::SFML::Shutdown();
#endif
}