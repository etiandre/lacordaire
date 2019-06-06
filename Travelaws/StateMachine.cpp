#include "StateMachine.hpp"

StateMachine::StateMachine(GameData& gameData)
    : _gameData(gameData), _states(), _currentState(None), _nextState(None) {}

void StateMachine::addState(StateName stateName, std::unique_ptr<State> state) {
  _states[stateName] = std::move(state);
}

void StateMachine::requestState(StateName stateName) { _nextState = stateName; }

void StateMachine::_switchState(StateName stateName) {
  if (_currentState != None) {
    _states[_currentState].get()->onExit();
  }
  _currentState = stateName;
  _states[_currentState].get()->onEnter();
}

void StateMachine::update() { _states[_currentState].get()->update(); }

void StateMachine::processStateSwitch() {
  if (_nextState != _currentState) _switchState(_nextState);
}
