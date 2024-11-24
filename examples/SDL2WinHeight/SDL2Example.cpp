#include "SDL2Example.h"
#include <iostream>

SDL2Example::SDL2Example() {
	this->initVars();
	this->initWindow();
}

SDL2Example::~SDL2Example() {
}

void SDL2Example::initWindow()
{
	window = SDL_CreateWindow( "SDL2 Hex Map Example with heights", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	textureMap["pointy"] = IMG_LoadTexture(renderer, "../../assets/hexagonPointy.png");
	
	hexMap->Hscale = 0.5;
	hexMap->loadAround(0, 0, 4);
	hexMap->getTileAtRQ(0,0)->h = 1;
	hexMap->getTileAtRQ(0,1)->h = 2;
	hexMap->getTileAtRQ(0,-1)->h = -1;
	hexMap->getTileAtRQ(2,2)->h = -1;
	hexMap->getTileAtRQ(2,-1)->h = -1;
	hexMap->getTileAtRQ(-2,-2)->h = 2;
	hexMap->getTileAtRQ(-3,3)->h = 2;
	
	hexMap->sortTileList();

	isLoaded = true;
}

void SDL2Example::initVars()
{
	windowHeight = 720;
	windowWidth = 1280;
	tileTargetedByMouse = NULL;
	hexMap = new HexMap(785, 3140, false);
	hexMap->offsetX = windowWidth/2;
	hexMap->offsetY = windowHeight/2;
	hexMap->scale = 0.1;
	hexMap->deafultTexture = "pointy";
}

void SDL2Example::update()
{
	if(!isLoaded)
		return;

	//check to see if mouse moved since last frame

	int newMouseX; int newMouseY;
	SDL_GetMouseState(&newMouseX,&newMouseY);

	Tile* e = getTileAtXY(newMouseX, newMouseY);

	if(tileTargetedByMouse != e && tileTargetedByMouse != NULL)
		tileTargetedByMouse->onExit(tileTargetedByMouse);

	if(tileTargetedByMouse != e && e != NULL)
		e->onEnter(e);
	
	tileTargetedByMouse = e;

	while (SDL_PollEvent(&ev))
		switch (ev.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_MOUSEBUTTONUP:
			//Left button released
			if(ev.button.button == SDL_BUTTON_LEFT){
				if(tileTargetedByMouse != NULL)
					tileTargetedByMouse->onLClick(tileTargetedByMouse);
			}
			//Right button released
			if(ev.button.button == SDL_BUTTON_RIGHT){
				if(tileTargetedByMouse != NULL)
					tileTargetedByMouse->onRClick(tileTargetedByMouse);
			}

			break;

		default:
			break;
	}
}

void SDL2Example::render()
{
	if(!isLoaded)
		return;

	SDL_RenderClear(renderer);

	for (Tile* tile : this->hexMap->loadedTiles){
		std::pair<int, int> XY = hexMap->rqTOxy(tile->r, tile->q, tile->h);
		std::pair<int, int> HW = hexMap->getTileDimentions();
		SDL_Rect frame;
		frame.x = XY.first;
		frame.y = XY.second;
		frame.w = HW.first;
		frame.h = HW.second;
		SDL_SetTextureColorMod(textureMap[tile->texture], tile->textureColor[0],tile->textureColor[1], tile->textureColor[2]);
		SDL_RenderCopy(renderer, textureMap[tile->texture], NULL, &frame);
		SDL_SetTextureColorMod(textureMap[tile->texture], 255, 255, 255);
	}

	SDL_RenderPresent(renderer);
}

Tile* SDL2Example::getTileAtXY(int x, int y) {
	for (std::list<Tile*>::reverse_iterator i = hexMap->loadedTiles.rbegin(); i != hexMap->loadedTiles.rend(); ++i)
		if (hexMap->isPointWithinTile(x,y,*i))
			return *i;
	return NULL;
}
