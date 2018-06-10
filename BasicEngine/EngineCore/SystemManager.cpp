#include "SystemManager.h"
#include "System.h"

namespace Core {
	SystemManager::SystemManager()
	{
	}

	SystemManager::~SystemManager()
	{
		for (System* s : systems) {
			delete s;
			s = nullptr;
		}

		systems.clear();
	}

	bool SystemManager::Init()
	{
		for (System* s : systems) {
			if (!s->Init()) {
				return false;
			}
		}

		return true;
	}
	void SystemManager::Update()
	{
		for (System* s : systems) {
			s->Update();
		}
	}
	void SystemManager::Render()
	{
		for (System* s : systems) {
			s->Render();
		}
	}
	bool SystemManager::Shutdown()
	{
		bool success = true;
		for (System* s : systems) {
			if (!s->Shutdown()) {
				success = false;
			}
		}
		return success;
	}
}