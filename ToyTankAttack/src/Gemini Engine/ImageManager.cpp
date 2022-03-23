// ImageManager

#include "ImageManager.h"

#include "Image.h"

#include "ErrorMessage.h"

ImageManager* ImageManager::ptrInstance = nullptr;

ImageManager& ImageManager::Instance()
{
	if (!ptrInstance)
		ptrInstance = new ImageManager();
	return *ptrInstance;
}

void ImageManager::privLoad(const std::string& key, Texture* tex)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Image with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}

	Image* i = new Image(tex, new Rect(0.0f, 0.0f, (float)tex->getWidth(), (float)tex->getHeight()));
	storageMap.insert({ key, i });
}

void ImageManager::privLoad(const std::string& key, Texture* tex, Rect* r)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Image with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}

	Image* i = new Image(tex, r);
	storageMap.insert({ key, i });
}

Image* ImageManager::privGet(const std::string& key)
{
	auto it = storageMap.find(key);

	if (it == storageMap.end()) // if not in the map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Image key name not found: '" + key + "'.", ErrorType::Crash);
	}

	return it->second;
}

void ImageManager::privDelete()
{
	for (auto& it : storageMap)
	{
		delete it.second;
	}

	storageMap.clear();

	delete ptrInstance;
}