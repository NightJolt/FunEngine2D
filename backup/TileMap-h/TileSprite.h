#pragma once

#include "../../Core/Globals.h"
#include "../../Core/Math.h"

#define TILE_TOP_MASK 1
#define TILE_RIGHT_MASK 2
#define TILE_DOWN_MASK 4
#define TILE_LEFT_MASK 8

#define TILE_FULL_MASK (TILE_TOP_MASK | TILE_RIGHT_MASK | TILE_DOWN_MASK | TILE_LEFT_MASK)

class TileSprite {
public:
    TileSprite(sf::Texture&, int, sf::Vector2i);

    void Draw(sf::RenderWindow&);
    void AppendState(unsigned int);

private:
    sf::Sprite sprite;

    unsigned int state = 0;
    int tile_id_index = 0;
};