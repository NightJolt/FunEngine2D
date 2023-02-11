#pragma once

#include "../globals.h"
#include "ecs.h"

namespace fun::ent {
    struct hierarchy_t {
        ecs::entity_t parent { ecs::nullentity };
        ecs::entity_t next_sibling { ecs::nullentity };
        ecs::entity_t prev_sibling { ecs::nullentity };
        ecs::entity_t child { ecs::nullentity };
        uint32_t child_count = 0;
    };

    ecs::entity_t create();
    void destroy(ecs::entity_t);

    void add_child(ecs::entity_t, ecs::entity_t);
    void remove_parent(ecs::entity_t);

    class children_iterator_t {
    public:
        children_iterator_t(ecs::entity_t, bool = false);
        
        bool valid() const;
        void next();
        ecs::entity_t get() const;

    private:
        void push(ecs::entity_t);

        bool recursive;
        std::queue <ecs::entity_t> queue;
    };
}