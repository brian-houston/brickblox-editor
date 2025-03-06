#include "brick_visual_controller.h"
#include "brick_shaders.h"

BrickVisualController* BrickVisualController::singleton = nullptr;

BrickVisualMetadata BrickVisualController::add_brick(const Transform3D& p_transform, BrickVisualData p_bvd) {
    BrickVisualMetadata meta;
    const Color custom_data = *reinterpret_cast<Color*>(&p_bvd);
    meta.visualizer_type = get_visualizer_type(p_bvd);
    meta.visualizer_slot = visualizers[meta.visualizer_type]->add_instance(p_transform, custom_data);
    return meta;
}

BrickVisualMetadata BrickVisualController::remove_brick(BrickVisualMetadata p_meta) {
    if (p_meta.visualizer_slot > -1) {
        visualizers[p_meta.visualizer_type]->remove_instance(p_meta.visualizer_slot);
        p_meta.visualizer_slot = -1;
    }

    return p_meta;
}

BrickVisualMetadata BrickVisualController::set_brick_transform(BrickVisualMetadata p_meta, const Transform3D& p_transform) {
    if (p_meta.visualizer_slot > -1) {
        visualizers[p_meta.visualizer_type]->set_instance_transform(p_meta.visualizer_slot, p_transform);
    }

    return p_meta;
}

BrickVisualMetadata BrickVisualController::set_brick_custom_data(BrickVisualMetadata p_meta, const Transform3D& p_transform, BrickVisualData p_bvd) {
    if (p_meta.visualizer_slot > -1) {
        const Color custom_data = *reinterpret_cast<Color*>(&p_bvd);
        int new_type = get_visualizer_type(p_bvd);
        if (new_type == p_meta.visualizer_type) {
            visualizers[p_meta.visualizer_type]->set_instance_custom_data(p_meta.visualizer_slot, custom_data);
        } else {
            visualizers[p_meta.visualizer_type]->remove_instance(p_meta.visualizer_slot);
            p_meta.visualizer_type = new_type;
            p_meta.visualizer_slot = visualizers[new_type]->add_instance(p_transform, custom_data);
        }
    }

    return p_meta;
}

int BrickVisualController::get_visualizer_type(BrickVisualData p_bvd) {
    uint32_t alpha = p_bvd.color & 0xff;
    if (alpha < 0xff) {
        return 1;
    }
    return 0;
}

BrickVisualController::BrickVisualController() {
    set_name("BrickVisualController");
    if (singleton == nullptr) {
        singleton = this;

        visualizers[0] = memnew(BrickVisualizer);
        visualizers[0]->setup(65536);
        visualizers[0]->set_shader_code(get_brick_shader_code());
        add_child(visualizers[0]);

        visualizers[1] = memnew(BrickVisualizer);
        visualizers[1]->setup(16384);
        visualizers[1]->set_shader_code(get_brick_alpha_shader_code());
        add_child(visualizers[1]);
    }
}