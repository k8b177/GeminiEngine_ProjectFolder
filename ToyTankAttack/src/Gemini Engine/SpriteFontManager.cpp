// SpriteFontManager

#include "SpriteFontManager.h"

#include "SpriteFont.h"

#include "ErrorMessage.h"

SpriteFontManager* SpriteFontManager::ptrInstance = nullptr;

SpriteFontManager& SpriteFontManager::Instance()
{
	if (!ptrInstance)
		ptrInstance = new SpriteFontManager();
	return *ptrInstance;
}

void SpriteFontManager::privLoad(const std::string& key, const std::string& path)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded SpriteFont with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}

	const std::string str = DefaultPath + path;
	SpriteFont* sf = new SpriteFont(str);
	storageMap.insert({ key, sf });
}

SpriteFont* SpriteFontManager::privGet(const std::string& key)
{
	auto it = storageMap.find(key);

	if (it == storageMap.end()) // if not in the map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Texture key name not found: '" + key + "'.", ErrorType::Crash);
	}

	return it->second;
}

void SpriteFontManager::privDelete()
{
	for (auto& it : storageMap)
	{
		delete it.second;
	}

	storageMap.clear();

	delete ptrInstance;
}