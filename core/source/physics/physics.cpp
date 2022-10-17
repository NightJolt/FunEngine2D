#include "physics/physics.h"
#include "_time.h"

static float simulation_scale = 1;
static b2World world = b2World(b2Vec2(0, 0));
static float timestep = .0166f;
static float delta_time_reminder = 0;
static uint8_t velocity_iterations = 10;
static uint8_t position_iterations = 8;


void fun::physics::set_simulation_scale(float s) {
    simulation_scale = s;
}

float fun::physics::get_simulation_scale() {
    return simulation_scale;
}

void fun::physics::set_gravity(vec2f_t gravity) {
    world.SetGravity(gravity.to_b2());
}

void set_timestep(float ts) {
    timestep = ts;
}

void set_velocity_iterations(uint8_t vi) {
    velocity_iterations = vi;
}

void set_position_iterations(uint8_t pi) {
    position_iterations = pi;
}

void fun::physics::simulate() {
    float delta_time = fun::time::delta_time();
    
    delta_time_reminder += delta_time;

    while (delta_time_reminder > timestep) {
        delta_time_reminder -= timestep;

        world.Step(timestep, velocity_iterations, position_iterations);
    }

    world.ClearForces();
}

b2Body* fun::physics::create_body(const b2BodyDef& body_def) {
    return world.CreateBody(&body_def);
}

void fun::physics::destroy_body(b2Body* body) {
    world.DestroyBody(body);
}
