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
      _view(sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT))),
      _clock() {}

void GameState::onEnter() {
  _gameData.world.loadLevel(_gameData.currentLevel);
  _gameData.player.teleportTo(_gameData.world.playerSpawn.left,
                              _gameData.world.playerSpawn.top);
  _gameData.player.velocity = sf::Vector2f();
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
  if (_gameData.player.getPosition().y >= VIEW_HEIGHT) {
    _stateMachine.requestState(GameOver);
  } else if (_gameData.player.collidesWith(_gameData.world.goal)) {
    _gameData.currentLevel++;
    if (_gameData.currentLevel > NUM_LEVELS) _gameData.currentLevel = 1;
    _stateMachine.requestState(Victory);
  }

  // VIEW
  auto cameraPos = sf::Vector2f(_gameData.player.getPosition().x + 16,
                                _gameData.player.getPosition().y);
  //     VIEW_HEIGHT / 2);
  if (cameraPos.x < VIEW_WIDTH / 2)
    cameraPos.x = VIEW_WIDTH / 2;
  else if (cameraPos.x > _gameData.world.getSize().x - VIEW_WIDTH / 2)
    cameraPos.x = _gameData.world.getSize().x - VIEW_WIDTH / 2;
  if (cameraPos.y < VIEW_HEIGHT / 2)
    cameraPos.y = VIEW_HEIGHT / 2;
  else if (cameraPos.y > _gameData.world.getSize().y - VIEW_HEIGHT / 2)
    cameraPos.y = _gameData.world.getSize().y - VIEW_HEIGHT / 2;

  _view.setCenter(cameraPos);
  _gameData.window.setView(_view);

#ifdef DEBUG
  // GUI
  ImGui::Begin("Rules");
  for (auto& rule : _gameData.rules) {
    ImGui::Checkbox(rule.get()->getName(), &rule.get()->active);
  }
  ImGui::End();  // Rules

  ImGui::Begin("GameState");
  ImGui::Text("position : x=%f y=%f", _gameData.player.getPosition().x,
              _gameData.player.getPosition().y);
  ImGui::Text("vitesse : x=%0.3f y=%0.3f", _gameData.player.velocity.x,
              _gameData.player.velocity.y);
  ImGui::Text("onGround : %d", _gameData.player.onGround);
  ImGui::Separator();
  if (ImGui::InputInt("Current level", &_gameData.currentLevel)) onEnter();
  ImGui::End();  // Debug
#endif           // DEBUG

  // DRAW
  _gameData.window.clear();
  _gameData.world.draw(_gameData.window);
  _gameData.player.draw(_gameData.window);
  // RULES DRAW
  for (auto& rule : _gameData.rules) {
    if (rule.get()->active) rule.get()->draw(_gameData.window);
  }
}

void GameState::onExit() { _gameData.time = _clock.getElapsedTime(); }