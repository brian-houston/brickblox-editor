#include "modules/brick_controller/brick_controller.h"
#include "brick.h"

void Brick::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            id = BrickController::get_singleton()->add_brick(get_global_transform());
        } break;
        case NOTIFICATION_EXIT_TREE: {
            BrickController::get_singleton()->remove_brick(id);
            id = -1;
        } break;
        case NOTIFICATION_TRANSFORM_CHANGED: {
            BrickController::get_singleton()->set_brick_transform(id, get_global_transform());
        }
    }
}

Brick::Brick() {
#ifdef TOOLS_ENABLED
    if (Engine::get_singleton()->is_editor_hint()) {
        set_notify_local_transform(true);
        set_notify_transform(true);
    }
#endif
}