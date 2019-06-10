#include "StateMachine.hpp"
#include "DEBUG.h"

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

void StateMachine::update(sf::Time dt) {
  _states[_currentState].get()->update(dt);
#ifdef DEBUG
  ImGui::Begin("State");
  ImGui::Text("Current State : %d", _currentState);
  ImGui::Text("dt = %d ms", dt.asMilliseconds());
  for (int i = None + 1; i <= Victory; i++) {
    char buf[20];
    sprintf_s(buf, "change to state %d", i);
    if (ImGui::Button(buf)) {
      requestState(static_cast<StateName>(i));
    }
  }
  ImGui::End();  // State
#endif           // DEBUG
}

void StateMachine::processEvent(sf::Event& event) {
  _states[_currentState].get()->processEvent(event);
}

void StateMachine::processStateSwitch() {
  if (_nextState != _currentState) _switchState(_nextState);
}
