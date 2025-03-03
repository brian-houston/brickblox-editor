#ifndef BRICK_VISUAL_CONTROLLER_H
#define BRICK_VISUAL_CONTROLLER_H

#include "scene/main/node.h"
#include "modules/brick_visualizer/brick_visualizer.h"

struct BrickVisualData {
    int visualizer_id = -1;
    int visualizer_type = 0;
    uint32_t color = 0;
    uint32_t surfaces;
};

class BrickVisualController : public Node {
    GDCLASS(BrickVisualController, Node);
public:
    static BrickVisualController* singleton;
    static BrickVisualController* get_singleton() {
        return singleton;
    }
    BrickVisualController();
    BrickVisualData add_brick(Transform3D p_transform);
    void remove_brick(BrickVisualData bvd);
    void set_brick_transform(BrickVisualData bvd, Transform3D p_transform);
private:
    BrickVisualizer* visualizer;
};
#endif