#include "World.h"

World::World() {}

World::World(int levelID) : _map(), _layers() {
  if (!_map.load("assets/levels/level" + std::to_string(levelID) + ".tmx")) {
    std::cout << "cannot load level !" << std::endl;
    exit(1);
  }
  for (int i = 0; i < _map.getLayers().size(); i++) {
    _layers.push_back(std::make_unique<MapLayer>(_map, i));
    //_layers.emplace_back<MapLayer>({_map, (size_t)i});
  }
}

void World::draw(sf::RenderWindow& window) {
  for (auto& layer : _layers) {
    window.draw(*layer.get());
  }
}

tmx::Map& World::getMap() { return _map; }

sf::Vector2i World::getSize() {
  return sf::Vector2i(_map.getTileSize().x * _map.getTileCount().x,
                      _map.getTileSize().y * _map.getTileCount().y);
}

std::unique_ptr<MapLayer>& World::getCollisionLayer() { return _layers.back(); }
