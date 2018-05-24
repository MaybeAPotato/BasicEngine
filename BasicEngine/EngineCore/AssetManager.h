#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "Singleton.h"
#include <map>
namespace Core {
	class AssetManager :public Singleton<AssetManager>
	{
		std::map<const char*, class Asset*>assets;
	public:
		~AssetManager();

		bool Init();
		void Update();
		void Render();
		bool Shutdown();

		void AddAsset(const char* key, Asset* a);
		inline Asset* GetAsset(char* key);
		inline std::map<const char*, Asset*> GetAssets() { return assets; }
	protected:
		AssetManager();
	};
}
#endif // !ASSET_MANAGER_H
