
#ifndef CollisionVolumeBSphere_
#define CollisionVolumeBSphere_

#include "CollisionVolume.h"
#include "Vect.h"

class Model;
class Matrix;
class CollisionVolumeBSphere;

class CollisionVolumeBSphere : public CollisionVolume
{
private:
	Vect Center;
	float Radius;

public:
	// ---- BIG FOUR ---- //
	CollisionVolumeBSphere() = default;
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = delete;
	CollisionVolumeBSphere& operator= (const CollisionVolumeBSphere&) = delete;
	~CollisionVolumeBSphere() = default;

	void ComputeData(Model* mod, const Matrix& mat);
	const Vect& GetCenter() const;
	float GetRadius() const;
	bool Intersect(const CollisionVolume& other);
	bool Intersect(const CollisionVolumeBSphere& other);


};

#endif CollisionVolumeBSphere_
