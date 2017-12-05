#include "Graphics.h"
#include <iostream>



Graphics::Graphics()
{
	if (!init()) { printf("Failed to initialize!\n"); }
	if (!loadMedia()) { printf("Failed to load media!\n"); }
}

Graphics::~Graphics() {}

bool Graphics::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	std::unique_ptr<SDL_Window, sdl_deleter> window(
		SDL_CreateWindow("Satellite visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1029, 873, SDL_WINDOW_SHOWN),
		sdl_deleter());
	if (!window) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = std::move(window);

	std::unique_ptr<SDL_Renderer, sdl_deleter> renderer(
		SDL_CreateRenderer(gWindow.get(), -1, SDL_RENDERER_ACCELERATED),
		sdl_deleter());

	if (!renderer) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gRenderer = std::move(renderer);

	SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

	return true;
}

bool Graphics::loadMedia() {
	
	SDL_Surface* loadedSurface = nullptr;

	std::string path = "";


	std::unique_ptr<SDL_Texture, sdl_deleter> newTexture(
			SDL_CreateTextureFromSurface(gRenderer.get(), loadedSurface),
			sdl_deleter());

	background = std::move(newTexture);
	SDL_FreeSurface(loadedSurface);

	SDL_Rect bg = { 0, 0, 1029, 873 };
	SDL_RenderCopy(gRenderer.get(), background.get(), nullptr, &bg);
	SDL_RenderPresent(gRenderer.get());
	SDL_Delay(6000);
	return true;
}

void Graphics::close() {
	//this order is important!
	background.reset();
	gRenderer.reset();
	gWindow.reset();

	SDL_Quit();
}