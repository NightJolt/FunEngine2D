#pragma once

#include "../../globals.h"
#include "../texture.h"
#include "../shader.h"

namespace fun::render {
    struct vertice_iterator_t {
        vertex_t* begin_p;
        vertex_t* end_p;
        vertex_t* ptr;

        vertice_iterator_t();
        vertice_iterator_t(std::vector <vertex_t>&, size_t n);

        vertex_t* begin();
        const vertex_t* begin() const;
        vertex_t* end();
        const vertex_t* end() const;
    };

    class primitive_t : public sf::Drawable {
    public:
        primitive_t() = default;
        primitive_t(std::vector <vertex_t>&, sf::PrimitiveType);

        void bind_texture(texture_t);
        // void bind_shader(shader_t);

        void set_vertices(const std::vector <vertex_t>&);
        void set_primitive_type(sf::PrimitiveType);

        void resize(uint32_t);
        uint32_t get_size() const;

        vertice_iterator_t get_iterator();
        vertice_iterator_t get_iterator(uint32_t); 
        vertex_t& get_vertex(uint32_t);

        void batch(primitive_t& primitive);

    private:
        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        sf::PrimitiveType m_primitive_type;

        texture_t m_texture;
        // shader_t m_shader;

        std::vector <vertex_t> m_vertices;
    };
}