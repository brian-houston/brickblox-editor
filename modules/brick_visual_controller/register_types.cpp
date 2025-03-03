#include "register_types.h"

#include "core/object/class_db.h"
#include "scene/main/window.h"
#include "brick_visual_controller.h"



void initialize_brick_visual_controller_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}
}

void uninitialize_brick_visual_controller_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}