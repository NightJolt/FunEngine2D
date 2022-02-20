#pragma once

#include "../../../core/include/Globals.h"
#include "../../../core/include/_Math.h"
#include "../../../core/include/_Time.h"
#include "../../../core/include/tools/Debugger.h"

namespace fun {
    class Particler : public sf::Drawable {
        public:

            static const uint8_t MAX_SUPPORTED_THREAD_COUNT = 8;

            enum RenderType {
                Quads
            };

            struct EmitData {
                float min_lifetime = 5;
                float max_lifetime = 10;

                sf::Color min_color_start = sf::Color(0, 0, 0);
                sf::Color max_color_start = sf::Color(0, 0, 0);
                sf::Color min_color_end = sf::Color(0, 0, 0);
                sf::Color max_color_end = sf::Color(0, 0, 0);

                sf::Vector2f min_spawn_offset = sf::Vector2f(0, 0);
                sf::Vector2f max_spawn_offset = sf::Vector2f(0, 0);

                float min_spawn_radius = 0;
                float max_spawn_radius = 0;

                float min_direction_angle = 0;
                float max_direction_angle = math::constants::double_pi;
                float direction_angle_step_min = 0;
                float direction_angle_step_max = 0;

                float min_velocity_start = 50;
                float max_velocity_start = 30;
                float min_velocity_end = 10;
                float max_velocity_end = 20;

                float min_torque_start = 0;
                float max_torque_start = 0;
                float min_torque_end = 0;
                float max_torque_end = 0;

                float min_size_start = 1;
                float max_size_start = 2;
                float min_size_end = 1;
                float max_size_end = 2;

                /*
                    noise texture
                    bitmap texture
                */
            };

            struct ParticleData {
                float lifetime;
                sf::Vector2f position;
                float direction_angle;
                float velocity;
                float velocity_step;
                float body_angle;
                float body_radius;
            };

            Particler(RenderType, uint32_t, uint8_t = 4);
            ~Particler() final;

            Particler(const Particler&) noexcept;
            Particler& operator =(const Particler&) noexcept;

            Particler(Particler&&) noexcept;
            Particler& operator =(Particler&&) noexcept;

            void Emit(uint32_t, const EmitData&);
            void Update();

            fun::Transform transform;

        private:

            struct ThreadData {
                uint32_t index;
                uint32_t count;
            };

            struct CallData {
                CallData(int, Particler*);

                const int id;
                Particler* particler;

                void operator()();
            };

            void UpdateRange(uint32_t, uint32_t);

            void draw(sf::RenderTarget&, sf::RenderStates) const override;
            

            RenderType render_type = RenderType::Quads;

            uint32_t max_count = 0;
            uint32_t count = 0;

            ParticleData* particles = nullptr;
            sf::Vertex* vertices = nullptr;


            uint8_t thread_count = 0;

            ThreadData* thread_data = nullptr;
            std::thread* thread_pool = nullptr;
        
            std::counting_semaphore <MAX_SUPPORTED_THREAD_COUNT> thread_launcher = std::counting_semaphore <MAX_SUPPORTED_THREAD_COUNT> (0);
            std::counting_semaphore <MAX_SUPPORTED_THREAD_COUNT> thread_blocker = std::counting_semaphore <MAX_SUPPORTED_THREAD_COUNT> (0);

            volatile bool kill_threads = false;
    };
}