#ifndef BRICK_VISUALIZER_H
#define BRICK_VISUALIZER_H

#include "scene/3d/multimesh_instance_3d.h"

class BrickVisualizer : public MultiMeshInstance3D {
    GDCLASS(BrickVisualizer, MultiMeshInstance3D);
public:
    BrickVisualizer();
    void setup(int p_max_instances);
    int add_instance(Transform3D p_transform);
    void remove_instance(int p_id);
    void set_instance_transform(int p_id, Transform3D p_transform);
private:
    int max_instances;
    int current_instances;
    LocalVector<int> available_slots;
};
#endif