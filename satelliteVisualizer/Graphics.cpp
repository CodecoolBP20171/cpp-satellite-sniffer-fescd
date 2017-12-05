#include "Graphics.h"


Graphics::~Graphics() {
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (!createWindow()) return false;
	if (!createRenderer()) return false;
	if (!initSDLImage()) return false;
	return true;
}

std::shared_ptr<Texture> Graphics::loadTexture(const std::string& filename) {
	SDL_Texture* imgTexture = IMG_LoadTexture_RW(renderer,
		SDL_RWFromFile(filename.c_str(), "rb"),
		1);
	if (nullptr == imgTexture) {
		printf("File not found: %s SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
	}
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(imgTexture);
	return texture;
}

bool Graphics::createWindow() {
	window = SDL_CreateWindow("Flat Earth Society Codecool Division", 40, 40, 823, 698, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Graphics::createRenderer() {
	if (!window) return false;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Graphics::initSDLImage() {
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
	return true;
}
