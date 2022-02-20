#include "../../Globals.h"

namespace fun {
    class Primitive : public sf::Drawable {
        public:

            Primitive(std::vector <sf::Vertex>&, sf::PrimitiveType);

        private:

            void draw(sf::RenderTarget&, sf::RenderStates) const override;

            std::vector <sf::Vertex> m_vertices;
            sf::PrimitiveType m_primitive_type;
    };
}