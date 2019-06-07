#include "CollisionRule.h"
#include <cmath>
#include "DEBUG.h"
#include "SFMLOrthogonalLayer.hpp"
#include "tmxlite/Map.hpp"

// merci https://jonathanwhiting.com/tutorial/collision/

CollisionRule::CollisionRule(){};

void CollisionRule::update(GameData& gameData, sf::Time dt) {
  sf::FloatRect box;
  auto& map = gameData.world.getMap();
  auto& collisionLayer = gameData.world.getCollisionLayer();

  gameData.player.onGround = false;

#ifdef DEBUG
  ImGui::Begin("CollisionRule");
#endif

  // axe x (horizontal)
  box = gameData.player.hitbox;
  box.top += gameData.player.getPosition().y;
  box.left += gameData.player.getPosition().x +
              gameData.player.velocity.x * dt.asSeconds();
  if (collides(box, map.getTileSize(), map.getTileCount(), collisionLayer)) {
#ifdef DEBUG
    ImGui::Text("Collision on axis X");
#endif
    if (gameData.player.velocity.x > 0) {  // on va vers la droite
      gameData.player.velocity.x -=
          fmod(box.left + box.width, map.getTileSize().x) / dt.asSeconds() +
          _epsilon;
    } else if (gameData.player.velocity.x < 0) {  // on va vers la gauche
      gameData.player.velocity.x +=
          (map.getTileSize().x - fmod(box.left, map.getTileSize().x)) /
              dt.asSeconds() +
          _epsilon;
    }
  }

  // axe y (vertical)
  box = gameData.player.hitbox;
  box.top += gameData.player.getPosition().y +
             gameData.player.velocity.y * dt.asSeconds();
  box.left += gameData.player.getPosition().x;
  if (collides(box, map.getTileSize(), map.getTileCount(), collisionLayer)) {
#ifdef DEBUG
    ImGui::Text("Collision on axis Y");
#endif
    if (gameData.player.velocity.y > 0) {  // on va vers le bas
      gameData.player.onGround = true;
      gameData.player.velocity.y -=
          (fmod(box.top + box.height, map.getTileSize().y)) / dt.asSeconds() +
          _epsilon;
    } else if (gameData.player.velocity.y < 0) {  // on va vers le haut
      gameData.player.velocity.y +=
          (map.getTileSize().y - fmod(box.top, map.getTileSize().y)) /
              dt.asSeconds() +
          _epsilon;
    }
  }

#ifdef DEBUG
  ImGui::End();
#endif  // DEBUG
}

bool CollisionRule::collides(const sf::FloatRect& box,
                             const tmx::Vector2u& tileSize,
                             const tmx::Vector2u& tileCount,
                             std::unique_ptr<MapLayer>& collisionLayer) {
  int topTile = box.top / tileSize.y;
  int leftTile = box.left / tileSize.x;
  int bottomTile = (box.top + box.height) / tileSize.y;
  int rightTile = (box.left + box.width) / tileSize.x;

  if (leftTile > tileCount.x) return false;
  if (topTile > tileCount.y) return false;

  if (leftTile < 0) leftTile = 0;
  if (topTile < 0) topTile = 0;
  if (rightTile > tileCount.x - 1) rightTile = tileCount.x - 1;
  if (bottomTile > tileCount.y - 1) bottomTile = tileCount.y - 1;

  for (int i = leftTile; i <= rightTile; i++) {
    for (int j = topTile; j <= bottomTile; j++) {
      if (collisionLayer->getTile(i, j).ID != 0) {
#ifdef DEBUG
        ImGui::Text("Collided with tile (%d,%d)", i, j);
#endif  // DEBUG

        return true;
      }
    }
  }
  return false;
}

const char* CollisionRule::getName() { return "Collisions"; }
