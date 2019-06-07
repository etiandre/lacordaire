#pragma once
#include "GameData.h"
#include "State.hpp"

enum StateName { None, Splash, InGame, GameOver, Victory };

class State;

class StateMachine {
 public:
  StateMachine(GameData& gameData);
  void addState(StateName stateName, std::unique_ptr<State> state);
  void requestState(StateName stateName);

  void update(sf::Time dt);
  void processEvent(sf::Event& event);

  void processStateSwitch();

 private:
  GameData& _gameData;
  std::map<StateName, std::unique_ptr<State>> _states;
  void _switchState(StateName stateName);
  StateName _currentState;
  StateName _nextState;
};