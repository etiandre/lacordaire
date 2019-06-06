#include "FontManager.hpp"

FontManager::FontManager() {}

map<string, sf::Font*> FontManager::fonts;
std::vector<string> FontManager::order;

// Get Length of Fonts Array
int FontManager::getLength() { return fonts.size(); }

// Get Font by Name
sf::Font* FontManager::getFont(string name) {
	// See if we have already loaded this Font
	if (fonts.find(name) != fonts.end()) {
		return fonts[name];
	}
	else {
		return NULL;
	}
}

// Get Font by Index
sf::Font* FontManager::getFont(int index) {
	// Stay DRY and reuse get by name, but get string name from vector with index
	return getFont(order.at(index));
}

// Assign a Font a Name (for accessing via get) and path (to load from)
sf::Font* FontManager::loadFont(string name, string path) {
	// Haven't loaded it yet, time to create it
	sf::Font* Font = new sf::Font();

	if (Font->loadFromFile(path)) {
		fonts[name] = Font;

		// Push to vector the order in which items were loaded into map, for
		// accessing via index.
		order.push_back(name);
		return fonts[name];
	}
	else {
		// Could not load the file
		delete Font;
		return NULL;
	}
}

FontManager::~FontManager() {
	// Delete all of the Fonts we used
	sf::Font* Font;
	map<string, sf::Font*>::iterator iter = fonts.begin();
	while (iter != fonts.end()) {
		Font = iter->second;
		delete Font;
		iter++;
	}
}
