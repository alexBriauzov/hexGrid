#pragma once
#include "Tile.h"
#include <string>
#include <list>

class HexMap{
public:

    // List of tiles currently loaded into the scene
    std::list<Tile*> loadedTiles;

    // If the hex texture is flat at the top, this is true
    // If the hex texture is pointy at the top, this is false
    bool mapMode = true;


    std::string deafultTexture;

    // Default costructor
    // mapMode is true if hexagons are flat at the top
    HexMap(uint32_t TileWidth, uint32_t TileHeight, bool mapMode);

    // Default destructor
    virtual ~HexMap();

    // Loads tiles within a radius around RQ in a shape of a larger hexagon
    // If tiles do not alrady exist in loadedTiles within radius, creates new them
    void loadAround(int r, int q, int radius);

    // Unloads tiles outside a radius around RQ
    // If tiles in loadedTiles are outside the radius, deletes them
    void unloadAround(int r, int q, int radius);

    // Clears all elements in the map
    void clearMap();

    // Sort loadedTiles so that when render call comes objects are layered correctly
	void sortTileList();

    // Returns the pointer to the Tile object from loadedTiles with the given r and q values
    // If loadedTiles contains no such tile, return null
    Tile* getTileAtRQ(int r, int q);

    // Axial coordinate to screen XY coordinate translation for this map
    std::pair<int, int> rqTOxy(int r, int q);

    // Axial coordinate + h modifier to screen XY coordinate translation for this map
    std::pair<int, int> rqTOxy(int r, int q, int h);

    // Returns the scaled tile width and height
    std::pair<int, int> getTileDimentions();

    bool isPointWithinTile(int x, int y, Tile* tile);

    //set the size of the tiles (1 = pixel to pixel, 0.5 = half-size and so on...)
    double scale = 1;

    //height modifier scale (tiles are shifted vertically in such a way, that for rqTOxy r = r - h*Hscale) ((remember to use rqTOxy(int r, int q, int h)))
    double Hscale = 0.5;
    
    // The offset from top left of the screen to map (0,0)
    // For example if offsetX = screenWidth/2, offsetY = screenHeight/2 then Tile(0,0) is located at the center of the screen
    int offsetX = 0;

    // The offset from top left of the screen to map (0,0)
    // For example if offsetX = screenWidth/2, offsetY = screenHeight/2 then Tile(0,0) is located at the center of the screen
    int offsetY = 0;

private:

    // Square root of 3 saved into a double to its max accuracy
    double sqrt3 = 1.7320508075688773;

    // Size variable used for correctly placing tiles on the XY screen
    double size = 100;

    double width = 100;
    double height = 100;

    // The translation X pivot for every tile in the map
    // Top left corner of the texture by default
    int TileCenterX = 0;

    // The translation Y pivot for every tile in the map
    // Top left corner of the texture by default
    int TileCenterY = 0;

    // A ratio determining how much tile texture has ben scaled on the y axis
    // if verticalRatio = 1 the hexagon texture is a true hexagon (height:width of 1:1.1547)
    // if verticalRatio = 0.5 the hexagon texture is half-height (height:width of 1:2.3094)
    double verticalRatio = 1;

    // Spawn a tile at RQ and add it to loadedTiles
    Tile* spawnTile(int r, int q);

    // Delete Tile and remove it from loadedTiles
    // Returns true if tile was successfuly deleted
    bool deleteTile(Tile* tile);

    // Returns true if tile is in the loadedTiles list
    bool isTileLoaded(int r, int q);

    // Returns an uint32_t distance from one axial coordinate to another
    uint32_t axialDistance(int r1, int q1, int r2, int q2);

    // Returns a height for the tile on the global map
    int determineHeightAt(int r, int q);

    // Returns a texture for the tile on the global map
    const char* determineTextureAt(int r, int q);

};