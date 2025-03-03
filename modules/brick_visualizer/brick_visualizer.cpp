#include "brick_visualizer.h"

#include "scene/resources/3d/primitive_meshes.h"

void BrickVisualizer::setup(int p_max_instances) {
    if (max_instances > 0) {
        return;
    }

    current_instances = 0;
    max_instances = p_max_instances;
    Ref<BoxMesh> box;
    box.instantiate();

    Ref<MultiMesh> multimesh;
    multimesh.instantiate();
    multimesh->set_transform_format(MultiMesh::TransformFormat::TRANSFORM_3D);
    multimesh->set_mesh(box);
    multimesh->set_visible_instance_count(0);
    multimesh->set_instance_count(max_instances);
    multimesh->set_custom_aabb(AABB(Vector3(-100000.0, -100000.0, -100000.0), Vector3(200000.0, 200000.0, 200000.0)));

    set_multimesh(multimesh);
}

int BrickVisualizer::add_instance(Transform3D p_transform) {
    int id = -1;
    Ref<MultiMesh> multimesh = get_multimesh();

    if (!available_slots.is_empty()) {
        id = available_slots[available_slots.size() - 1];
        available_slots.remove_at(available_slots.size() - 1);
    } else if (current_instances < max_instances) {
        id = current_instances;
        multimesh->set_visible_instance_count(++current_instances);
    }

    if (id > -1) {
        multimesh->set_instance_transform(id, p_transform);
    }

    return id;
}

void BrickVisualizer::remove_instance(int p_id) {
    if (p_id >= max_instances) {
        return;
    }

    Transform3D transform;
    transform.basis[0] = Vector3(0.0, 0.0, 0.0);
    transform.basis[1] = Vector3(0.0, 0.0, 0.0);
    transform.basis[2] = Vector3(0.0, 0.0, 0.0);

    set_instance_transform(p_id, transform);

    available_slots.push_back(p_id);
}

void BrickVisualizer::set_instance_transform(int p_id, Transform3D p_transform) {
    Ref<MultiMesh> multimesh = get_multimesh();
    multimesh->set_instance_transform(p_id, p_transform);
}

BrickVisualizer::BrickVisualizer() {
    max_instances = 0;
    current_instances = 0;
}