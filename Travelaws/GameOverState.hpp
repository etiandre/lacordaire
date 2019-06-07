#pragma once
#include "DEFINITIONS.h"
#include "GameData.h"
#include "InputManager.hpp"
#include "State.hpp"

class GameOverState : public State {
 public:
  GameOverState(GameData& gameData, StateMachine& stateMachine);
  void processEvent(sf::Event& event) override;
  void update(sf::Time dt) override;
  void onEnter() override;

 private:
  sf::Sprite _gameOverSprite;
  sf::Text _text;
  InputManager _inputManager;
  sf::Text _gitgudText;
};