#include "physics/Physics.h"

b2Vec2 fun::physics::gravity = b2Vec2(0, 0);
b2World fun::physics::world = b2World(gravity);

void fun::physics::set_gravity(b2Vec2 g) {
    gravity = g;
}

void fun::physics::simulate() {

}