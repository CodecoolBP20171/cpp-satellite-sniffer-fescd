#pragma once

#include <memory>

#include <SDL.h>
#include <cstdio>
#include <string>
#include <map>

class Graphics
{
public:
	Graphics();
	~Graphics();

	void close();

private:

	struct sdl_deleter
	{
		void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
		void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
		void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
	};

	std::unique_ptr<SDL_Window, sdl_deleter> gWindow = nullptr;
	std::unique_ptr<SDL_Renderer, sdl_deleter> gRenderer = nullptr;

	std::unique_ptr<SDL_Texture, sdl_deleter> background = nullptr;
	
	bool init();
	bool loadMedia();

};
