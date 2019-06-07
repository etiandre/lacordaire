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
};