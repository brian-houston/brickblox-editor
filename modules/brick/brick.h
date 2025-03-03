#ifndef BRICK__H
#define BRICK__H

#include "modules/brick_visual_controller/brick_visual_controller.h"
#include "scene/3d/node_3d.h"

class Brick : public Node3D {
    GDCLASS(Brick, Node3D);
public:
    Brick();
    void _notification(int p_what);
    Color get_color() const;
    void set_color(Color p_color);

    float get_alpha() const;
    void set_alpha(float p_alpha);
    static void _bind_methods();
private:
    BrickVisualData bvd;
};
#endif