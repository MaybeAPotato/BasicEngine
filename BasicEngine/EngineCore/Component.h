#ifndef COMPONENT_H
#define COMPONENT_H
namespace Core {

	class Component
	{
	public:
		Component();
		virtual ~Component();

		virtual bool Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual bool Shutdown() = 0;
	};
}
#endif // !COMPONENT_H
