#pragma once

#include <SDL_render.h>

class Texture {
public:
	Texture() {};
	Texture(SDL_Texture* texture);
	~Texture();
	void render(SDL_Renderer* renderer, const SDL_Rect* pos);
	SDL_Texture* getSDLTexture() { return texture; }
private:
	SDL_Texture * texture;
};
