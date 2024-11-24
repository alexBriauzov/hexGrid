#include "SDL2/SDL.h"
#include <iostream>
#include "SDL2Example.h"


int main(int argv, char** args) {

    SDL_Init(SDL_INIT_EVERYTHING);
	SDL2Example ex;

	while(!ex.isRunning){
		SDL_Delay(10);
	}
	while (ex.isRunning) {
		SDL_Delay(10);
		ex.update();
		ex.render();
	}

	std::cout<<"quitting...\n";
	SDL_Quit();	
	return 0;
}