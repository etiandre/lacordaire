#include "GravityRule.hpp"

void GravityRule::physicsUpdate(GameData& gameData) {
  gameData.player.velocity.y += gravity;
}