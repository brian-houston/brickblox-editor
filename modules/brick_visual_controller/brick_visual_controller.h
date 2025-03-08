#ifndef BRICK_VISUAL_CONTROLLER_H
#define BRICK_VISUAL_CONTROLLER_H

#include "scene/main/node.h"
#include "modules/brick_visualizer/brick_visualizer.h"

struct BrickVisualData {
    uint32_t color = 0;
    uint32_t surfaces;
    uint32_t space1;
    uint32_t space2;
};

struct BrickVisualMetadata {
    int32_t visualizer_type = 0;
    int32_t visualizer_slot = -1;
};

class BrickVisualController : public Node {
    GDCLASS(BrickVisualController, Node);
public:
    static BrickVisualController* singleton;
    static BrickVisualController* get_singleton() {
        return singleton;
    }
    static void _bind_methods();
    BrickVisualController();
    BrickVisualMetadata add_brick(const Transform3D& p_transform, BrickVisualData p_bvd);
    BrickVisualMetadata remove_brick(BrickVisualMetadata p_meta);
    BrickVisualMetadata set_brick_transform(BrickVisualMetadata p_meta, const Transform3D& p_transform);
    BrickVisualMetadata set_brick_custom_data(BrickVisualMetadata p_meta, const Transform3D& p_transform, BrickVisualData p_bvd);
    void set_visualizer_material(int32_t visualizer_type, Ref<Material> mat);
    int get_visualizer_type(BrickVisualData p_bvd);
private:
    BrickVisualizer* visualizers[4];
};
#endif