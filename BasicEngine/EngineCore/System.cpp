#include "System.h"

namespace Core {

	System::System(SystemType systemType) : type(systemType),name(SetName(systemType))
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
	const char* System::SetName(SystemType type)
	{
		switch (type)
		{
		case SystemType::WINDOW:
			return "Window";
			break;
		case SystemType::INPUT:
			return "Input";
			break;
		case SystemType::GRAPHICS:
			return "Graphics";
			break;
		case SystemType::CLOCK:
			return "Clock";
			break;
		case SystemType::TOTAL:
			return "Total";
			break;
		default:
			break;
		}
	}
	const char * System::GetName()
	{
		return name;
	}
}
