#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include <memory>

class Graphics {
public:
	Graphics() : window(nullptr), renderer(nullptr) {}
	~Graphics();
	bool init();
	std::shared_ptr<Texture> loadTexture(const std::string& filename);
	SDL_Renderer* getRenderer() { return renderer; }

private:
	SDL_Window * window;
	SDL_Renderer *renderer;
	bool createWindow();
	bool createRenderer();
	bool initSDLImage();
};
