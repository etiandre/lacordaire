//from https://github.com/netpoetica/sfml-texture-manager
//The MIT License(MIT) Copyright(c) 2013 Dylan Jones
//
//    Permission is hereby granted,
//    free of charge,
//    to any person obtaining a copy of this software and associated documentation
//    files(the "Software"),
//    to deal in the Software without restriction,
//    including without limitation the rights to use, copy, modify, merge, publish
//    ,
//    distribute, sublicense, and / or sell copies of the Software,
//    and to permit persons to whom the Software is furnished to do so,
//    subject to the following conditions :
//
//    The above copyright notice and this permission notice shall be included in
//    all copies
//    or
//    substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS",
//    WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//    TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN
//    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#include "TextureManager.h"

TextureManager::TextureManager() {}

map<string, sf::Texture *> TextureManager::textures;
std::vector<string> TextureManager::order;

// Get Length of Textures Array
int TextureManager::getLength() { return textures.size(); }

// Get Texture by Name
sf::Texture *TextureManager::getTexture(string name) {
  // See if we have already loaded this texture
  if (textures.find(name) != textures.end()) {
    return textures[name];
  } else {
    return NULL;
  }
}

// Get Texture by Index
sf::Texture *TextureManager::getTexture(int index) {
  // Stay DRY and reuse get by name, but get string name from vector with index
  return getTexture(order.at(index));
}

// Assign a Texture a Name (for accessing via get) and path (to load from)
sf::Texture *TextureManager::loadTexture(string name, string path) {
  // Haven't loaded it yet, time to create it
  sf::Texture *texture = new sf::Texture();

  if (texture->loadFromFile(path)) {
    textures[name] = texture;

    // Push to vector the order in which items were loaded into map, for
    // accessing via index.
    order.push_back(name);
    return textures[name];
  } else {
    // Could not load the file
    delete texture;
    return NULL;
  }
}

TextureManager::~TextureManager() {
  // Delete all of the textures we used
  sf::Texture *texture;
  map<string, sf::Texture *>::iterator iter = textures.begin();
  while (iter != textures.end()) {
    texture = iter->second;
    delete texture;
    iter++;
  }
}
