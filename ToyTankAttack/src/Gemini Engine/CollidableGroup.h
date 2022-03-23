#ifndef CollidableGroup_
#define CollidableGroup_

#include <list>

class Collidable;

class CollidableGroup
{
public:
	using CollidableCollection = std::list<Collidable*>;
	using CollidableCollectionRef = CollidableCollection::iterator;

private:
	CollidableCollection CollideCol;

public:
	// ---- BIG FOUR ---- //
	CollidableGroup() = default;
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator= (const CollidableGroup&) = delete;
	virtual ~CollidableGroup() = default;

	void Register(Collidable* c, CollidableCollectionRef& ref);
	void Deregister(const CollidableCollectionRef& ref);

	const CollidableCollection& GetColliderCollection();


};


#endif CollidableGroup_
