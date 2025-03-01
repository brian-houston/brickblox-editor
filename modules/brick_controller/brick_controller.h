#ifndef BRICK_CONTROLLER_H
#define BRICK_CONTROLLER_H

#include "scene/main/node.h"
#include "modules/brick_visualizer/brick_visualizer.h"

struct BrickData {
    int visualizer_id = -1;
    int physics_id = -1;
};

class BrickController : public Node {
    GDCLASS(BrickController, Node);
public:
    static BrickController* singleton;
    static BrickController* get_singleton() {
        return singleton;
    }
    BrickController();
    int add_brick(Transform3D p_transform);
    void remove_brick(int p_id);
    void set_brick_transform(int p_id, Transform3D p_transform);
    static void _bind_methods();
private:
    int count;
    BrickVisualizer* visualizer;
    HashMap<int, BrickData> lookup;
};
#endif