#ifndef BRICK_VISUALIZER_H
#define BRICK_VISUALIZER_H

#include "scene/3d/multimesh_instance_3d.h"


class BrickVisualizer : public MultiMeshInstance3D {
    GDCLASS(BrickVisualizer, MultiMeshInstance3D);
public:
    BrickVisualizer();
    void setup(int p_max_instances);
    void set_material(Ref<Material> mat);
    int add_instance(const Transform3D& p_transform, Color p_color);
    void remove_instance(int p_slot);
    void set_instance_transform(int p_slot, const Transform3D& p_transform);
    void set_instance_custom_data(int p_slot, Color p_color);
private:
    int max_instances;
    int current_instances;
    LocalVector<int> available_slots;
};
#endif