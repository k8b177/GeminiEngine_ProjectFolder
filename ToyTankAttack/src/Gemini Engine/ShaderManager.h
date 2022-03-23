// ShaderManager
// Katherine Burnett, January 2022

#include <map>

#ifndef _ShaderManager
#define _ShaderManager

class ShaderObject;

class ShaderManager
{
	/// \cond
	friend class ShaderManagerAttorney;
	/// \endcond

private:
	/// \cond
	static ShaderManager* ptrInstance;

	static ShaderManager& Instance();

	// ---- BIG FOUR ---- //
	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator= (const ShaderManager&) = delete;
	~ShaderManager() = default;

	// ---- PRIVATE METHODS ---- //
	void privLoad(const std::string& key, const std::string& path);
	ShaderObject* privGet(const std::string& key);
	void privDelete();

	static void Delete() { Instance().privDelete(); } // No User acces, only Attorney



	// ---- PRIVATE MEMBER VARS ---- //
	std::map<std::string, ShaderObject*> storageMap;
	const std::string DefaultPath = "Shaders/";
	/// \endcond

public:
	///-------------------------------------------------------------------------------------------------
	/// \fn	static void ShaderManager::Load(const std::string& key, const std::string& path)
	///
	/// \brief	Loads a shader from a filename, saving it with a string key.
	///
	/// \param 	key 	The key for the shader as a string. Used for retrieving the shader.
	/// \param 	path	Name of the shader file.
	/// 
	/// \par Example:
	/// 	 
	/// \code
	/// 	 ShaderManager::Load("TextureLight", "textureLightRender");
	/// \endcode
	/// 						
	/// \note 1. All shaders MUST be stored in the GeminiEngine/Assets/Shaders folder of your project.
	///	
	///	\note 2. Shader Loading should be done in Gemini::LoadResources()
	///		  
	/// -------------------------------------------------------------------------------------------------
	static void Load(const std::string& key, const std::string& path) { Instance().privLoad(key, path); }
	
	///-------------------------------------------------------------------------------------------------
	/// \fn	static ShaderObject* ShaderManager::Get(const std::string& key)
	///
	/// \brief	Gets a ShaderObject* using the given key
	///
	/// \param 	key	The key to retrieve, as a string.
	///
	/// \returns	Null if it fails, else a pointer to a ShaderObject.
	/// 			
	/// \par Example:
	/// 	 
	/// \code
	/// 	 // Context: 
	/// 	 // - Creating a Graphics Object for the Frigate - needs a pointer to the TextureLight ShaderObject
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
	static ShaderObject* Get(const std::string& key) { return Instance().privGet(key); }
};

#endif _ShaderManager