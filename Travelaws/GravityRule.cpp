#include "GravityRule.hpp"

void GravityRule::update(GameData& gameData) {
  gameData.player.velocity.y += gravity;
}

const char* GravityRule::getName() { return "Gravite"; }