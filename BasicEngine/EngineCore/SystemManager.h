#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "Singleton.h"
#include <algorithm>
#include <vector>

namespace Core {

	class SystemManager : public Singleton<SystemManager>
	{

		friend Singleton;

		std::vector<class System*>systems;

	public:
		~SystemManager();

		bool Init();
		void Update();
		void Render();
		bool Shutdown();

		void AddSystem(System& newSystem) { systems.push_back(&newSystem); }
		void AddSystem(System& newSystem, int index) { systems.insert(systems.begin() + index, &newSystem); }
		void RemoveSystem(int index) { systems.erase(systems.begin() + index); }
		void RemoveSystem() { systems.pop_back(); }
		inline const std::vector<System*>& GetSystems() const { return systems; }
		template<class T>
		T * GetSystem() const
		{
			//System* s = std::find_if(systems.begin(), systems.end(), [T](System* m) > bool{
			//	return dynamic_cast<T>(m) != nullptr;
			//	})
			for (System* s : systems) {
				T* m = dynamic_cast<T*>(s);
				if (m) {
					return m;
				}
			}
		}
	protected:
		SystemManager();
	};
}
#endif // !SYSTEM_MANAGER_H
