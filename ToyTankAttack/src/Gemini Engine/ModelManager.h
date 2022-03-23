// ModelManager
// Katherine Burnett, January 2022

#include <map>
#include "Model.h"

#ifndef _ModelManager
#define _ModelManager

class ModelManager
{
	/// \cond
	friend class ModelManagerAttorney;
	/// \endcond

private:
	/// \cond
	static ModelManager* ptrInstance;

	static ModelManager& Instance();

	// ---- BIG FOUR ---- //
	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator= (const ModelManager&) = delete;
	~ModelManager() = default;

	// ---- PRIVATE METHODS ---- //
	void privLoad(const std::string& key, const std::string& path);
	void privLoad(const std::string& key, const Model::PreMadeModels pmm);
	void privLoad(const std::string& key, int sizeXZ, int repeatU, int repeatV);
	Model* privGet(const std::string& key);
	void privDelete();

	static void Delete() { Instance().privDelete(); } // No User acces, only Attorney



	// ---- PRIVATE MEMBER VARS ---- //
	std::map<std::string, Model*> storageMap;
	const std::string DefaultPath = "Models/";
	/// \endcond

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void ModelManager::Load(const std::string& key, const std::string& path)
	///
	/// \brief	Loads a .azul model from a filename, saving it with a string key.
	///
	/// \param 	key 	The key for the model as a string. Used for retrieving the model.
	/// \param 	path	Name of the model file. MUST be .azul format.
	/// 
	/// \par Example:
	/// 	 
	/// \code
	/// 	 ModelManager::Load("Frigate", "space_frigate.azul");
	/// \endcode
	/// 						
	/// \note 1. All models MUST be stored in the GeminiEngine/Assets/Models folder of your project.
	///	
	///	\note 2. Model Loading should be done in Gemini::LoadResources()
	///		  
	/// -------------------------------------------------------------------------------------------------
	static void Load(const std::string& key, const std::string& path) { Instance().privLoad(key, path); }

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void ModelManager::Load(const std::string& key, const Model::PreMadeModels pmm)
	///
	/// \brief	Loads a PreMadeModel, saving it with a string key.
	///
	/// \param 	key	The key for the model as a string. Used for retrieving the model.
	/// \param 	pmm	The Model::PreMadeModel enum desired.
	/// 			
	/// \par Example:
	/// 	 
	/// \code
	/// 	 ModelManager::Load("Sphere", Model::PreMadeModels::UnitSphere);
	/// \endcode
	/// 			
	/// \note 1. If loading a PreMadeModel, you do not need any external model in the Models folder.
	/// 	 
	/// \note 2. Model loading should be done in Gemini::LoadResources() 
	/// 	  
	///-------------------------------------------------------------------------------------------------
	static void Load(const std::string& key, const Model::PreMadeModels pmm)
	{
		Instance().privLoad(key, pmm);
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void ModelManager::Load(const std::string& key, int sizeXZ, int repeatU, int repeatV)
	///
	/// \brief	Loads a plane Model of sizeXZ with repeating UVs, saving it with a string key.
	/// 			
	/// \param 	key		The key for the model as a string. Used for retrieving the model.
	/// \param 	sizeXZ 	The size xz of the plane.
	/// \param 	repeatU	The repeat u.
	/// \param 	repeatV	The repeat v.
	/// 	
	/// \par Example:
	///
	/// \code
	/// 	 ModelManager::Load("FloorPlane", 800, 8, 8);
	/// \endcode
	///
	/// \note 1. If loading a plane Model, you do not need any external model in the Models folder.
	///
	/// \note 2. Model loading should be done in Gemini::LoadResources()
	///
	///-------------------------------------------------------------------------------------------------
	static void Load(const std::string& key, int sizeXZ, int repeatU, int repeatV)
	{
		Instance().privLoad(key, sizeXZ, repeatU, repeatV);
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	static Model* ModelManager::Get(const std::string& key)
	///
	/// \brief	Gets a Model* using the given key
	///
	/// \param 	key	The key to retrieve, as a string.
	///
	/// \returns	Null if it fails, else a pointer to a Model.
	/// 			
	/// \par Example:
	/// 	 
	/// \code
	/// 	 // Context: 
	/// 	 // - Creating a Graphics Object for the Frigate - needs a pointer to the Frigate model
	/// 	 // - pGObjLT is type GraphicsObject_TextureLight*
	/// 	 // - LightColor and LightPos are Vect's
	/// 	 
	/// 		pGObjLT = new GraphicsObject_TextureLight(
	/// 			ModelManager::Get("Frigate"), 
	/// 			ShaderManager::Get("TextureLight"), 
	/// 			TextureManager::Get("SpaceFrigateTex"), 
	/// 			LightColor, 
	/// 			LightPos);
	///	\endcode
	///			
	///-------------------------------------------------------------------------------------------------
	static Model* Get(const std::string& key) { return Instance().privGet(key); }

};

#endif _ModelManager