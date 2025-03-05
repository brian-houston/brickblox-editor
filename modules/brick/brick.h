#ifndef BRICK__H
#define BRICK__H

#include "modules/brick_visual_controller/brick_visual_controller.h"
#include "scene/3d/node_3d.h"
#include "scene/resources/3d/box_shape_3d.h"

class Brick : public Node3D {
    GDCLASS(Brick, Node3D);
public:
    Brick();
    ~Brick();
    void _notification(int p_what);
    Color get_color() const;
    void set_color(Color p_color);

    float get_alpha() const;
    void set_alpha(float p_alpha);

    bool get_anchored() const;
    void set_anchored(bool p_anchored);
    
    void _body_state_changed(PhysicsDirectBodyState3D *p_state);
    static void _bind_methods();
    static BoxShape3D* box_shape;
private:
    BrickVisualData bvd;
    BrickVisualMetadata brick_meta;
    RID physics_id;
    bool anchored;
};
#endif