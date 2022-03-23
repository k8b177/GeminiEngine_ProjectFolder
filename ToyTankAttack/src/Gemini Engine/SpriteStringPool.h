#ifndef SpriteStringPool_
#define SpriteStringPool_

#include <stack>

class SpriteString;

class SpriteStringPool
{
private:
	std::stack<SpriteString*> recycledSpriteStrings;

public:
	SpriteStringPool() = default;
	SpriteStringPool(const SpriteStringPool&) = delete;
	SpriteStringPool& operator=(const SpriteStringPool&) = delete;
	~SpriteStringPool();

	SpriteString* GetSpriteString();

	void ReturnSpriteString(SpriteString* s);
};


#endif SpriteStringPool_
