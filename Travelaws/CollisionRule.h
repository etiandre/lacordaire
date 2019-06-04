#pragma once
#include "Rule.h"
#include "SFMLOrthogonalLayer.hpp"

class CollisionRule : public Rule {
 public:
  CollisionRule(MapLayer& layer);
  void physicsUpdate(GameData& gameData) override;

 private:
  MapLayer& collisionLayer;
};
