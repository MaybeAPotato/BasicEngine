#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

namespace Core {
	class GameObject
	{
		//Not cache friendly
		std::vector<GameObject*> children;
		//Change to ECS
		std::vector<class Component*> components;
	public:
		GameObject();
		virtual ~GameObject();

		void AddComponent(Component& c);
		void AddChild(GameObject& g);
		GameObject* GetChildren() { return children[0]; }
		Component* GetComponent() { return components[0]; }

		virtual bool Init();
		virtual void Update();
		virtual void Render();
		virtual bool Shutdown();

		template<class T>
		Component* GetComponent() {
			for (Component* c : components) {
				if (dynamic_cast<T>(c)) {
					return c;
				}
			}
			return nullptr;
		}
	};
}

#endif // !GAME_OBJECT_H
