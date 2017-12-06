#include <iostream>
#include "Graphics.h"
#include "Main.h"
#include "Sky.h"

using namespace std;

bool handleEvents(SDL_Event &event) {
	//clickedX = -1; clickedY = -1;
	bool quit = false;
	if (event.type == SDL_QUIT) { return true; }
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		//clickedX = x; clickedY = y;
		std::cout << "Clicked @ x = " << x << " , y = " << y << std::endl;
	}
	return quit;
}

int main(int argc, char * argv[]) {

	Sky sky;
	sky.evaluate();

	Graphics graphics;
	graphics.init();
	std::shared_ptr<Texture> background = graphics.loadTexture("MercatorEarth.png");
	
	bool quit = false;
	Uint32 timepassed = 0;
	Uint32  timestep = 16;
	while (!quit) {
		timepassed = SDL_GetTicks();
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event) != 0) {
			quit = handleEvents(sdl_event);
			SDL_RenderClear(graphics.getRenderer());
			background->render(graphics.getRenderer(), nullptr);
			SDL_RenderPresent(graphics.getRenderer());
			while (timepassed + timestep > SDL_GetTicks()) {
				SDL_Delay(0);
			}
		}
	}
	graphics.~Graphics();
	system("pause");
	
	return 0;
}