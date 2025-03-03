#ifndef BRICK__H
#define BRICK__H

#include "modules/brick_visual_controller/brick_visual_controller.h"
#include "scene/3d/node_3d.h"

class Brick : public Node3D {
    GDCLASS(Brick, Node3D);
public:
    Brick();
    void _notification(int p_what);
private:
    BrickVisualData bvd;
};
#endif