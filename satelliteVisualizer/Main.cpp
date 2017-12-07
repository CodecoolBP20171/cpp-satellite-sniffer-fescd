#include <iostream>
#include "Graphics.h"
#include "Sky.h"
#include "Main.h"

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

	Graphics graphics;
	Sky sky;

	bool quit = false;
	int timeDelta = 0;
	

	Uint32 timepassed = 0;
	Uint32  timestep = 16;
	
	while (!quit) {
		vector<MapCoordinates> coords = sky.GetSATPos(timeDelta);
		int max = coords.size();
		
		for (auto i = 0; i < max; i++) {
			graphics.putSatToSky(coords[i].first, coords[i].second);
		}
			
		graphics.showAllSat();
		SDL_Delay(1000);
		timeDelta++;
		if (timeDelta == 180) quit = true;
	}
	
	graphics.~Graphics();
	system("pause");
	
	return 0;
}