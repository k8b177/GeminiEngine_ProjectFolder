#include "GeminiMathTools.h"

#include "Vect.h"
#include "CollisionVolumeBSphere.h"

bool GeminiMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
{
	// Get the distance between the BSpheres, squared
	float d2 = (B.GetCenter()-A.GetCenter()).magSqr();

	// Get the sum of the radii, squared
	float sum = A.GetRadius() + B.GetRadius();
	sum *= sum;

	// If sum of the radii (squared) is less than distance (squared), no intersection
	if (sum < d2)
		return false;
	// else, intersection
	else
		return true;
}