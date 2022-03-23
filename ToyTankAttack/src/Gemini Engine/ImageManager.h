// ImageManager
// Katherine Burnett, February 2022

#include <map>

#ifndef _ImageManager
#define _ImageManager

class Image;
class Texture;
struct Rect;

class ImageManager
{
	friend class ImageManagerAttorney;

private:
	// ---- PRIVATE MEMBER VARS ---- //
	using StorageMap = std::map<std::string, Image*>;
	StorageMap storageMap;
	const std::string DefaultPath = "Images/";

	static ImageManager* ptrInstance;

	static ImageManager& Instance();

	// ---- BIG FOUR ---- //
	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator= (const ImageManager&) = delete;
	~ImageManager() = default;

	// ---- PRIVATE METHODS ---- //
	void privLoad(const std::string& key, Texture* tex);
	void privLoad(const std::string&, Texture* tex, Rect* r);
	Image* privGet(const std::string& key);
	void privDelete();

	static void Delete() { Instance().privDelete(); } // No User acces, only Attorney



public:
	static void Load(const std::string& key, Texture* tex) { Instance().privLoad(key, tex); }
	static void Load(const std::string& key, Texture* tex, Rect* r)
	{
		Instance().privLoad(key, tex, r);
	}
	static Image* Get(const std::string& key) { return Instance().privGet(key); }
};

#endif _ImageManager