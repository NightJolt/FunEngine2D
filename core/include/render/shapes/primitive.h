#include "../../globals.h"

namespace fun {
    class primitive_t : public sf::Drawable {
        public:

            primitive_t(std::vector <sf::Vertex>&, sf::PrimitiveType);

        private:

            void draw(sf::RenderTarget&, sf::RenderStates) const override;

            std::vector <sf::Vertex> m_vertices;
            sf::PrimitiveType m_primitive_type;
    };
}
