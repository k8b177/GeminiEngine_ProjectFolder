// ModelManager

#include "ModelManager.h"

#include "ErrorMessage.h"

ModelManager* ModelManager::ptrInstance = nullptr;

ModelManager& ModelManager::Instance()
{
	if (!ptrInstance)
		ptrInstance = new ModelManager();
	return *ptrInstance;
}

ModelManager::ModelManager()
{
	// Load the spriteRender UnitSquareXY model out the gate (for sprites)
	this->privLoad("UnitSquareXY", Model::PreMadeModels::UnitSquareXY);
}

void ModelManager::privLoad(const std::string& key, const std::string& path)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Model with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}


	const std::string fullPath = DefaultPath + path;
	Model* m = new Model(&fullPath[0]);
	storageMap.insert({ key, m });
}

void ModelManager::privLoad(const std::string& key, const Model::PreMadeModels pmm)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Model with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}

	Model* m = new Model(pmm);
	storageMap.insert({ key, m });
}

void ModelManager::privLoad(const std::string& key, int sizeXZ, int repeatU, int repeatV)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Model with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}

	Model* m = new Model(sizeXZ, repeatU, repeatV);
	storageMap.insert({ key, m });
}

Model* ModelManager::privGet(const std::string& key)
{
	auto it = storageMap.find(key);

	if (it == storageMap.end()) // if not in the map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Model key name not found: '" + key + "'.", ErrorType::Crash);
	}

	return it->second;
}

void ModelManager::privDelete()
{
	for (auto& it : storageMap)
	{
		delete it.second;
	}

	storageMap.clear();

	delete ptrInstance;
}