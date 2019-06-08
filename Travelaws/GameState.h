#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <tmxlite/Map.hpp>
#include "GameData.h"
#include "Player.h"
#include "Rule.h"
#include "State.hpp"
#include "TextureManager.h"

class GameState : public State {
 public:
  GameState(GameData& gameData, StateMachine& stateMachine);
  void onEnter() override;
  void update(sf::Time dt) override;

  void onExit() override;

 private:
  sf::View _view;
  sf::Clock _clock;
  sf::Text _topText;
};