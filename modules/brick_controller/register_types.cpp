#include "register_types.h"

#include "core/object/class_db.h"
#include "scene/main/window.h"
#include "brick_controller.h"



void initialize_brick_controller_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}
	BrickController* bc = memnew(BrickController);
	//SceneTree::get_singleton()->get_root()->add_child(bc);
	ClassDB::register_class<BrickController>();
}

void uninitialize_brick_controller_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}