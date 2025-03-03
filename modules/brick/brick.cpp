#include "brick.h"

void Brick::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            bvd = BrickVisualController::get_singleton()->add_brick(get_global_transform());
        } break;
        case NOTIFICATION_EXIT_TREE: {
            BrickVisualController::get_singleton()->remove_brick(bvd);
            bvd.visualizer_id = -1;
        } break;
        case NOTIFICATION_TRANSFORM_CHANGED: {
            BrickVisualController::get_singleton()->set_brick_transform(bvd, get_global_transform());
        }
    }
}

Brick::Brick() {
    set_notify_local_transform(true);
    set_notify_transform(true);
    set_as_top_level(true);
}