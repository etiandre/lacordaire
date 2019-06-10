#ifndef FontManager_H
#define FontManager_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

using namespace std;

class FontManager {
	// The Fonts to load
	static map<string, sf::Font*> fonts;
	// Manually keep track of the order in which Font were loaded
	static std::vector<string> order;
	FontManager();

public:
	// Destructor which deletes the Fonts previously loaded
	~FontManager();

	static int getLength();
	// Get texutre by name specified in loadFont, or return null
	static sf::Font* getFont(string name);

	// Get texutre by index in map, or return null
	static sf::Font* getFont(int index);

	// Loads the Font and returns a pointer to it
	// If it is already loaded, this function just returns it
	// If it cannot find the file, returns NULL
	static sf::Font* loadFont(string name, string path);
};

#endif