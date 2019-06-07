#pragma once
#include "GameData.h"
#include "InputManager.hpp"
#include "State.hpp"
#include "DEFINITIONS.h"

class GameOverState : public State {
public:
  GameOverState(GameData& gameData, StateMachine& stateMachine);
  void processEvent(sf::Event& event) override;
	void update(sf::Time dt) override;
	void onEnter() override;
private:
	sf::Sprite _gameOverSprite;
	InputManager _inputManager;
};