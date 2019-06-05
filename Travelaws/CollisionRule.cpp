#include "CollisionRule.h"
#include <cmath>
#include "SFMLOrthogonalLayer.hpp"
#include "tmxlite/Map.hpp"

// merci https://jonathanwhiting.com/tutorial/collision/

CollisionRule::CollisionRule(){};

void CollisionRule::update(GameData& gameData) {
  sf::FloatRect box;
  auto& map = gameData.world.getMap();
  auto& collisionLayer = gameData.world.getCollisionLayer();
  // axe x (horizontal)
  gameData.player.onGround = false;
  box = gameData.player.box;
  box.top += gameData.player.getPosition().y;
  box.left += gameData.player.getPosition().x + gameData.player.velocity.x;
  if (collides(box, map.getTileSize(), map.getTileCount(), collisionLayer)) {
    gameData.player.velocity.x = 0;
  }

  // axe y (vertical)
  box = gameData.player.box;
  box.top += gameData.player.getPosition().y + gameData.player.velocity.y;
  box.left += gameData.player.getPosition().x;
  if (collides(box, map.getTileSize(), map.getTileCount(), collisionLayer)) {
    if (gameData.player.velocity.y > 0) {
      gameData.player.onGround = true;
    }
    gameData.player.velocity.y = 0;
  }
}

bool CollisionRule::collides(const sf::FloatRect& box,
                             const tmx::Vector2u& tileSize,
                             const tmx::Vector2u& tileCount,
                             std::unique_ptr<MapLayer>& collisionLayer) {

	if (box.left <= 0) return true;
  int topTile = box.top / tileSize.y;
  int leftTile = box.left / tileSize.x;
  int bottomTile = (box.top + box.height) / tileSize.y;
  int rightTile = (box.left + box.width) / tileSize.x;
	
	if (leftTile > tileCount.x) return false;
  if (topTile > tileCount.y) return false;

  if (leftTile < 0) leftTile = 0;
  if (topTile < 0) topTile = 0;
  if (rightTile > tileCount.x - 1) rightTile = tileCount.x - 1;
  if (bottomTile > tileCount.y - 1) rightTile = tileCount.y - 1;

  for (int i = leftTile; i <= rightTile; i++) {
    for (int j = topTile; j <= bottomTile; j++) {
      if (collisionLayer->getTile(i, j).ID != 0) {
        return true;
      }
    }
  }
  return false;
}

const char* CollisionRule::getName() { return "Collisions"; }
