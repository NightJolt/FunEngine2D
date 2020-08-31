#include "TileMap/TileSprite.h"

TileSprite::TileSprite(sf::Texture& texture, int id, sf::Vector2i p) : tile_id_index(id) {
    sprite = sf::Sprite(texture);

    float s = TILE_SIZE / TILE_ATLAS_SIZE * TILE_TEXTURE_SIZE * 4.f; // del 2.f
    sprite.scale(sf::Vector2f(s, s));

    sprite.setPosition(Math::GridToWorld(p));
}

void TileSprite::Draw(sf::RenderWindow& window) {
    if (tile_id_index >= 0) {
        window.draw(sprite);
    }
}

void TileSprite::AppendState(unsigned int state_mask) {
    if (state_mask <= TILE_FULL_MASK) { // place tile
        this->state |= state_mask;
    } else { // destroy tile
        this->state &= state_mask;
    }

    int rand_texture_coord_shift = TILE_ATLAS_SIZE / RAND_TEXTURE_COUNT;
    int rand_texture_ind = rand() % RAND_TEXTURE_COUNT;
    sprite.setTextureRect(sf::IntRect(TILE_TEXTURE_SIZE * state + rand_texture_coord_shift * rand_texture_ind, TILE_TEXTURE_SIZE * tile_id_index, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE));
}