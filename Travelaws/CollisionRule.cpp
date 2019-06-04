#include "CollisionRule.h"
#include <cmath>

// merci https://jonathanwhiting.com/tutorial/collision/

CollisionRule::CollisionRule(MapLayer& layer) : collisionLayer(layer){};

void CollisionRule::update(GameData& gameData) {
  sf::FloatRect box;
  // axe x
	
  box = sf::FloatRect(
      gameData.player.getPosition().x + gameData.player.velocity.x,
      gameData.player.getPosition().y, 64, 64);
  if (collides(box, gameData.map.getTileSize(), gameData.map.getTileCount())) {
    std::cout << "collision en x" << std::endl;
    gameData.player.velocity.x = 0;
  }

  // axe y
  box = sf::FloatRect(
      gameData.player.getPosition().x,
      gameData.player.getPosition().y + gameData.player.velocity.y, 64, 64);
  if (collides(box, gameData.map.getTileSize(), gameData.map.getTileCount())) {
    std::cout << "collision en y" << std::endl;
    gameData.player.velocity.y = 0;
  }
}

bool CollisionRule::collides(const sf::FloatRect& box,
                             const tmx::Vector2u& tileSize,
                             const tmx::Vector2u& tileCount) {
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
        return true;
      }
    }
  }
  return false;
}

const char* CollisionRule::getName() { return "Collisions"; }
