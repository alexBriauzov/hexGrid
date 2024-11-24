# hexGrid
A modular hexagonal grid generator for 2D applications made in c++

Most math logic are based off the Hexagonal Grid guide by Red Blob Games:
https://www.redblobgames.com/grids/hexagons/#neighbors

![](https://github.com/alexBriauzov/hexGrid/blob/main/github/hexgif.gif)

All relevant code is contained within src directory

Rendering examples are created using SDL2, but core features are designed to work with any graphics library

## Tile
![](https://github.com/alexBriauzov/hexGrid/blob/main/github/tilecoord.gif)
![](https://github.com/alexBriauzov/hexGrid/blob/main/github/tilesHeights.jpg) 
- q, r - position of a tile in axial coordinates
- h - vertical offset of a tile
- onLClick(), onRClick() - pointers to functions that will be called whenever a tile is clicked

## HexMap
![](https://github.com/alexBriauzov/hexGrid/blob/main/github/hexload.gif)
- loadAround(r, q, radius) - Loads tiles within a radius around coordinates r q
- unloadAround(r, q, radius) - Unloads tiles outside a radius around coordinates r q
