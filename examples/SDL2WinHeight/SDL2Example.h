#pragma once
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_image.h"
#include <map>
#include "../../src/HexMap.h"

class SDL2Example
{
private:
	bool isLoaded = false;

	SDL_Window* window;
	SDL_Event ev;

	std::map<std::string, SDL_Texture*> textureMap;

	HexMap* hexMap;
	
	Tile* tileTargetedByMouse;

	void initWindow();

	void initVars();


	//returns the first object in the objectList that exists at XY
	// retuns NULL if no such object exists
	Tile* getTileAtXY(int x, int y);


public:
	int windowHeight = 720;
	int windowWidth = 1280;

	bool isRunning = true;

	inline static SDL_Renderer* renderer;

	// xy offsets used to drag maps around. in px.
	int xOffset = 0;
	int yOffset = 0;

	// stores width of the current hex tile so that objects of different sizes can be placed correctly
	int hexTileWidth = 0;

	SDL2Example();
	virtual ~SDL2Example();

	void update();
	void render();

};