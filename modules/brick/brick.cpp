#include "brick.h"

BoxShape3D* Brick::box_shape = nullptr;

void Brick::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            brick_meta = BrickVisualController::get_singleton()->add_brick(get_global_transform(), bvd);
            if (brick_meta.visualizer_slot == -1) {
                queue_free();
            }
        } break;
        case NOTIFICATION_EXIT_TREE: {
            brick_meta = BrickVisualController::get_singleton()->remove_brick(brick_meta);
        } break;
        case NOTIFICATION_TRANSFORM_CHANGED: {
            if (anchored) {
                PhysicsServer3D::get_singleton()->body_set_state(physics_id, PhysicsServer3D::BODY_STATE_TRANSFORM, get_global_transform());
            } else {
                reset_position = true;
            }
            
            brick_meta = BrickVisualController::get_singleton()->set_brick_transform(brick_meta, get_global_transform());
        } break;
        case NOTIFICATION_ENTER_WORLD: {
            PhysicsServer3D::get_singleton()->body_set_state(physics_id, PhysicsServer3D::BODY_STATE_TRANSFORM, get_global_transform());
            Ref<World3D> world_ref = get_world_3d();
            RID space = world_ref->get_space();
            PhysicsServer3D::get_singleton()->body_set_space(physics_id, space);
        } break;
        case NOTIFICATION_EXIT_WORLD: {
            PhysicsServer3D::get_singleton()->body_set_space(physics_id, RID());
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
    Transform3D transform = is_inside_tree() ? get_global_transform() : Transform3D();
    brick_meta = BrickVisualController::get_singleton()->set_brick_custom_data(brick_meta, transform, bvd);
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
    Transform3D transform = is_inside_tree() ? get_global_transform() : Transform3D();
    brick_meta = BrickVisualController::get_singleton()->set_brick_custom_data(brick_meta, transform, bvd);
}

bool Brick::get_anchored() const {
    return anchored;
}

void Brick::set_anchored(bool p_anchored) {
    if (p_anchored == anchored) {
        return;
    }
    anchored = p_anchored;

    if (anchored) {
        PhysicsServer3D::get_singleton()->body_set_mode(physics_id, PhysicsServer3D::BODY_MODE_STATIC);
    } else {
        PhysicsServer3D::get_singleton()->body_set_mode(physics_id, PhysicsServer3D::BODY_MODE_RIGID);
    }
}

void Brick::_body_state_changed(PhysicsDirectBodyState3D *p_state) {
    set_ignore_transform_notification(true);
    if (reset_position) {
        PhysicsServer3D::get_singleton()->body_set_state(physics_id, PhysicsServer3D::BODY_STATE_TRANSFORM, get_global_transform());
        reset_position = false;
    } else {
        set_global_transform(p_state->get_transform());
        brick_meta = BrickVisualController::get_singleton()->set_brick_transform(brick_meta, p_state->get_transform());
    }
    set_ignore_transform_notification(false);
}


void Brick::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_color", "color"), &Brick::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &Brick::get_color);
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color", PROPERTY_HINT_COLOR_NO_ALPHA), "set_color", "get_color");

    ClassDB::bind_method(D_METHOD("set_alpha", "alpha"), &Brick::set_alpha);
	ClassDB::bind_method(D_METHOD("get_alpha"), &Brick::get_alpha);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "alpha", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_alpha", "get_alpha");

    ClassDB::bind_method(D_METHOD("set_anchored", "anchored"), &Brick::set_anchored);
	ClassDB::bind_method(D_METHOD("get_anchored"), &Brick::get_anchored);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "anchored"), "set_anchored", "get_anchored");
}

Brick::Brick() {
    set_notify_local_transform(true);
    set_notify_transform(true);
    set_as_top_level(true);
    set_alpha(1.0);
    set_color(Color(0.5, 0.5, 0.5, 1.0));
    

    if (box_shape == nullptr) {
        box_shape = memnew(BoxShape3D);
    }

    physics_id = PhysicsServer3D::get_singleton()->body_create();
    PhysicsServer3D::get_singleton()->body_add_shape(physics_id, box_shape->get_rid());
    PhysicsServer3D::get_singleton()->body_set_mode(physics_id, PhysicsServer3D::BODY_MODE_STATIC);
    PhysicsServer3D::get_singleton()->body_set_state_sync_callback(physics_id, callable_mp(this, &Brick::_body_state_changed));
}

Brick::~Brick() {
    PhysicsServer3D::get_singleton()->free(physics_id);
}