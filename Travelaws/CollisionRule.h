#pragma once
#include "Rule.h"
#include "SFMLOrthogonalLayer.hpp"

class CollisionRule : public Rule {
 public:
  CollisionRule();
  void update(GameData& gameData, sf::Time dt) override;
  const char* getName();
  int getScore() override;

 private:
  bool collides(const sf::FloatRect& box, const tmx::Vector2u& tileSize,
                const tmx::Vector2u& tileCount, std::unique_ptr<MapLayer>& collisionLayer);
  const tmx::Vector2u tileSize;
  const tmx::Vector2u tileCount;
  const float _epsilon = 0.01;
};
