#pragma once

#include "../globals.h"

namespace fun::render {
    class shader_t {
    public:
        explicit shader_t(sf::Shader* = nullptr);

        void set_shader(sf::Shader*);
        sf::Shader* get_shader() const;

    private:
        sf::Shader* m_shader;
    };
}