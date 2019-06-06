#pragma once
#include "GameData.h"
#include "StateMachine.hpp"

class StateMachine;

class State {
 public:
  State(GameData& gameData, StateMachine& stateMachine);
  virtual void processEvent(sf::Event& event);
  virtual void update() = 0;
  virtual void onEnter();
  virtual void onExit();

 protected:
  GameData& _gameData;
  StateMachine& _stateMachine;
};