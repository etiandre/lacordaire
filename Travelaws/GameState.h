#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <tmxlite/Map.hpp>
#include "GameData.h"
#include "InputManager.hpp"
#include "Player.h"
#include "Rule.h"
#include "TextureManager.h"

class GameState {
 public:
  GameState(GameData& gameData);
  void update();

 private:
  std::vector<std::unique_ptr<Rule>> rules;
  sf::View _view;
  GameData& _gameData;
  InputManager _inputManager;
};