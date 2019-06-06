#include "StateMachine.hpp"

StateMachine::StateMachine(GameData& gameData)
    : _gameData(gameData), _states(), _currentState(None) {}

void StateMachine::addState(StateName stateName, std::unique_ptr<State> state) {
  _states[stateName] = std::move(state);
}

void StateMachine::switchState(StateName stateName) {
  if (_currentState != None) {
    _states[_currentState].get()->onExit();
    _currentState = stateName;
    _states[_currentState].get()->onEnter();
	}
	else {
    _currentState = stateName;
	}
}

void StateMachine::update() { _states[_currentState].get()->update(); }
