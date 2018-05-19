#include "System.h"

namespace Core {

	System::System(SystemType systemType) : type(systemType)
	{
	}


	System::~System()
	{
	}
	bool System::Init()
	{
		return true;
	}
	void System::Update()
	{
	}
	void System::Render()
	{
	}
	bool System::Shutdown()
	{
		return true;
	}
}
