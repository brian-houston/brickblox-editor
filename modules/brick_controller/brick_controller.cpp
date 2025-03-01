#include "brick_controller.h"

BrickController* BrickController::singleton = nullptr;

int BrickController::add_brick(Transform3D p_transform) {
    BrickData bd;
    bd.visualizer_id = visualizer->add_instance(p_transform);
    lookup[count] = bd;
    return count++;
}

void BrickController::remove_brick(int p_id) {
    BrickData bd = lookup[p_id];
    if (bd.visualizer_id > -1) {
        visualizer->remove_instance(bd.visualizer_id);
    }
    lookup.erase(p_id);
}

void BrickController::set_brick_transform(int p_id, Transform3D p_transform) {
    BrickData bd = lookup[p_id];
    visualizer->set_instance_transform(bd.visualizer_id, p_transform);
}

void BrickController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add_brick", "transform"), &BrickController::add_brick);
    ClassDB::bind_method(D_METHOD("remove_brick", "id"), &BrickController::remove_brick);
    ClassDB::bind_method(D_METHOD("set_brick_transform", "id", "transform"), &BrickController::set_brick_transform);
}

BrickController::BrickController() {
    if (singleton == nullptr) {
        singleton = this;

        visualizer = memnew(BrickVisualizer);
        visualizer->setup(65536);
        add_child(visualizer);
    }
}