#include "AssetManager.h"
#include "Asset.h"

namespace Core {
	AssetManager::AssetManager()
	{
	}


	AssetManager::~AssetManager()
	{
	}

	bool Core::AssetManager::Init()
	{
		auto itr = assets.begin();

		while (itr->second) {
			if (!assets.at(itr->first)->Init()) {
				return false;
			}
			itr++;
		}

		return true;
	}

	void Core::AssetManager::Update()
	{
		auto itr = assets.begin();

		while(itr->second) {
			assets.at(itr->first)->Update();
			itr++;
		}
	}

	void Core::AssetManager::Render()
	{
		auto itr = assets.begin();

		while (itr->second) {
			assets.at(itr->first)->Render();
			itr++;
		}
	}

	bool Core::AssetManager::Shutdown()
	{
		auto itr = assets.begin();

		while (itr->second) {
			if (!assets.at(itr->first)->Shutdown()) {
				return false;
			}
			itr++;
		}

		return true;
	}
	void AssetManager::AddAsset(char * key, Asset * a)
	{
		assets.insert(std::make_pair(key, a));
	}
	Asset * AssetManager::GetAsset(char * key)
	{
		return assets.find(key)->second;
	}
}