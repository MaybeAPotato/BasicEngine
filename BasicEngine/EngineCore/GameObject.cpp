#include "GameObject.h"
#include "Component.h"

namespace Core {

	GameObject::GameObject()
	{
	}


	GameObject::~GameObject()
	{
	}
	void GameObject::AddComponent(Component & c)
	{
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
}