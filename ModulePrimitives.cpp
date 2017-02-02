#include "ModulePrimitives.h"
#include "SCube.h"
#include "SPlane.h"
#include "SCylinder.h"

ModulePrimitives::ModulePrimitives(const JSON_Value *json, bool enable) : Module(json, enable){
}


ModulePrimitives::~ModulePrimitives() {
}

update_status ModulePrimitives::PreUpdate() {
	for (std::list<SPrimitive*>::iterator it = primitives.begin(); it != primitives.end();) {
		if ((*it)->toDelete) {
			RELEASE(*it);
			it = primitives.erase(it);
		}
		else {
			++it;
		}

	}
	return UPDATE_CONTINUE;
}


SPrimitive * ModulePrimitives::AddPrimitive(const std::list<float> &points, float size, SPRIMITIVE_TYPE type) {
	SPrimitive *result = nullptr;
	static_assert(SPRIMITIVE_TYPE::UNDEFINED == 3, "Update primitives types");

	switch (type) {
	case SCUBE_TYPE:
		result = new SCube();
		break;
	case SPLANE_TYPE:
		result = new SPlane();
		break;
	case SCYLINDER_TYPE:
		result = new SCylinder();
		break;
	}

	if (result != nullptr)
		primitives.push_back(result);

	return result;
}

bool ModulePrimitives::CleanUp() {
	for (std::list<SPrimitive*>::iterator it = primitives.begin(); it != primitives.end(); ++it) {
		RELEASE(*it);
	}

	primitives.clear();
	return true;
}
