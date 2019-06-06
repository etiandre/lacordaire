#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <tmxlite/Map.hpp>
#include "GameData.h"
#include "InputManager.hpp"
#include "Player.h"
#include "Rule.h"
#include "State.hpp"
#include "TextureManager.h"


class GameState : public State {
 public:
  GameState(GameData& gameData, StateMachine& stateMachine);
  void update() override;

 private:
  std::vector<std::unique_ptr<Rule>> rules;
  sf::View _view;
  InputManager _inputManager;
};