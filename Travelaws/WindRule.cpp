#include "WindRule.hpp"

void WindRule::update(GameData& gameData, sf::Time dt) {
	gameData.player.velocity.x += _windForce * dt.asSeconds();
	
}
const char* WindRule::getName() { return "Vent"; }

int WindRule::getScore() { return 80; }
