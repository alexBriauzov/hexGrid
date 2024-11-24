#include "HexMap.h"

HexMap::HexMap(uint32_t TileWidth, uint32_t TileHeight, bool mapMd){
    this->mapMode = mapMd;
    this->width = TileWidth;
    this->height = TileHeight;
    if(mapMd){
        this->size = TileWidth/2.;
    } else {
        this->size = TileWidth/sqrt3;
    }
}

HexMap::~HexMap(){
    clearMap();
}

void HexMap::loadAround(int rc, int qc, int radius){
    for(int r = -radius; r <= 0; r++){
        for(int q = -radius - r; q <= radius; q++){
            if(!isTileLoaded(rc+r, qc+q))
                spawnTile(rc+r, qc+q);
        }
    }
    for(int r = 1; r <= radius; r++)
        for(int q = -radius; q <= radius - r; q++){
            if(!isTileLoaded(rc+r, qc+q))
                spawnTile(rc+r, qc+q);
        }
}


void HexMap::unloadAround(int rc, int qc, int radius){
    for(Tile* tile : loadedTiles){
        if (axialDistance(rc, qc, tile->r, tile->q) > radius)
            deleteTile(tile);
    }
}

void HexMap::clearMap(){
     while(loadedTiles.size()){
        delete(loadedTiles.front());
        loadedTiles.pop_front();
    }
}

Tile* HexMap::getTileAtRQ(int r, int q){
    for(Tile* tile : loadedTiles){
        if (r == tile->r && q ==  tile->q)
            return tile;
    }
    return NULL;
}

std::pair<int, int> HexMap::rqTOxy(int r, int q) {
    if(mapMode){
	    return std::pair(scale*size*(3. / 2 * q) + offsetX, scale*size * (sqrt3 / 2 * q + sqrt3 * r) + offsetY);
    } else {
        return std::pair(scale*size*(sqrt3 * q + sqrt3/2 * r) + offsetX, scale*size * (3. / 2  * r) + offsetY);
    }
}

std::pair<int, int> HexMap::rqTOxy(int r, int q, int h) {
    if(mapMode){
	return std::pair(scale*size*(3. / 2 * q) + offsetX, scale*size * (sqrt3 / 2 * q + sqrt3 * (r - h*Hscale)) + offsetY);
    } else {
        return std::pair(scale*size*(sqrt3 * q + sqrt3/2 * r) + offsetX, scale*size * (3. / 2  * (r - h*Hscale)) + offsetY);
    }
}

std::pair<int, int> HexMap::getTileDimentions() {
	return std::pair(scale*width, scale * height);
}

bool HexMap::isPointWithinTile(int x, int y, Tile* tile) {
    std::pair<int, int> pos = rqTOxy(tile->r, tile->q, tile->h);

	if (x < pos.first || x > pos.first + width*scale)
		return false;

	if (y < pos.second)
		return false;

	if (y < pos.second + width*scale*0.22)
		if (x < pos.first + width*scale*0.22 && (y - pos.second) + (x - pos.first) < width*scale*0.22 )
			return false;
		else if (x > pos.first + (width*scale - width*scale*0.22)  && (y - pos.second) + (width*scale + pos.first - x) < width*scale*0.22)
			return false;

	return true;
}





Tile* HexMap::spawnTile(int r, int q){
    Tile* tile = new Tile(r, q, determineTextureAt(r,q));
    loadedTiles.push_back(tile);
    return tile;
}

bool HexMap::deleteTile(Tile* tile){
    if(tile == NULL)
        return false;
    loadedTiles.remove(tile);
    delete (tile);
    return true;
}

void HexMap::sortTileList() {
	loadedTiles.sort([](Tile* lhs, Tile* rhs) {
		    return (
				    lhs->r < rhs->r
				    || 
				    (lhs->r == rhs->r && lhs->q < rhs->q)
			);
	    });
}

bool HexMap::isTileLoaded(int r, int q){
    for (Tile* tile : this->loadedTiles)
        if(tile->r == r && tile->q == q)
            return true;
    return false;
}


uint32_t HexMap::axialDistance(int r1, int q1, int r2, int q2){
    return (abs(q1 - q2) 
          + abs(q1 + r1 - q2 - r2)
          + abs(r1 - r2)) / 2;
}

int HexMap::determineHeightAt(int r, int q){
    // To make map generation more interesting, add random height for tiles
    // Adding PerlinNoise using the XY from HexMap::rqTOxy can be a good start
    return 0;
}

const char* HexMap::determineTextureAt(int r, int q){
    // To make map generation more interesting, add different textures for tiles
    // Adding diffused PerlinNoise can help with creating different biomes for the map with different textures
    return deafultTexture.c_str();
}