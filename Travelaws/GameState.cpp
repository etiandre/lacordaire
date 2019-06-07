// Travelaws.cpp : Ce fichier contient la fonction 'main'
//

#pragma region includes
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <tmxlite/Map.hpp>
#include "CollisionRule.h"
#include "DEBUG.h"
#include "DEFINITIONS.h"
#include "GameOverState.hpp"
#include "GravityRule.hpp"
#include "InputManager.hpp"
#include "Player.h"
#include "SFMLOrthogonalLayer.hpp"
#include "StateMachine.hpp"
#include "VictoryState.hpp"
#include "VisionRule.hpp"
#include "WindRule.hpp"
#include "World.h"
#include "imgui-SFML.h"
#include "imgui.h"
#pragma endregion includes

GameState::GameState(GameData& gameData, StateMachine& stateMachine)
    : State(gameData, stateMachine),
      _inputManager(),
      _view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH / SCALE_FACTOR,
                                   SCREEN_HEIGHT / SCALE_FACTOR))),
      _clock() {}

void GameState::onEnter() {
  _gameData.world.loadLevel(_gameData.currentLevel);
  _gameData.player.teleportTo(_gameData.world.playerSpawn.left,
                              _gameData.world.playerSpawn.top);
  _clock.restart();
}

void GameState::update(sf::Time dt) {
  // MOVEMENT
  _gameData.player.manageInputs(dt);

  // PHYSICS UPDATE
  for (auto& rule : _gameData.rules) {
    if (rule.get()->active) rule.get()->update(_gameData, dt);
  }

  // POSITION UPDATE
  _gameData.player.update(dt);

  // CHECK STATE
  if (_gameData.player.getPosition().y >= SCREEN_HEIGHT / SCALE_FACTOR) {
    _stateMachine.requestState(GameOver);
  } else if (_gameData.player.collidesWith(_gameData.world.goal)) {
    _gameData.currentLevel++;
    if (_gameData.currentLevel > NUM_LEVELS) _gameData.currentLevel = 1;
    _stateMachine.requestState(Victory);
    _gameData.time = _clock.getElapsedTime();
  }

  // VIEW
  auto cameraPos = sf::Vector2f(_gameData.player.getPosition().x + 16,
                                _gameData.player.getPosition().y);
  //     SCREEN_HEIGHT / SCALE_FACTOR / 2);
  if (cameraPos.x < SCREEN_WIDTH / SCALE_FACTOR / 2)
    cameraPos.x = SCREEN_WIDTH / SCALE_FACTOR / 2;
  else if (cameraPos.x >
           _gameData.world.getSize().x - SCREEN_WIDTH / SCALE_FACTOR / 2)
    cameraPos.x = _gameData.world.getSize().x - SCREEN_WIDTH / SCALE_FACTOR / 2;
  if (cameraPos.y < SCREEN_HEIGHT / SCALE_FACTOR / 2)
    cameraPos.y = SCREEN_HEIGHT / SCALE_FACTOR / 2;
  else if (cameraPos.y >
           _gameData.world.getSize().y - SCREEN_HEIGHT / SCALE_FACTOR / 2)
    cameraPos.y =
        _gameData.world.getSize().y - SCREEN_HEIGHT / SCALE_FACTOR / 2;

  _view.setCenter(cameraPos);
  _gameData.window.setView(_view);

#ifdef DEBUG
  // GUI
  ImGui::Begin("Rules");
  for (auto& rule : _gameData.rules) {
    ImGui::Checkbox(rule.get()->getName(), &rule.get()->active);
  }
  ImGui::End();  // Rules

  ImGui::Begin("Debug");
  ImGui::Text("Current level=%d", _gameData.currentLevel);
  ImGui::Text("position : x=%f y=%f", _gameData.player.getPosition().x,
              _gameData.player.getPosition().y);
  ImGui::Text("vitesse : x=%0.3f y=%0.3f", _gameData.player.velocity.x,
              _gameData.player.velocity.y);
  ImGui::Text("onGround : %d", _gameData.player.onGround);
  ImGui::End();  // Debug
#endif           // DEBUG

  // DRAW
  _gameData.player.updateAnimation();
  _gameData.window.clear();
  _gameData.world.draw(_gameData.window);
  _gameData.player.draw(_gameData.window);
  // RULES DRAW
  for (auto& rule : _gameData.rules) {
    if (rule.get()->active) rule.get()->draw(_gameData.window);
  }
}
