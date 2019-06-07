#include "WindRule.hpp"

void WindRule::update(GameData& gameData) {
  gameData.player.velocity.x += _windForce;
}
const char* WindRule::getName() { return "Vent"; }

int WindRule::getScore() { return 80; }
