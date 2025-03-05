#include "brick_visual_controller.h"
#include "brick_shaders.h"

BrickVisualController* BrickVisualController::singleton = nullptr;

BrickVisualMetadata BrickVisualController::add_brick(const Transform3D& p_transform, BrickVisualData p_bvd) {
    BrickVisualMetadata meta;
    const Color custom_data = *reinterpret_cast<Color*>(&p_bvd);
    meta.visualizer_slot = visualizer->add_instance(p_transform, custom_data);
    return meta;
}

BrickVisualMetadata BrickVisualController::remove_brick(BrickVisualMetadata p_meta) {
    if (p_meta.visualizer_slot > -1) {
        visualizer->remove_instance(p_meta.visualizer_slot);
        p_meta.visualizer_slot = -1;
    }

    return p_meta;
}

BrickVisualMetadata BrickVisualController::set_brick_transform(BrickVisualMetadata p_meta, const Transform3D& p_transform) {
    if (p_meta.visualizer_slot > -1) {
        visualizer->set_instance_transform(p_meta.visualizer_slot, p_transform);
    }

    return p_meta;
}

BrickVisualMetadata BrickVisualController::set_brick_custom_data(BrickVisualMetadata p_meta, BrickVisualData p_bvd) {
    if (p_meta.visualizer_slot > -1) {
        const Color custom_data = *reinterpret_cast<Color*>(&p_bvd);
        visualizer->set_instance_custom_data(p_meta.visualizer_slot, custom_data);
    }

    return p_meta;
}

BrickVisualController::BrickVisualController() {
    set_name("BrickVisualController");
    if (singleton == nullptr) {
        singleton = this;

        visualizer = memnew(BrickVisualizer);
        visualizer->setup(65536);
        visualizer->set_shader_code(get_brick_shader_code());
        add_child(visualizer);
    }
}