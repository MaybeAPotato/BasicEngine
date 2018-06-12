#ifndef COMPONENT_H
#define COMPONENT_H
namespace Core {

	class Component
	{
	protected:
		class GameObject* parent;
	public:
		Component();
		virtual ~Component();

		virtual bool Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual bool Shutdown() = 0;

		void SetParent(GameObject* go) { parent = go; }
	};
}
#endif // !COMPONENT_H
