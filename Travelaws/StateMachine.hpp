#pragma once
#include "GameData.h"
#include "State.hpp"

enum StateName {
  None,
  InGame,
  GameOver,
  Victory
};  // add Splashscreen and MainMenu later on

class StateMachine {
 public:
  StateMachine(GameData& gameData);
  void addState(StateName stateName, std::unique_ptr<State> state);
  void switchState(StateName stateName);
  void update();

 private:
  GameData& _gameData;
  std::map<StateName, std::unique_ptr<State>> _states;
  StateName _currentState;
};