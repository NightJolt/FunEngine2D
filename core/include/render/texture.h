#pragma once

#include "../globals.h"
#include "../vec2.h"

namespace fun {
    class texture_t {
        public:
            explicit texture_t(sf::Texture* = nullptr, vec2u_t = { 1, 1 });

            void set_texture(sf::Texture*);
            void set_grid_size(vec2u_t);

            sf::Texture* get_texture() const;
            uint32_t4 get_subtexture(uint32_t) const;

        private:
            sf::Texture* m_texture;
            vec2u_t m_grid_size;

            vec2u_t m_cell_size;
    };
}