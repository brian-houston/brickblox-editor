#include "brick_gizmo_plugin.h"

#include "editor/plugins/node_3d_editor_plugin.h"
#include "scene/resources/3d/primitive_meshes.h"
#include "modules/brick/brick.h"

BrickGizmoPlugin::BrickGizmoPlugin() {
}

bool BrickGizmoPlugin::has_gizmo(Node3D *p_spatial) {
	return Object::cast_to<Brick>(p_spatial) != nullptr;
}

String BrickGizmoPlugin::get_gizmo_name() const {
	return "Brick";
}

int BrickGizmoPlugin::get_priority() const {
	return -1;
}

bool BrickGizmoPlugin::can_be_hidden() const {
	return false;
}

void BrickGizmoPlugin::redraw(EditorNode3DGizmo *p_gizmo) {
	p_gizmo->clear();

	Ref<TriangleMesh> tm;
    Ref<BoxMesh> box;
    box.instantiate();
    tm = box->generate_triangle_mesh();

	if (tm.is_valid()) {
		p_gizmo->add_collision_triangles(tm);
	}
}
