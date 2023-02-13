#include "../../globals.h"
#include "../../ecs/ecs.h"
#include "../../vec2.h"
#include "../sprite.h"
#include "../window/window.h"

namespace fun::gui {
    ecs::entity_t create_box();
    void free_box(ecs::entity_t);

    ecs::entity_t create_canvas(vec2f_t);
    void free_canvas(ecs::entity_t);

    ecs::entity_t create_image();
    void free_image(ecs::entity_t);

    void render(ecs::entity_t, render::window_t&);
}
