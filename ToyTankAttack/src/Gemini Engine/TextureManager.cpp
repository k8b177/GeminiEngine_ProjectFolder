// TextureManager

#include "TextureManager.h"

#include "Texture.h"

#include "ErrorMessage.h"

TextureManager* TextureManager::ptrInstance = nullptr;

TextureManager& TextureManager::Instance()
{
	if (!ptrInstance)
		ptrInstance = new TextureManager();
	return *ptrInstance;
}

void TextureManager::privLoad(const std::string& key, const std::string& path, int filtermode)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Texture with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}


	const std::string str = DefaultPath + path;
	Texture* t = new Texture(str.c_str(), filtermode);
	storageMap.insert({ key, t });
}

void TextureManager::privLoad(const std::string& key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char alpha)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Texture with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}

	Texture* t = new Texture(red, green, blue, alpha);
	storageMap.insert({ key, t });
}

void TextureManager::privLoadSpriteFontTexture(const std::string& key, const std::string& fontpath)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Texture with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}

	std::string fontpath_withext = fontpath + ".tga"; // need to add .tga extension
	Texture* t = new Texture(fontpath_withext.c_str()); // No DefaultPath because Fonts will be in Fonts folder (fontpath includes "Fonts/...")
	storageMap.insert({ key, t });
}

Texture* TextureManager::privGet(const std::string& key)
{
	auto it = storageMap.find(key);

	if (it == storageMap.end()) // if not in the map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Texture key name not found: '" + key + "'.", ErrorType::Crash);
	}

	return it->second;
}

void TextureManager::privDelete()
{
	for (auto& it : storageMap)
	{
		delete it.second;
	}

	storageMap.clear();

	delete ptrInstance;
}