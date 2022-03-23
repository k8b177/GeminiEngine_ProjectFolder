// TextureManager
// Katherine Burnett, January 2022

#include <map>
#include "GL\glcorearb.h"

#ifndef _TextureManager
#define _TextureManager

class Texture;

class TextureManager
{
	/// \cond
	friend class TextureManagerAttorney;
	/// \endcond

private:
	/// \cond
	static TextureManager* ptrInstance;

	static TextureManager& Instance();

	// ---- BIG FOUR ---- //
	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator= (const TextureManager&) = delete;
	~TextureManager() = default;

	// ---- PRIVATE METHODS ---- //
	void privLoad(const std::string& key, const std::string& path, int filtermode);
	void privLoad(const std::string& key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char alpha);
	Texture* privGet(const std::string& key);
	void privDelete();

	static void Delete() { Instance().privDelete(); } // No User acces, only Attorney


	void privLoadSpriteFontTexture(const std::string& key, const std::string& fontpath);
	static void LoadSpriteFontTexture(const std::string& key, const std::string& fontpath) { Instance().privLoadSpriteFontTexture(key, fontpath); }



	// ---- PRIVATE MEMBER VARS ---- //
	std::map<std::string, Texture*> storageMap;
	const std::string DefaultPath = "Textures/";
	/// \endcond

public:
	///-------------------------------------------------------------------------------------------------
	/// \fn	static void TextureManager::Load(const std::string& key, const std::string& path)
	///
	/// \brief	Loads a texture from a filename, saving it with a string key.
	///
	/// \param 	key 	The key for the texture as a string. Used for retrieving the texture.
	/// \param 	path	Name of the texture file. MUST be .tga format
	/// \param  filtermode (optional) Specify the filtering mode of the texture.  Default mode is GL_LINEAR.
	/// 
	/// \par Example:
	/// 	 
	/// \code
	/// 	 TextureManager::Load("SpaceFrigateTex", "space_frigate.tga");
	/// \endcode
	/// 						
	/// \note 1. All textures MUST be stored in the GeminiEngine/Assets/Texture folder of your project.
	///	
	///	\note 2. Texture Loading should be done in Gemini::LoadResources()
	///		  
	/// ------------------------------------------------------------------------------------------------
	static void Load(const std::string& key, const std::string& path, int filtermode = GL_LINEAR) { Instance().privLoad(key, path, filtermode); }

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void TextureManager::Load(const std::string& key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char alpha = 255U)
	///
	/// \brief	Loads a single-color texture based on RGBA parameters.
	///
	/// \par Example:
	///
	/// \code
	/// 	 TextureManager::Load("Orange", 255, 165, 0);
	/// \endcode
	///
	/// \note 1. If loading a single-color texture, you do not need any external texture in the Textures folder.
	///
	///	\note 2. Texture Loading should be done in Gemini::LoadResources()
	///
	/// \param 	key  	The key for the texture as a string. Used for retrieving the texture.
	/// \param 	red  	Red color value.
	/// \param 	green	Green color value.
	/// \param 	blue 	Blue color value.
	/// \param 	alpha	(Optional) Alpha color value.
	/// 				
	///-------------------------------------------------------------------------------------------------
	static void Load(const std::string& key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char alpha = 255U)
	{
		Instance().privLoad(key, red, green, blue, alpha);
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	static Texture* TextureManager::Get(const std::string& key)
	///
	/// \brief	Gets a Texture* using the given key
	///
	/// \param 	key	The key to retrieve, as a string.
	///
	/// \returns	Null if it fails, else a pointer to a Texture.
	/// 			
	/// \par Example:
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
	static Texture* Get(const std::string& key) { return Instance().privGet(key); }
};

#endif _TextureManager