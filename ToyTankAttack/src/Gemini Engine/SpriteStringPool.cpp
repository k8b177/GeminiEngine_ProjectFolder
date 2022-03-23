#include "SpriteStringPool.h"

#include "SpriteString.h"

SpriteString* SpriteStringPool::GetSpriteString()
{
	SpriteString* s;

	if (recycledSpriteStrings.empty())
	{
		s = new SpriteString();
	}
	else
	{
		s = recycledSpriteStrings.top();
		recycledSpriteStrings.pop();
	}

	return s;
}

void SpriteStringPool::ReturnSpriteString(SpriteString* s)
{
	recycledSpriteStrings.push(s);
}

SpriteStringPool::~SpriteStringPool()
{
	// forcefully delele all recycled sprite strings
	while (!recycledSpriteStrings.empty())
	{
		delete recycledSpriteStrings.top();
		recycledSpriteStrings.pop();
	}
}