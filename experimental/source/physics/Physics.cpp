#include "physics/Physics.h"

static b2World world = b2World(b2Vec2(0, 0));
static float timestep = .0166f;
static float delta_time_reminder = 0;
static uint8_t velocity_iterations = 10;
static uint8_t position_iterations = 8;

void fun::physics::set_gravity(b2Vec2 gravity) {
    world.SetGravity(gravity);
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