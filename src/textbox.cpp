#include "textbox.hpp"
#include <map>

bool TextboxGenerator::loadFromFile(std::string const& filename, uint msize) {
	bool loaded = base.loadFromFile(filename);
	if (!loaded)
		return false;
	blw = (base.getSize().x - msize) / 2;
	brw = blw;
	bmw = msize;
	bth = (base.getSize().y - msize) / 2;
	bbh = bth;
	bmh = msize;
	return true;
}

bool TextboxGenerator::loadFromFile(std::string const& filename, uint lwidth, uint rwidth, uint theight, uint bheight) {
	bool loaded = base.loadFromFile(filename);
	if (!loaded)
		return false;
	blw = lwidth;
	brw = rwidth;
	bmw = base.getSize().x - lwidth - rwidth;
	bth = theight;
	bbh = bheight;
	bmh = base.getSize().y - theight - bheight;
	return true;
}

sf::Texture const& TextboxGenerator::getTexture(uint width, uint height) {
	std::pair<uint,uint> size;
	size.first = width;
	size.second = height;
	auto it = textures.find(size);
	if (it == textures.end()) { //Generate a new texture of the right size
		std::cout << "beep" << std::endl;
		uint bw = base.getSize().x;
		uint bh = base.getSize().y;

		sf::Texture& tex = textures[size];
		tex.create(width, height);
		if (width < bw || height < bh) {
			return tex;	
		}
		sf::Uint8 const* src = base.getPixelsPtr();
		sf::Uint8* pixels = new sf::Uint8[4*width*height];

		auto copyPixel = [&pixels, &src](uint spix, uint dpix){
			for (int i = 0; i < 4; i++)
				pixels[4*dpix+i] = src[4*spix+i];
		};

		for (uint y = 0; y < bth; y++) {
			for (uint x = 0; x < blw; x++) //TL corner
				copyPixel(bw*y+x, width*y+x);
			for (uint x = blw; x < width-brw; x++) { //TM ribbon
				uint bx = blw + (x-blw)%bmw;
				copyPixel(bw*y+bx, width*y+x);
			}
			for (uint x = width-brw; x < width; x++) { //TR corner
				uint bx = blw + bmw + x - (width-brw);
				copyPixel(bw*y+bx, width*y+x);
			}
		}
		for (uint y = bth; y < height-bbh; y++) {
			uint by = bth + (y-bth)%bmh;
			for (uint x = 0; x < blw; x++) //ML ribbon
				copyPixel(bw*by+x, width*y+x);
			for (uint x = blw; x < width-brw; x++) { //Center part
				uint bx = blw + (x-blw)%bmw;
				copyPixel(bw*by+bx, width*y+x);
			}
			for (uint x = width-brw; x < width; x++) {//MR ribbon
				uint bx = blw + bmw + x - (width-brw);
				copyPixel(bw*by+bx, width*y+x);
			}
		}
		for (uint y = height-bbh; y < height; y++) {
			uint by = bth + bmh + y - (height-bbh);
			for (uint x = 0; x < blw; x++) //BL corner
				copyPixel(bw*by+x, width*y+x);
			for (uint x = blw; x < width-brw; x++) { //BM ribbon
				uint bx = blw + (x-blw)%bmw;
				copyPixel(bw*by+bx, width*y+x);
			}
			for (uint x = width-brw; x < width; x++) { //BR corner
				uint bx = blw + bmw + x - (width-brw);
				copyPixel(bw*by+bx, width*y+x);
			}
		}
		
		tex.update(pixels);
		delete[] pixels;

		return tex;
	}
	return it->second;
}

bool TextboxGenerator::clearTexture(uint width, uint height) {
	auto it = textures.find(std::pair<uint,uint>(width,height));
	if (it == textures.end())
		return false;
	textures.erase(it);
	return true;
}

void TextboxGenerator::clearAll() {
	textures.clear();
}