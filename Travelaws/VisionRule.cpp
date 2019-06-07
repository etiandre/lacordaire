#include "VisionRule.hpp"
#include "DEFINITIONS.h"
#include "TextureManager.h"
const char* VisionRule::getName() { return "Vision"; }

int VisionRule::getScore() { return 150; }

void VisionRule::draw(sf::RenderWindow& window) {
	// draw mask
	window.draw(filter);
	window.draw(_rect1);
	window.draw(_rect2);
}

// Synchronize mask's position with the player's
void VisionRule::update(GameData& gameData, sf::Time dt) {
	auto X = gameData.player.getPosition().x + BLOCK_SIZE / 2;
	auto xWidth = filter.getTexture()->getSize().x;
	filter.setPosition(X - xWidth / 2,
		gameData.player.getPosition().y - filter.getTexture()->getSize().y / 2 + BLOCK_SIZE / 2);
	_rect1.setPosition(X - xWidth / 2 - _rect1.getSize().x, 0);
	_rect2.setPosition(X + xWidth / 2 , 0);
}

VisionRule::VisionRule() {
	sf::Texture* texturePointer =
		TextureManager::loadTexture("filtre", "assets/textures/filtrecamera.png");
	if (texturePointer == NULL) {
		exit(1);
	}
	filter.setTexture(*texturePointer);

	// Generate the 2 rectangle completing the mask
	_rect1.setSize(sf::Vector2f((float)(VIEW_WIDTH - filter.getTexture()->getSize().x) / 2.0f, 2*(float)VIEW_HEIGHT));
	_rect1.setFillColor(sf::Color());
	_rect2.setSize(sf::Vector2f((float)(VIEW_WIDTH - filter.getTexture()->getSize().x)*4 / 2.0f, 2*(float)VIEW_HEIGHT));
	_rect2.setFillColor(sf::Color());

}
