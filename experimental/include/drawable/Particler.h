#pragma once

#include "../../../core/include/Globals.h"
#include "../../../core/include/_Math.h"
#include "../../../core/include/_Time.h"

namespace fun {
    class Particler : public sf::Drawable {
        public:

            enum RenderType {
                Quads
            };

            struct EmitData {
                sf::Color min_color_start;
                sf::Color max_color_start;
                sf::Color min_color_end;
                sf::Color max_color_end;

                sf::Vector2f min_spawn_offset;
                sf::Vector2f max_spawn_offset;

                float min_spawn_radius;
                float max_spawn_radius;

                float min_lifetime;
                float max_lifetime;

                float min_direction_angle;
                float max_direction_angle;
                float direction_angle_step;

                float min_velocity_start;
                float max_velocity_start;
                float min_velocity_end;
                float max_velocity_end;

                float min_torque_start;
                float max_torque_start;
                float min_torque_end;
                float max_torque_end;

                float min_size_start;
                float max_size_start;
                float min_size_end;
                float max_size_end;

                /*
                    noise texture
                    bitmap texture
                */
            };

            struct ParticleData {
                sf::Vector2f position;
                float direction_angle;
                float body_angle;
                float velocity;
                float body_radius;
            };

            Particler(RenderType, uint32_t, uint8_t = 4);
            ~Particler() final;

            // Particler(Particler&&) noexcept;
            // Particler& operator =(Particler&&) noexcept;

            void Emit(uint32_t, const EmitData&);
            void Update();

            fun::Transform transform;

        private:

            void UpdateRange(size_t, uint32_t);

            void draw(sf::RenderTarget&, sf::RenderStates) const override;

            RenderType render_type;
            size_t size = 0;

            std::vector <ParticleData> particles;
            std::vector <sf::Vertex> vertices;
            // std::vector <std::thread> thread_pool;
    };
}