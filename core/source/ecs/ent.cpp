#include "ecs/ent.h"

auto fun::ent::create() -> ecs::entity_t {
    ecs::entity_t entity = ecs::new_entity();

    ecs::add_component <hierarchy_t> (entity);

    return entity;
}

auto fun::ent::destroy(ecs::entity_t entity) -> void {
    ASSERT_VERBAL(entity != ecs::nullentity, "Entity can not be null");

    auto& hierarchy = ecs::get_component <hierarchy_t> (entity);
    
    if (hierarchy.parent != ecs::nullentity) remove_parent(entity);

    if (hierarchy.child_count > 0) {
        auto child = hierarchy.child;

        for (uint32_t i = 0; i < hierarchy.child_count; i++) {
            auto& child_hierarchy = ecs::get_component <hierarchy_t> (child);

            child = child_hierarchy.next_sibling;
            
            child_hierarchy.parent = ecs::nullentity;
            child_hierarchy.next_sibling = ecs::nullentity;
            child_hierarchy.prev_sibling = ecs::nullentity;
        }
    }

    ecs::remove_component <hierarchy_t> (entity);
    ecs::destroy_entity(entity);
}

auto fun::ent::add_child(ecs::entity_t parent, ecs::entity_t child) -> void {
    ASSERT_VERBAL(parent != ecs::nullentity, "Parent entity can not be null");
    ASSERT_VERBAL(child != ecs::nullentity, "Child entity can not be null");
    ASSERT_VERBAL(parent != child, "Entity can not be its own parent");

    auto& parent_info = ecs::get_component <hierarchy_t> (parent);
    auto& child_info = ecs::get_component <hierarchy_t> (child);

    ASSERT_VERBAL(child_info.parent == ecs::nullentity, "Entity already has a parent");

    parent_info.child_count++;
    child_info.parent = parent;

    if (parent_info.child == ecs::nullentity) {
        parent_info.child = child;
        child_info.next_sibling = child;
        child_info.prev_sibling = child;
    } else {
        auto& prev_info = ecs::get_component <hierarchy_t> (parent_info.child);
        auto& next_info = ecs::get_component <hierarchy_t> (prev_info.next_sibling);

        child_info.prev_sibling = parent_info.child;
        child_info.next_sibling = prev_info.next_sibling;

        prev_info.next_sibling = child;
        next_info.prev_sibling = child;
    }
}

void fun::ent::remove_parent(ecs::entity_t child) {
    ASSERT_VERBAL(child != ecs::nullentity, "Child entity can not be null");

    auto& child_info = ecs::get_component <hierarchy_t> (child);

    ASSERT_VERBAL(child_info.parent != ecs::nullentity, "Entity does not have a parent");

    auto& parent_info = ecs::get_component <hierarchy_t> (child_info.parent);
    parent_info.child_count--;

    if (parent_info.child == child) {
        if (parent_info.child_count == 0) {
            parent_info.child = ecs::nullentity;
        } else {
            parent_info.child = child_info.next_sibling;
        }
    }

    {
        auto& next_info = ecs::get_component <hierarchy_t> (child_info.next_sibling);
        auto& prev_info = ecs::get_component <hierarchy_t> (child_info.prev_sibling);

        next_info.prev_sibling = child_info.prev_sibling;
        prev_info.next_sibling = child_info.next_sibling;
    }

    child_info.parent = ecs::nullentity;
    child_info.next_sibling = ecs::nullentity;
    child_info.prev_sibling = ecs::nullentity;
}

fun::ent::children_iterator_t::children_iterator_t(ecs::entity_t parent, bool recursive) : recursive(recursive) {
    push(parent);
}

auto fun::ent::children_iterator_t::valid() const -> bool {
    return !queue.empty();
}

auto fun::ent::children_iterator_t::next() -> void {
    auto entity = queue.front();
    queue.pop();

    if (recursive) {
        push(entity);
    }
}

auto fun::ent::children_iterator_t::get() const -> ecs::entity_t {
    return queue.front();
}

auto fun::ent::children_iterator_t::push(ecs::entity_t entity) -> void {
    auto& hierarchy = ecs::get_component <hierarchy_t> (entity);
    auto child = hierarchy.child;

    for (uint32_t i = 0; i < hierarchy.child_count; i++) {
        queue.emplace(child);

        auto& child_hierarchy = ecs::get_component <hierarchy_t> (child);
        child = child_hierarchy.next_sibling;
    }
}
