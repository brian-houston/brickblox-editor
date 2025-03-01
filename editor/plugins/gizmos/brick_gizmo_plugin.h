#ifndef BRICK_GIZMO_PLUGIN_H
#define BRICK_GIZMO_PLUGIN_H

#include "editor/plugins/node_3d_editor_gizmos.h"

class BrickGizmoPlugin : public EditorNode3DGizmoPlugin {
	GDCLASS(BrickGizmoPlugin, EditorNode3DGizmoPlugin);

public:
	bool has_gizmo(Node3D *p_spatial) override;
	String get_gizmo_name() const override;
	int get_priority() const override;
	bool can_be_hidden() const override;
	void redraw(EditorNode3DGizmo *p_gizmo) override;

	BrickGizmoPlugin();
};

#endif
