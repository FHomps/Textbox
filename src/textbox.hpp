#pragma once
#include <unordered_map>

class TextboxGenerator {
public:
	bool loadFromFile(std::string const& filename, uint middlesize = 1); //Assumes the template image is symmetrical
	bool loadFromFile(std::string const& filename, uint leftwidth, uint rightwidth, uint topheight, uint bottomheight);

	sf::Texture const& getTexture(uint width, uint height);
	bool clearTexture(uint width, uint height);
	void clearAll();

private:
	sf::Image base;
	uint blw; uint bmw; uint brw; uint bth; uint bmh; uint bbh; //Base Left Width, Base Middle Width, etc.

	std::map<std::pair<uint,uint>, sf::Texture> textures;

};