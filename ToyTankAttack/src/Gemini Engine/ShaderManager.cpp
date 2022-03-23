// ShaderManager

#include "ShaderManager.h"

#include "ShaderObject.h"

#include "ErrorMessage.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;

ShaderManager& ShaderManager::Instance()
{
	if (!ptrInstance)
		ptrInstance = new ShaderManager();
	return *ptrInstance;
}

ShaderManager::ShaderManager()
{
	// Load the spriteRender ShaderObject out the gate (for sprites)
	this->privLoad("SpriteRender", "spriteRender");
}

void ShaderManager::privLoad(const std::string& key, const std::string& path)
{
	if (auto it = storageMap.find(key) != storageMap.end()) // if key already in map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Already loaded Shader with key name '" + key + "'.  Use another key name.", ErrorType::Crash);
	}


	const std::string str = DefaultPath + path;
	ShaderObject* s = new ShaderObject(&str[0]);
	storageMap.insert({ key, s });
}

ShaderObject* ShaderManager::privGet(const std::string& key)
{
	auto it = storageMap.find(key);

	if (it == storageMap.end()) // if not in the map --> ERROR
	{
		ErrorMessage E = ErrorMessage("Shader key name not found: '" + key + "'.", ErrorType::Crash);
	}

	return it->second;
}

void ShaderManager::privDelete()
{
	for (auto& it : storageMap)
	{
		delete it.second;
	}

	storageMap.clear();

	delete ptrInstance;
}