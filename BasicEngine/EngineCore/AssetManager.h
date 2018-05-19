#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "Singleton.h"
#include <map>
namespace Core {
	class AssetManager :public Singleton<AssetManager>
	{
		AssetManager();
		std::map<char*, class Asset*>assets;

	public:
		~AssetManager();

		bool Init();
		void Update();
		void Render();
		bool Shutdown();

		void AddAsset(char* key, Asset* a);
		inline Asset* GetAsset(char* key);
		inline std::map<char*, Asset*> GetAssets() { return assets; }
	};
}
#endif // !ASSET_MANAGER_H
