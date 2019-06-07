#include "GravityRule.hpp"

GravityRule::GravityRule() : gSquared(900) {}

void GravityRule::update (GameData& gameData, sf::Time dt) {
  gameData.player.velocity.y += gSquared * dt.asSeconds();
}

const char* GravityRule::getName() { return "Gravite"; }

int GravityRule::getScore() { return 50; }
