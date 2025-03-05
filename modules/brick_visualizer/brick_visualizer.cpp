#include "brick_visualizer.h"

#include "scene/resources/3d/primitive_meshes.h"
#include "scene/resources/material.h"
#include "scene/resources/shader.h"

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
    multimesh->set_use_colors(false);
    multimesh->set_use_custom_data(true);
    multimesh->set_mesh(box);
    multimesh->set_visible_instance_count(0);
    multimesh->set_instance_count(max_instances);
    multimesh->set_custom_aabb(AABB(Vector3(-100000.0, -100000.0, -100000.0), Vector3(200000.0, 200000.0, 200000.0)));

    set_multimesh(multimesh);
}

void BrickVisualizer::set_shader_code(const String& shader_code) {
    if (!get_multimesh().is_valid()) {
        return;
    }

    Ref<Shader> shader;
    shader.instantiate();
    shader->set_code(shader_code);

    Ref<ShaderMaterial> material;
    material.instantiate();
    material->set_shader(shader);

    get_multimesh()->get_mesh()->surface_set_material(0, material);
}


int BrickVisualizer::add_instance(const Transform3D& p_transform) {
    int slot = -1;
    Ref<MultiMesh> multimesh = get_multimesh();

    if (!available_slots.is_empty()) {
        slot = available_slots[available_slots.size() - 1];
        available_slots.remove_at(available_slots.size() - 1);
    } else if (current_instances < max_instances) {
        slot = current_instances;
        multimesh->set_visible_instance_count(++current_instances);
    }

    if (slot > -1) {
        multimesh->set_instance_transform(slot, p_transform);
    }

    return slot;
}

void BrickVisualizer::remove_instance(int p_slot) {
    if (p_slot >= max_instances) {
        return;
    }

    Transform3D transform = Transform3D();
    transform.basis[0] = Vector3(0.0, 0.0, 0.0);
    transform.basis[1] = Vector3(0.0, 0.0, 0.0);
    transform.basis[2] = Vector3(0.0, 0.0, 0.0);

    set_instance_transform(p_slot, transform);

    available_slots.push_back(p_slot);
}

void BrickVisualizer::set_instance_transform(int p_slot, const Transform3D& p_transform) {
    Ref<MultiMesh> multimesh = get_multimesh();
    multimesh->set_instance_transform(p_slot, p_transform);
}

void BrickVisualizer::set_instance_custom_data(int p_slot, Color p_color) {
    Ref<MultiMesh> multimesh = get_multimesh();
    multimesh->set_instance_custom_data(p_slot, p_color);
}

BrickVisualizer::BrickVisualizer() {
    max_instances = 0;
    current_instances = 0;
}