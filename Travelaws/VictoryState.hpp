#pragma once
#include "GameData.h"
#include "State.hpp"
#include "DEFINITIONS.h"

class VictoryState : public State {
public:
  VictoryState(GameData& gameData, StateMachine& stateMachine);
  void processEvent(sf::Event& event) override;
  void update(sf::Time dt) override;
	void onEnter() override;
private:
	sf::Sprite _victorySprite;
	sf::Text _ggText;
	sf::Text _scoreText;
};