#include "CollisionRule.h"
#include <cmath>

// merci https://jonathanwhiting.com/tutorial/collision/

CollisionRule::CollisionRule(MapLayer& layer) : collisionLayer(layer){};

void CollisionRule::update(GameData& gameData) {
  sf::FloatRect box;
  // axe x (horizontal)
	
  box = gameData.player.box;
  box.top += gameData.player.getPosition().y;
  box.left += gameData.player.getPosition().x + gameData.player.velocity.x;
  if (collides(box, gameData.map.getTileSize(), gameData.map.getTileCount())) {
    gameData.player.velocity.x = 0;
  }

  // axe y (vertical)
  box = gameData.player.box;
  box.top += gameData.player.getPosition().y + gameData.player.velocity.y;
  box.left += gameData.player.getPosition().x;
  if (collides(box, gameData.map.getTileSize(), gameData.map.getTileCount())) {
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
