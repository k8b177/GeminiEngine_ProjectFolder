#include "CollisionVolumeBSphere.h"

#include "Matrix.h"
#include "Model.h"


void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{
	this->Center = mod->getCenter() * mat;

	float scalingFactor = mat.get(ROW_0).mag(); // scaling factor is magnitude of first row
	
	this->Radius = mod->getRadius()* scalingFactor;

}

const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return Center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return Radius;
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolume& other)
{
	other.~CollisionVolume(); // to get rid of warning, remove later
	return true;
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeBSphere& other)
{
	other.~CollisionVolumeBSphere (); // to get rid of warning, remove later
	return true;
}