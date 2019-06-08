#pragma once
#include "GameData.h"
#include "StateMachine.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>

class PreGameState : public State {
 public:
  PreGameState(GameData& gameData, StateMachine& stateMachine);
  void processEvent(sf::Event& event) override;
  void update(sf::Time dt) override;
  void onEnter() override;

 private:
  sf::Text _titleText;
  sf::Text _rule1;
  sf::Text _rule2;
  sf::Text _rule3;
  sf::Text _rule4;
  sf::Sprite _rule1ButtonImage;
  sf::Sprite _rule2ButtonImage;
  sf::Sprite _rule3ButtonImage;
  sf::Sprite _rule4ButtonImage;
  float _buttonWidth;
  float _buttonHeight;
};