#pragma once

#include "../../globals.h"
#include "../../transform.h"
#include "../../_math.h"
#include "../../_time.h"
#include "../../tools/debugger.h"

namespace fun {
    class particler_t : public sf::Drawable {
        // public:

        //     static const uint8_t MAX_SUPPORTED_THREAD_COUNT = 8;

        //     enum primitive_type_t {
        //         quads
        //     };

        //     struct emit_data_t {
        //         float min_lifetime = 5;
        //         float max_lifetime = 10;

        //         sf::Color min_color_start = sf::Color(0, 0, 0);
        //         sf::Color max_color_start = sf::Color(0, 0, 0);
        //         sf::Color min_color_end = sf::Color(0, 0, 0);
        //         sf::Color max_color_end = sf::Color(0, 0, 0);

        //         vec2f_t min_spawn_offset = vec2f_t(0, 0);
        //         vec2f_t max_spawn_offset = vec2f_t(0, 0);

        //         float min_spawn_radius = 0;
        //         float max_spawn_radius = 0;

        //         float min_direction_angle = 0;
        //         float max_direction_angle = math::constants::double_pi;
        //         float direction_angle_step_min = 0;
        //         float direction_angle_step_max = 0;

        //         float min_velocity_start = 50;
        //         float max_velocity_start = 30;
        //         float min_velocity_end = 10;
        //         float max_velocity_end = 20;

        //         float min_torque_start = 0;
        //         float max_torque_start = 0;
        //         float min_torque_end = 0;
        //         float max_torque_end = 0;

        //         float min_size_start = 1;
        //         float max_size_start = 2;
        //         float min_size_end = 1;
        //         float max_size_end = 2;

        //         /*
        //             noise texture
        //             bitmap texture
        //         */
        //     };

        //     struct particle_data_t {
        //         float lifetime;
        //         vec2f_t position;
        //         float direction_angle;
        //         float velocity;
        //         float velocity_step;
        //         float body_angle;
        //         float body_radius;
        //     };

        //     particler_t(primitive_type_t, uint32_t, uint8_t = 4);
        //     ~particler_t() final;

        //     particler_t(const particler_t&) noexcept;
        //     particler_t& operator =(const particler_t&) noexcept;

        //     particler_t(particler_t&&) noexcept;
        //     particler_t& operator =(particler_t&&) noexcept;

        //     void emit(uint32_t, const emit_data_t&);
        //     void update();

        //     fun::transform_t transform;

        // private:

        //     struct thread_data_t {
        //         uint32_t index;
        //         uint32_t count;
        //     };

        //     struct call_data_t {
        //         call_data_t(int, particler_t*);

        //         const int id;
        //         particler_t* particler;

        //         void operator()();
        //     };

        //     void update_range(uint32_t, uint32_t);

        //     void draw(sf::RenderTarget&, sf::RenderStates) const override;
            

        //     primitive_type_t primitive_type = primitive_type_t::quads;

        //     uint32_t max_count = 0;
        //     uint32_t count = 0;

        //     particle_data_t* particles = nullptr;
        //     sf::Vertex* vertices = nullptr;


        //     uint8_t thread_count = 0;

        //     thread_data_t* thread_data = nullptr;
        //     std::thread* thread_pool = nullptr;
        
        //     std::counting_semaphore <MAX_SUPPORTED_THREAD_COUNT> thread_launcher = std::counting_semaphore <MAX_SUPPORTED_THREAD_COUNT> (0);
        //     std::counting_semaphore <MAX_SUPPORTED_THREAD_COUNT> thread_blocker = std::counting_semaphore <MAX_SUPPORTED_THREAD_COUNT> (0);

        //     volatile bool kill_threads = false;
    };
}