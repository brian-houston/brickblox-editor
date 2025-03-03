#include "register_types.h"

#include "core/object/class_db.h"
#include "brick.h"

void initialize_brick_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<Brick>();
}

void uninitialize_brick_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	if (Brick::box_shape != nullptr) {
		memdelete(Brick::box_shape);
	}
}