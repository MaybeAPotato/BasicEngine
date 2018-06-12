#include "Component.h"

namespace Core {

	Component::Component()
	{
	}


	Component::~Component()
	{
		delete parent;
		parent = nullptr;
	}
}