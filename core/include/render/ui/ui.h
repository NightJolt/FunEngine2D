#include "../../globals.h"
#include "../../ecs/ecs.h"
#include "../../vec2.h"
#include "../sprite.h"

namespace fun::gui {
    struct transform_t {
        vec2f_t abs_pos;
        vec2f_t rel_pos;

        vec2f_t abs_size;
        vec2f_t rel_size;
    };

    CREATE_TYPE_FROM_NONPRIMITIVE(image_t, render::sprite_t)

    ecs::entity_t create_box();
    void set_transform(ecs::entity_t, transform_t);
    void set_layer(ecs::entity_t, layer_t);
    void free_box(ecs::entity_t);

    ecs::entity_t create_canvas();
    void free_canvas(ecs::entity_t);

    ecs::entity_t create_image();
    void free_image(ecs::entity_t);

    ecs::entity_t create_button();
    void free_button(ecs::entity_t);

    void invalidate(ecs::entity_t);
    void render(ecs::entity_t, render::window_t&);
}
