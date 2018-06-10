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

		while (itr != assets.end()) {
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

		while(itr != assets.end()) {
			assets.at(itr->first)->Update();
			itr++;
		}
	}

	void Core::AssetManager::Render()
	{
		auto itr = assets.begin();

		while (itr != assets.end()) {
			assets.at(itr->first)->Render();
			itr++;
		}
	}

	bool Core::AssetManager::Shutdown()
	{
		auto itr = assets.begin();

		while (itr != assets.end()) {
			if (!assets.at(itr->first)->Shutdown()) {
				return false;
			}
			itr++;
		}

		return true;
	}
	void AssetManager::AddAsset(const char * key, Asset * a)
	{
		//assets.insert(std::make_pair(key, a));
		//For key have asset a
		assets[key] = a;
	}
	void AssetManager::AddAsseti(const char * key, Asset * a)
	{
		a->Init();
		assets[key] = a;
	}
	Asset * AssetManager::GetAsset(const char * key)
	{
		auto it = assets.find(key);
		if (it != assets.end()) {
			return it->second;
		}
		return nullptr;
	}
}