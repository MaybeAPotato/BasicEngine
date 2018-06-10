#ifndef SYSTEM_H
#define SYSTEM_H

enum class SystemType : unsigned __int8 {
	WINDOW,
	INPUT,
	GRAPHICS,
	CLOCK,
	UI,
	TOTAL
};

namespace Core {
	class System
	{
		SystemType type;
		const char* name;

		const char* SetName(SystemType type);

	public:
		System(SystemType systemType);
		virtual ~System();

		virtual bool Init();
		virtual void Update();
		virtual void Render();
		virtual bool Shutdown();

		const char* GetName();
	};
}
#endif // !SYSTEM_H
