#include "brick_visual_controller.h"

BrickVisualController* BrickVisualController::singleton = nullptr;

BrickVisualData BrickVisualController::add_brick(Transform3D p_transform) {
    BrickVisualData bvd;
    bvd.visualizer_id = visualizer->add_instance(p_transform);
    return bvd;
}

void BrickVisualController::remove_brick(BrickVisualData bvd) {
    if (bvd.visualizer_id > -1) {
        visualizer->remove_instance(bvd.visualizer_id);
    }
}

void BrickVisualController::set_brick_transform(BrickVisualData bvd, Transform3D p_transform) {
    if (bvd.visualizer_id > -1) {
        visualizer->set_instance_transform(bvd.visualizer_id, p_transform);
    }
}

BrickVisualController::BrickVisualController() {
    set_name("BrickVisualController");
    if (singleton == nullptr) {
        singleton = this;

        visualizer = memnew(BrickVisualizer);
        visualizer->setup(65536);
        add_child(visualizer);
    }
}