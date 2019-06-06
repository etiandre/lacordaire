#pragma once
#include "GameData.h"
#include "InputManager.hpp"
#include "State.hpp"
#include "DEFINITIONS.h"

class VictoryState : public State {
public:
  VictoryState(GameData& gameData, StateMachine& stateMachine);
  void processEvent(sf::Event& event) override;
	void update() override;
	void onEnter() override;
private:
	sf::Sprite _victorySprite;
	InputManager _inputManager;
};