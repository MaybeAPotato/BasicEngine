#ifndef ASSET_H
#define ASSET_H

namespace Core {
	class Asset
	{
	public:
		Asset();
		~Asset();

		virtual bool Init();
		virtual void Update();
		virtual void Render();
		virtual bool Shutdown();
	};
}
#endif // !ASSET_H
