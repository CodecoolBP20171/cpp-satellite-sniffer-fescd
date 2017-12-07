#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include <memory>

class Graphics {
public:
	Graphics();
	~Graphics();
	bool init();
	std::shared_ptr<Texture> loadTexture(const std::string& filename);
	SDL_Renderer* getRenderer() { return renderer; }
	void putSatToSky(unsigned int x, unsigned int y);
	void showAllSat();

private:
	SDL_Window * window;
	SDL_Renderer *renderer;
	std::shared_ptr<Texture> background;
	
	bool createWindow();
	bool createRenderer();
	bool initSDLImage();
};
