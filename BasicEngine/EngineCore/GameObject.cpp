#include "GameObject.h"
#include "Component.h"

namespace Core {



	GameObject::GameObject() : position(0.0f,0.0f,0.0f,1.0f),scale(1.0f,1.0f,1.0f,1.0f),rotation(0.0f,0.0f,0.0f,0.0f),transform()
	{
	}


	GameObject::~GameObject()
	{
	}
	void GameObject::AddComponent(Component & c)
	{
		c.SetParent(this);
		components.push_back(&c);
	}
	void GameObject::AddChild(GameObject & g)
	{
		children.push_back(&g);
	}
	bool GameObject::Init()
	{
		for (Component* c : components) {
			if (c->Init()) {
				return false;
			}
		}
		for (GameObject* g : children) {
			if (g->Init()) {
				return false;
			}
		}
		return true;
	}
	void GameObject::Update()
	{
		for (Component* c : components) {
			c->Update();
		}
		for (GameObject* g : children) {
			g->Update();
		}
	}
	void GameObject::Render()
	{
		for (Component* c : components) {
			c->Render();
		}
		for (GameObject* g : children) {
			g->Render();
		}
	}
	bool GameObject::Shutdown()
	{
		for (Component* c : components) {
			if (c->Shutdown()) {
				return false;
			}
		}
		for (GameObject* g : children) {
			if (g->Shutdown()) {
				return false;
			}
		}
		return true;
	}
	void GameObject::Translate(float x, float y, float z)
	{
		transform = glm::translate(transform, glm::vec3(x, y, z));
	}
	void GameObject::Translate(glm::vec3 vec)
	{
		transform = glm::translate(transform, vec);
	}
	void GameObject::Scale(float x, float y, float z)
	{
		transform = glm::scale(transform, glm::vec3(x, y, z));
	}
	void GameObject::Scale(glm::vec3 scale)
	{
		transform = glm::scale(transform, scale);
	}
	void GameObject::Rotate(float angle, float x, float y, float z)
	{
		transform = glm::rotate(transform, angle, glm::vec3(x, y, z));
	}
	void GameObject::Rotate(float angle, glm::vec3 vec)
	{
		transform = glm::rotate(transform, angle, vec);
	}
}