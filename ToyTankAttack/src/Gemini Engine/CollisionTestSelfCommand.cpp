#include "CollisionTestSelfCommand.h"

#include "CollisionDispatchBase.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "GeminiMathTools.h"
#include "Visualizer.h"
#include "Colors.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd)
	:pG(g), pDispatch(pd)
{}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete pDispatch;
}

void CollisionTestSelfCommand::Execute()
{
	// get the Collidable Collection from each Collision Group --> give me a list all of the Collidables for both of these groups
	const CollidableGroup::CollidableCollection& Collection1 = pG->GetColliderCollection();


	// Test all the pairs within the list (for this quarter - no optimizations
	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		const CollisionVolumeBSphere& bs1 = (*it1)->GetBSphere();

		for (auto it2 = --Collection1.end(); it2 != it1; it2--)
		{
			const CollisionVolumeBSphere& bs2 = (*it2)->GetBSphere();

			if (GeminiMathTools::Intersect(bs1, bs2))
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