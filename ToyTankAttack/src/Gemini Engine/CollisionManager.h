#ifndef CollisionManager_
#define CollisionManager_

#include "DebugOut.h"
#include <vector>
#include <list>
#include "CollisionDispatch.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"

class CollidableGroup;
class CollisionTestCommandBase;

class CollisionManager
{

public:
	using GemTypeID = int; // shortcut for collision group type id's
	static const GemTypeID GEMID_UNDEFINED = -1; // default value for undefined type id

private:
	// Collision Groups
	static GemTypeID TypeIDNextNumber; // counter for collision group type id's --> increases each time a new collision group is created

	const int MAX_COLLISION_GROUP = 300; // maximum number of collidable groups
	using CollidableGroupCollection = std::vector<CollidableGroup*>; // shortcut for the vector of CollidableGroups
	CollidableGroupCollection ColGroupCollection; // vector storage for all the Collidable Groups

	void SetGroupForTypeID(CollisionManager::GemTypeID ind); // creates a new Collidable Group if the type doesn't already have a group


	// Collision Test Commands
	using CollisionTestCommands = std::list<CollisionTestCommandBase*>; // shortcut for the list of collision test commands
	CollisionTestCommands colTestCommands; // list of collision test commands

public:
	// ---- BIG FOUR ---- //
	CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator= (const CollisionManager&) = delete;
	~CollisionManager();

	template <typename C>
	GemTypeID GetTypeID() // gets the type id for a given game object type
	{
		static GemTypeID myTypeID = TypeIDNextNumber++;
		
		SetGroupForTypeID(myTypeID);

		//DebugMsg::out("Type ID: %i\n", myTypeID);
		return myTypeID;
	}

	CollidableGroup* GetColGroup(GemTypeID id); // returns the Collidable Group for a given type id

	template <typename C1, typename C2>
	void SetCollisionPair()
	{
		// fetch the two Collidable Groups associated with ID's for C1 and C2
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];
		CollidableGroup* pg2 = ColGroupCollection[GetTypeID<C2>()];

		// create a Collision Dispatch for this pair of types
		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		// a new test is added to the manager's test collection
		colTestCommands.push_back(new CollisionTestPairCommand(pg1, pg2, pDispatch));
	}

	template <typename C>
	void SetCollisionSelf()
	{
		// fetch the Collidable Group associated with the ID for C
		CollidableGroup* pg = ColGroupCollection[GetTypeID<C>()];

		// create a CollisionDispatch for this type
		CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();

		// add a new test to the manager's test collection
		colTestCommands.push_back(new CollisionTestSelfCommand(pg, pDispatch));
		
	}

	void ProcessCollisions();

};


#endif CollisionManager_
