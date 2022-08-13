#pragma once

#include "../../globals.h"

namespace fun {
    class primitive_t : public sf::Drawable {
    public:
        primitive_t() = default;
        primitive_t(std::vector <sf::Vertex>&, sf::PrimitiveType);

        std::vector <sf::Vertex>& get_vertices();
        void set_primitive_type(sf::PrimitiveType);

        void batch(primitive_t& primitive);

    private:

        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        std::vector <sf::Vertex> m_vertices;
        sf::PrimitiveType m_primitive_type;
    };
}
