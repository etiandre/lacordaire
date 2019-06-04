#include "pch.h"
//
#include <cmath>
#include "CollisionRule.h"

// merci https://jonathanwhiting.com/tutorial/collision/

CollisionRule::CollisionRule(MapLayer& layer) : collisionLayer(layer) {};

void CollisionRule::physicsUpdate(GameData& gameData) {
  sf::FloatRect box = sf::FloatRect(gameData.player.getPosition().x,
                                    gameData.player.getPosition().y, 64, 64);
  collides(box, gameData.map.getTileSize(), gameData.map.getTileCount());
}

bool CollisionRule::collides(const sf::FloatRect& box, const tmx::Vector2u& tileSize, const tmx::Vector2u& tileCount) {
  int topTile = box.top / tileSize.y;
  int leftTile = box.left / tileSize.x;
  int bottomTile = (box.top + box.height) / tileSize.y;
  int rightTile = (box.left + box.width) / tileSize.x;

  if (leftTile < 0) leftTile = 0;
  if (topTile < 0) topTile = 0;
  if (rightTile > tileCount.x) rightTile = tileCount.x;
  if (bottomTile > tileCount.y) rightTile = tileCount.y;

  for (int i = leftTile; i <= rightTile; i++) {
    for (int j = topTile; j <= bottomTile; j++) {
      if (collisionLayer.getTile(i, j).ID != 0) {
        std::cout << "collision" << std::endl;
        return true;
      }
    }
  }
}
