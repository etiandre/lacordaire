#include "State.hpp"

State::State(GameData& gameData, StateMachine& stateMachine)
    : _gameData(gameData), _stateMachine(stateMachine) {}

void State::onEnter() {}

void State::onExit() {}

void State::update(sf::Time dt) {}

void State::processEvent(sf::Event& event) {}