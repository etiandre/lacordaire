#pragma once
#include <tmxlite/Map.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLOrthogonalLayer.hpp"

class World {
 public:
  World();
  World(int levelID);
  void draw(sf::RenderWindow &window);

	tmx::Map& getMap();
  std::unique_ptr<MapLayer>& getCollisionLayer();

 private:
  tmx::Map _map;
  std::vector<std::unique_ptr<MapLayer>> _layers;
};