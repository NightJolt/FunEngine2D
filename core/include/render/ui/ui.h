#include "../../globals.h"
#include "../../ecs/ecs.h"
#include "../../vec2.h"
#include "../sprite.h"
#include "../../interact/interactable.h"

namespace fun::gui {
    struct transform_t {
        vec2f_t abs_pos;
        vec2f_t rel_pos;

        vec2f_t abs_size;
        vec2f_t rel_size;
    };

    CREATE_TYPE_FROM_NONPRIMITIVE(image_t, render::sprite_t)

    ecs::entity_t create_box();
    void free_box(ecs::entity_t);

    ecs::entity_t create_canvas();
    void free_canvas(ecs::entity_t);

    ecs::entity_t create_image();
    void free_image(ecs::entity_t);

    ecs::entity_t create_button(const action_fun_t&);
    void free_button(ecs::entity_t);

    void set_transform(ecs::entity_t, transform_t);
    void set_layer(ecs::entity_t, layer_t);

    void set_dirty(ecs::entity_t);
    void force_repaint(render::window_t&);
    void render(ecs::entity_t, render::window_t&);
}
