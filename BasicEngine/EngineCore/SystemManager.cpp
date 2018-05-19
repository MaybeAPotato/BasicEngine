#include "SystemManager.h"
#include "System.h"

namespace Core {
	SystemManager::SystemManager()
	{
	}

	SystemManager::~SystemManager()
	{
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

	template<class T>
	T * SystemManager::GetSystem() const
	{
		//System* s = std::find_if(systems.begin(), systems.end(), [T](System* m) > bool{
		//	return dynamic_cast<T>(m) != nullptr;
		//	})
		for (System* s : systems) {
			if (m = dynamic_cast<T>(s)) {
				return m;
			}
		}
	}
}