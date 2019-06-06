#include "StateMachine.hpp"


StateMachine::StateMachine(GameData& gameData) : _gameData(gameData), _states(), _currentState(None) {
}

void StateMachine::addState(std::unique_ptr<State> state, StateName stateName) {
	_states.insert(std::pair<StateName, std::unique_ptr<State> >(stateName, state));
}

void StateMachine::switchState(StateName stateName) {
	_states[_currentState]->onExit();
	_currentState = stateName;
	_states[_currentState]->onEnter();
}

void StateMachine::update() {
	_states[_currentState]->update();
}
