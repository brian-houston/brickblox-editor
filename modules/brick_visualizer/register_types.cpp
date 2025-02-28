#include "register_types.h"

#include "core/object/class_db.h"
#include "brick_visualizer.h"

void initialize_brick_visualizer_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<BrickVisualizer>();
}

void uninitialize_brick_visualizer_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}