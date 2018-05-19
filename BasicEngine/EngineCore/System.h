#ifndef SYSTEM_H
#define SYSTEM_H

enum class SystemType : unsigned __int8 {
	WINDOW,
	INPUT,
	GRAPHICS,
	TOTAL
};

namespace Core {
	class System
	{
		SystemType type;

	public:
		System(SystemType systemType);
		virtual ~System();

		virtual bool Init();
		virtual void Update();
		virtual void Render();
		virtual bool Shutdown();
	};
}
#endif // !SYSTEM_H
