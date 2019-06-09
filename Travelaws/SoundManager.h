#pragma once
#include "SFML/Audio.hpp"


class playSound {
public:
	void operator()(std::string PATH)
	{
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(PATH))
			exit(-1);
		sf::Sound sound;
		sound.setBuffer(buffer);
		sound.play();
		while (sound.getStatus() != sf::SoundSource::Status::Stopped) {	}
	}
};