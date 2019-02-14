#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Core {
	class GameObject
	{
	protected:
		glm::vec4 position;
		glm::vec4 rotation;
		glm::vec4 scale;

		glm::mat4 transform;

		//Not cache friendly
		std::vector<GameObject*> children;
		//Change to ECS
		std::vector<class Component*> components;
		std::vector<class Asset*> assets;
	public:
		GameObject();
		virtual ~GameObject();

		virtual bool Init();
		virtual void Update();
		virtual void Render();
		virtual bool Shutdown();

		void AddComponent(Component& c);
		void AddChild(GameObject& g);
		void RemoveComponent(Component& c);
		void RemoveChild(GameObject& g);
		void RemoveComponent(int index);
		void RemoveChild(int index);
		void AddAsset(Asset& a);
		void RemoveAsset(Asset& a);
		void RemoveAsset(int index);

		GameObject* GetChildren() { return children[0]; }
		Component* GetComponent() { return components[0]; }
		Asset* GetAsset() { return assets[0]; }

		GameObject* GetChildren(int index) { return children.at(index); }
		Component* GetComponent(int index) { return components.at(index); }
		Asset* GetAsset(int index) { return assets.at(index); }

		template<class T>
		GameObject* GetChildren() {
			for (GameObject* g : children) {
				if (dynamic_cast<T*>(g)) {
					return g;
				}
			}
			return nullptr;
		}

		template<class T>
		Component* GetComponent() {
			for (Component* c : components) {
				if (dynamic_cast<T*>(c)) {
					return c;
				}
			}
			return nullptr;
		}

		template<class T>
		void RemoveComponent() {
			for (auto itr = components.begin(); itr != components.end(); itr++) {
				if (dynamic_cast<T*>(*itr)) {
					components.erase(itr);
				}
			}
		}

		template<class T>
		void RemoveAsset() {
			for (auto itr = assets.begin(); itr != assets.end(); itr++) {
				if (dynamic_cast<T*>(*itr)) {
					assets.erase(itr);
				}
			}
		}

		template<class T>
		void RemoveChild() {
			for (auto itr = children.begin(); itr != children.end(); itr++) {
				if (dynamic_cast<T*>(*itr)) {
					children.erase(itr);
				}
			}
		}

		template<class T>
		void AddChildren() {
			if (dynamic_cast<GameObject*>(T)) {
				children.push_back(T);
			}
		}

		template<class T>
		void AddComponent() {
			if (dynamic_cast<Component*>(T)){
				components.push_back(T);
			}
		}

		template<class T>
		void AddAsset() {
			if (dynamic_cast<Asset*>(T)) {
				assets.push_back(T);
			}
		}

		//Translate object
		void Translate(float x, float y, float z);
		void Translate(glm::vec3 vec);

		//Scale object
		void Scale(float x, float y, float z);
		void Scale(glm::vec3 vec);

		//Rotate object
		void Rotate(float angle, float x, float y, float z);
		void Rotate(float angle, glm::vec3 vec);

		//Getter
		const glm::mat4& GetTransform() const { return transform; }
		const glm::vec4& GetPosition() const { return position; }
		const glm::vec4& GetRotatin() const { return rotation; }
		const glm::vec4& GetScale() const { return scale; }
	};
}

#endif // !GAME_OBJECT_H
