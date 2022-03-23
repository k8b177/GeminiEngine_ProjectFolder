#include "CollisionTestPairCommand.h"

#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "Collidable.h"
#include "GeminiMathTools.h"
#include "Visualizer.h"
#include "Colors.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd)
	:pG1(g1), pG2(g2), pDispatch(pd)
{}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	// delete the Collision Dispatch
	delete pDispatch;
}

void CollisionTestPairCommand::Execute()
{
	// get the Collidable Collection from each Collision Group --> give me a list all of the Collidables for both of these groups
	const CollidableGroup::CollidableCollection& Collection1 = pG1->GetColliderCollection();
	const CollidableGroup::CollidableCollection& Collection2 = pG2->GetColliderCollection();

	// Test all the pairs between both lists (for this quarter - no optimizations)
	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		const CollisionVolumeBSphere& bs1 = (*it1)->GetBSphere();

		for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
		{
			const CollisionVolumeBSphere& bs2 = (*it2)->GetBSphere();

			if (GeminiMathTools::Intersect(bs1, bs2) )
			{
				pDispatch->ProcessCallbacks(*it1, *it2);

				//Visualizer::SubmitBSphereVisualization(bs1, Colors::Red);
				//Visualizer::SubmitBSphereVisualization(bs2, Colors::Red);
			}
			else
			{
				//Visualizer::SubmitBSphereVisualization(bs1, Colors::Blue);
				//Visualizer::SubmitBSphereVisualization(bs2, Colors::Blue);
			}
		}
	}
}