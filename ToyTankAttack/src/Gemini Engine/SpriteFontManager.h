// SpriteFontManager

#include <map>

#ifndef _SpriteFontManager
#define _SpriteFontManager

class SpriteFont;

class SpriteFontManager
{
	/// \cond
	friend class SpriteFontManagerAttorney;
	/// \endcond

private:
	/// \cond
	static SpriteFontManager* ptrInstance;

	static SpriteFontManager& Instance();

	// ---- BIG FOUR ---- //
	SpriteFontManager() = default;
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator= (const SpriteFontManager&) = delete;
	~SpriteFontManager() = default;

	// ---- PRIVATE METHODS ---- //
	void privLoad(const std::string& key, const std::string& path);
	SpriteFont* privGet(const std::string& key);
	void privDelete();

	static void Delete() { Instance().privDelete(); } // No User acces, only Attorney


	// ---- PRIVATE MEMBER VARS ---- //
	std::map<std::string, SpriteFont*> storageMap;
	const std::string DefaultPath = "Fonts/";
	/// \endcond

public:
	///-------------------------------------------------------------------------------------------------
	/// \fn	static void SpriteFontManager::Load(const std::string& key, const std::string& path)
	///
	/// \brief	Loads a font from a filename, saving it with a string key.
	///
	/// \param 	key 	The key for the font as a string. Used for retrieving the font.
	/// \param 	path	Name of the font file. MUST be .tga format
	/// 
	/// \par Example:
	/// 	 
	/// \code
	/// 	 TextureManager::Load("SpaceFrigateTex", "space_frigate.tga"); // FIX!!!!!!!!!!!!!!!!!!!!!
	/// \endcode
	/// 						
	/// \note 1. All textures MUST be stored in the GeminiEngine/Assets/Fonts folder of your project.
	///	
	///	\note 2. Font Loading should be done in Gemini::LoadResources()
	///		  
	/// ------------------------------------------------------------------------------------------------
	static void Load(const std::string& key, const std::string& path) { Instance().privLoad(key, path); }


	///-------------------------------------------------------------------------------------------------
	/// \fn	static SpriteFont* SpriteFontManager::Get(const std::string& key)
	///
	/// \brief	Gets a SpriteFont* using the given key
	///
	/// \param 	key	The key to retrieve, as a string.
	///
	/// \returns	Null if it fails, else a pointer to a SpriteFont.
	/// 			
	/// \par Example: // FIX!!!!!!!!!!!!!!!!!!!!!!!!
	/// 	 
	/// \code
	/// 	 // Context: 
	/// 	 // - Creating a Graphics Object for the Frigate - needs a pointer to the Frigate Texture
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
	static SpriteFont* Get(const std::string& key) { return Instance().privGet(key); }
};

#endif _SpriteFontManager