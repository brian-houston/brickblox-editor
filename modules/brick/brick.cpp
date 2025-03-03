#include "brick.h"

void Brick::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            bvd = BrickVisualController::get_singleton()->add_brick(get_global_transform());
            if (bvd.visualizer_id == -1) {
                queue_free();
            }
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

Color Brick::get_color() const {
    uint32_t c = bvd.color;
    int64_t a = 0xff;
    c >>= 8;
    int64_t b = c & 0xff;
    c >>= 8;
    int64_t g = c & 0xff;
    c >>= 8;
    int64_t r = c & 0xff;
    return Color::from_rgba8(r, g, b, a);
}

void Brick::set_color(Color p_color) {
    bvd.color = (p_color.to_rgba32() & (~0xff)) | (bvd.color & 0xff);
}

float Brick::get_alpha() const {
    return (bvd.color & 0xff) / 255.0;
}

void Brick::set_alpha(float p_alpha) {
    uint32_t a = Math::round(p_alpha * 255.0);
    if (a > 0xff) {
        a = 0xff;
    }
    bvd.color = (bvd.color & (~0xff)) | a;
}

void Brick::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_color", "color"), &Brick::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &Brick::get_color);
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color", PROPERTY_HINT_COLOR_NO_ALPHA), "set_color", "get_color");

    ClassDB::bind_method(D_METHOD("set_alpha", "alpha"), &Brick::set_alpha);
	ClassDB::bind_method(D_METHOD("get_alpha"), &Brick::get_alpha);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "alpha", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_alpha", "get_alpha");
}

Brick::Brick() {
    set_notify_local_transform(true);
    set_notify_transform(true);
    set_as_top_level(true);
}