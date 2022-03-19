#include "render/shapes/particler.h"

// fun::particler_t::particler_t(primitive_type_t pt, uint32_t mc, uint8_t tc) : primitive_type(pt), max_count(mc), thread_count(tc) {
// #if defined(DEBUG_BUILD)
//     assert(thread_count > 0 && thread_count <= MAX_SUPPORTED_THREAD_COUNT);
// #endif

//     // ? setup threads
//     if (thread_count > 1) {
//         thread_data = new thread_data_t[thread_count];
//         thread_pool = new std::thread[thread_count];

//         for (int i = 0; i < thread_count; i++) {
//             thread_pool[i] = std::thread(call_data_t(i, this));
//         }
//     }

//     if (primitive_type == primitive_type_t::quads) {
//         particles = new particle_data_t[max_count];
//         vertices = new sf::Vertex[max_count * 4];
//     }
// }

// fun::particler_t::~particler_t() {
//     // ? destroy threads
//     if (thread_count > 1 && thread_pool != nullptr) {
//         kill_threads = true;

//         thread_launcher.release(thread_count);

//         for (int i = 0; i < thread_count; i++) {
//             thread_pool[i].join();
//         }
//     }

//     delete[] particles;
//     delete[] vertices;

//     delete[] thread_data;
//     delete[] thread_pool;
// }


// fun::particler_t::call_data_t::call_data_t(int id, particler_t* particler) : id(id), particler(particler) {}

// void fun::particler_t::CallData::operator ()() {
//     thread_data_t& data = particler->thread_data[id];

//     while (true) {
//         particler->thread_launcher.acquire();

//         if (particler->kill_threads) {
//             return;
//         }

//         if (data.count) particler->UpdateRange(data.index, data.count);
        
//         particler->thread_blocker.release();
//     }
// }



// #pragma region copy/move constructors

// fun::Particler::Particler(const Particler& _other) noexcept {
//     println("Copying ()");

//     Particler& other = const_cast <Particler&> (_other);

//     // ? assign
//     {
//         // ? particler related
//         {
//             transform = other.transform;

//             render_type = other.render_type;

//             max_count = other.max_count;
//             count = other.count;

//             particles = other.particles;
//             vertices = other.vertices;
//         }
        
//         // ? threads related
//         {
//             thread_count = other.thread_count;

//             thread_data = other.thread_data;
//             thread_pool = other.thread_pool;
//         }
//     }

//     // ? clear
//     {
//         other.particles = nullptr;
//         other.vertices = nullptr;

//         other.thread_data = nullptr;
//         other.thread_pool = nullptr;
//     }
// }

// fun::Particler& fun::Particler::operator =(const Particler& _other) noexcept {
//     println("Copying =");

//     if (this == &_other) return *this;

//     this->~Particler();

//     Particler& other = const_cast <Particler&> (_other);

//     // ? assign
//     {
//         // ? particler related
//         {
//             transform = other.transform;

//             render_type = other.render_type;

//             max_count = other.max_count;
//             count = other.count;

//             particles = other.particles;
//             vertices = other.vertices;
//         }
        
//         // ? threads related
//         {
//             thread_count = other.thread_count;

//             thread_data = other.thread_data;
//             thread_pool = other.thread_pool;
//         }
//     }

//     // ? clear
//     {
//         other.particles = nullptr;
//         other.vertices = nullptr;

//         other.thread_data = nullptr;
//         other.thread_pool = nullptr;
//     }

//     return *this;
// }

// fun::Particler::Particler(Particler&& other) noexcept {
//     println("Moving ()");
    
//     // ? assign
//     {
//         // ? particler related
//         {
//             transform = other.transform;

//             render_type = other.render_type;

//             max_count = other.max_count;
//             count = other.count;

//             particles = other.particles;
//             vertices = other.vertices;
//         }
        
//         // ? threads related
//         {
//             thread_count = other.thread_count;

//             thread_data = other.thread_data;
//             thread_pool = other.thread_pool;
//         }
//     }

//     // ? clear
//     {
//         other.particles = nullptr;
//         other.vertices = nullptr;

//         other.thread_data = nullptr;
//         other.thread_pool = nullptr;
//     }
// }

// fun::Particler& fun::Particler::operator =(Particler&& other) noexcept {
//     println("Moving =");

//     if (this == &other) return *this;

//     this->~Particler();
    
//     // ? assign
//     {
//         // ? particler related
//         {
//             transform = other.transform;

//             render_type = other.render_type;

//             max_count = other.max_count;
//             count = other.count;

//             particles = other.particles;
//             vertices = other.vertices;
//         }
        
//         // ? threads related
//         {
//             thread_count = other.thread_count;

//             thread_data = other.thread_data;
//             thread_pool = other.thread_pool;
//         }
//     }

//     // ? clear
//     {
//         other.particles = nullptr;
//         other.vertices = nullptr;

//         other.thread_data = nullptr;
//         other.thread_pool = nullptr;
//     }

//     return *this;
// }

// #pragma endregion



// void fun::particler_t::Emit(uint32_t emit_count, const EmitData& data) {
//     if (count == max_count || emit_count == 0) return;

//     emit_count = std::min((uint32_t)(max_count - count), emit_count);
//     uint32_t vertex_index = (count - 1) * 4;

//     for (auto particle = particles + count; particle != particles + count + emit_count; particle++) {
//         particle->lifetime = fun::math::random_f(data.min_lifetime, data.max_lifetime);
//         particle->position = transform.position;
//         particle->direction_angle = fun::math::random_f(data.min_direction_angle, data.max_direction_angle) + transform.rotation;
//         particle->body_angle = fun::math::random_f(0, fun::math::constants::double_pi);
//         particle->velocity = fun::math::random_f(data.min_velocity_start, data.max_velocity_start);
//         particle->velocity_step = (fun::math::random_f(data.min_velocity_start, data.max_velocity_start) - particle->velocity) / particle->lifetime;
//         particle->body_radius = data.max_size_start * fun::math::constants::half_sqrt_2;

//         vertex_index += 4;
//     }

//     count += emit_count;
// }

// void fun::Particler::Update() {
//     if (thread_count == 1) {
//         UpdateRange(0, count);
//     } else {
//         uint32_t thread_size = count / thread_count;
//         uint32_t extra_size = count % thread_count;

//         uint32_t index = 0;
//         uint32_t c_thread_size;

//         for (int i = 0; i < thread_count; i++) {
//             c_thread_size = thread_size + (bool)(extra_size);

//             thread_data[i].index = index;
//             thread_data[i].count = c_thread_size;

//             if (extra_size) extra_size--;

//             index += c_thread_size;
//         }

//         thread_launcher.release(thread_count);

//         for (int i = 0; i < thread_count; i++) {
//             thread_blocker.acquire();
//         }
//     }
// }

// void fun::Particler::UpdateRange(uint32_t index, uint32_t size) {
//     const float delta_time = fun::time::delta_time();

//     uint32_t vertex_index = 0;
//     uint32_t next_vertex_index = (index - 1) * 4;

//     float x;
//     float y;

//     for (auto particle = particles + index; particle != particles + index + size; particle++) {
//         vertex_index = (next_vertex_index += 4);

//         if (particle->lifetime <= 0) continue;

//         particle->lifetime -= delta_time;

//         particle->position += vec2_t(sin(particle->direction_angle), cos(particle->direction_angle)) * particle->velocity * delta_time;

//         particle->velocity += particle->velocity_step * delta_time;

//         {
//             x = sin(particle->body_angle) * particle->body_radius;
//             y = cos(particle->body_angle) * particle->body_radius;

//             vertices[vertex_index].position.x = particle->position.x + x;
//             vertices[vertex_index].position.y = -(particle->position.y + y);

//             vertices[vertex_index].color = sf::Color::Black; // ! check if color step is > 0

//             vertex_index += 1;

//             vertices[vertex_index].position.x = particle->position.x + y;
//             vertices[vertex_index].position.y = -(particle->position.y - x);

//             vertices[vertex_index].color = sf::Color::Black;

//             vertex_index += 1;

//             vertices[vertex_index].position.x = particle->position.x - x;
//             vertices[vertex_index].position.y = -(particle->position.y - y);

//             vertices[vertex_index].color = sf::Color::Black;

//             vertex_index += 1;

//             vertices[vertex_index].position.x = particle->position.x - y;
//             vertices[vertex_index].position.y = -(particle->position.y + x);

//             vertices[vertex_index].color = sf::Color::Black;

//             vertex_index += 1;
//         }
//     }
// }

// void fun::Particler::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
//     if (!count) return;

//     render_target.draw(&vertices[0], count * 4, sf::Quads, render_states);
// }
