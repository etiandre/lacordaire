#include "VisionRule.hpp"
#include "DEFINITIONS.h"
#include "TextureManager.h"
const char* VisionRule::getName() { return "Vision"; }

void VisionRule::draw(sf::RenderWindow& window) {
  // draw mask
  window.draw(filter);
  window.draw(_rect1);
  window.draw(_rect2);
}

// Synchronize mask's position with the player's
void VisionRule::update(GameData& gameData) {
  int X = gameData.player.getPosition().x;
  // Always tracks Y axis
  filter.setPosition(X + BLOCK_SIZE / 2 - 540,
                     gameData.player.getPosition().y + BLOCK_SIZE / 2 -
                         1080);  // texture is 1080x2160
  // Only tracks X axis between borders
  if (X >= 480) {
    filter.setPosition(X + BLOCK_SIZE / 2 - 540,
                       gameData.player.getPosition().y + BLOCK_SIZE / 2 -
                           1080);  // texture is 1080x2160
  }
  _rect1.setPosition(X + BLOCK_SIZE / 2 - 2040,
                     0);  // 540 pour la texture + 1500 pour le rectangle
  _rect2.setPosition(X + BLOCK_SIZE / 2 + 540, 0);
}

VisionRule::VisionRule() {
  sf::Texture* texturePointer =
      TextureManager::loadTexture("filtre", "assets/textures/filtrecamera.png");
  if (texturePointer == NULL) {
    // std::cout << "erreur chargement texture filtre !" << std::endl;
    exit(1);
  }
  filter.setTexture(*texturePointer);

  // Generate the 2 rectangle completing the mask
  _rect1.setSize(sf::Vector2f(1500, 1080));
  _rect1.setFillColor(sf::Color());
  _rect1.setPosition(-1080, 0);
  _rect2.setSize(sf::Vector2f(1500, 1080));
  _rect2.setFillColor(sf::Color());
  _rect2.setPosition(540, 0);
  filter.setPosition(BLOCK_SIZE / 2, BLOCK_SIZE / 2 - 1080);
}
