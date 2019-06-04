#include "pch.h"
//
#include <cmath>
#include "CollisionRule.h"

CollisionRule::CollisionRule(MapLayer& layer) : collisionLayer(layer){};

void CollisionRule::physicsUpdate(GameData& gameData) {
  sf::FloatRect box = sf::FloatRect(gameData.player.getPosition().x,
                                    gameData.player.getPosition().y, 64, 64);
  int i = gameData.player.getPosition().x / gameData.map.getTileSize().x;
  int j = gameData.player.getPosition().y / gameData.map.getTileSize().y;
  if (collisionLayer.getTile(i, j).ID != 0) {
    std::cout << "collision" << std::endl;
    gameData.player.velocity.x = 0;
    gameData.player.velocity.y = 0;
  }
}
