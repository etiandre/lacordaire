#pragma once
#include "Rule.h"
#include "SFMLOrthogonalLayer.hpp"

class CollisionRule : public Rule {
 public:
  CollisionRule(MapLayer& layer);
  void physicsUpdate(GameData& gameData) override;

 private:
  MapLayer& collisionLayer;
  bool collides(const sf::FloatRect& box, const tmx::Vector2u& tileSize,
                const tmx::Vector2u& tileCount);
  const tmx::Vector2u tileSize;
  const tmx::Vector2u tileCount;
};
