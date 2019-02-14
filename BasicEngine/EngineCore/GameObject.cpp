#include "GameObject.h"
#include "Component.h"
#include "Asset.h"

namespace Core {



	GameObject::GameObject() : position(0.0f, 0.0f, 0.0f, 1.0f), scale(1.0f, 1.0f, 1.0f, 1.0f), rotation(0.0f, 0.0f, 0.0f, 0.0f), transform()
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
	void GameObject::RemoveComponent(Component & c)
	{
		auto itr = components.begin();
		
		while (itr != components.end()) {

		}
	}
	void GameObject::RemoveChild(GameObject & g)
	{
		auto itr = children.begin();

		while (itr != children.end()) {

		}
	}

	void GameObject::RemoveComponent(int index)
	{
		components.erase(components.begin() + index);
	}

	void GameObject::RemoveChild(int index)
	{
		children.erase(children.begin() + index);
	}

	void GameObject::AddAsset(Asset & a)
	{
		assets.push_back(&a);
	}

	void GameObject::RemoveAsset(Asset & a)
	{
		auto itr = assets.begin();

		while (itr != assets.end()) {

		}
	}

	void GameObject::RemoveAsset(int index)
	{
		assets.erase(assets.begin() + index);
	}

	bool GameObject::Init()
	{
		for (Asset* a : assets) {
			if (!a->Init()) {
				return false;
			}
		}
		for (Component* c : components) {
			if (!c->Init()) {
				return false;
			}
		}
		for (GameObject* g : children) {
			if (!g->Init()) {
				return false;
			}
		}
		return true;
	}
	void GameObject::Update()
	{
		transform = glm::translate(transform, glm::vec3(position));
		transform = glm::rotate(transform, rotation.z, glm::vec3(rotation));
		transform = glm::scale(transform, glm::vec3(scale));

		for (Component* c : components) {
			c->Update();
		}
		for (GameObject* g : children) {
			g->Update();
		}
		for (Asset* a : assets) {
			a->Update();
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
		for (Asset* a : assets) {
			a->Render();
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
		for (Asset* a : assets) {
			if (a->Shutdown()) {
				return false;
			}
		}
		return true;
	}
	void GameObject::Translate(float x, float y, float z)
	{ 
		position = glm::vec4(x, y, z,1.0f);
		transform = glm::translate(transform, glm::vec3(x, y, z));
	}
	void GameObject::Translate(glm::vec3 vec)
	{
		position = glm::vec4(vec,1.0f);
		transform = glm::translate(transform, vec);
	}
	void GameObject::Scale(float x, float y, float z)
	{
		scale = glm::vec4(x, y, z, 1.0f);
		transform = glm::scale(transform, glm::vec3(x, y, z));
	}
	void GameObject::Scale(glm::vec3 vec)
	{
		scale = glm::vec4(vec, 1.0f);
		transform = glm::scale(transform, vec);
	}
	void GameObject::Rotate(float angle, float x, float y, float z)
	{
		rotation = glm::vec4(x, y, z, angle);
		transform = glm::rotate(transform, angle, glm::vec3(x, y, z));
	}
	void GameObject::Rotate(float angle, glm::vec3 vec)
	{
		rotation = glm::vec4(vec, angle);
		transform = glm::rotate(transform, angle, vec);
	}
}