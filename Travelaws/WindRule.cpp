#include "WindRule.hpp"

void WindRule::physicsUpdate(GameData& gameData) {
  gameData.player.velocity.x += _windForce;
}
const char* WindRule::getName() { return "Vent"; }
