#ifndef BRICK__H
#define BRICK__H

#include "scene/3d/multimesh_instance_3d.h"

class Brick : public Node3D {
    GDCLASS(Brick, Node3D);
public:
    Brick();
    void _notification(int p_what);
private:
    int id;
};
#endif