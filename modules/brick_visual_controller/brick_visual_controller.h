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
    int32_t visualizer_type;
    int32_t visualizer_slot;
};

class BrickVisualController : public Node {
    GDCLASS(BrickVisualController, Node);
public:
    static BrickVisualController* singleton;
    static BrickVisualController* get_singleton() {
        return singleton;
    }
    BrickVisualController();
    BrickVisualMetadata add_brick(const Transform3D& p_transform, const BrickVisualData p_bvd);
    BrickVisualMetadata remove_brick(BrickVisualMetadata p_meta);
    BrickVisualMetadata set_brick_transform(BrickVisualMetadata p_meta, const Transform3D& p_transform);
    BrickVisualMetadata set_brick_custom_data(BrickVisualMetadata p_meta, BrickVisualData p_bvd);
private:
    BrickVisualizer* visualizer;
};
#endif