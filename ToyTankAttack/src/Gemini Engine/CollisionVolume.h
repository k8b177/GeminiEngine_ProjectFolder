
#ifndef CollisionVolume_
#define CollisionVolume_


class Model;
class Matrix;
class CollisionVolumeBSphere;

class CollisionVolume
{
public:
	// ---- BIG FOUR ---- //
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = delete;
	CollisionVolume& operator= (const CollisionVolume&) = delete;
	~CollisionVolume() = default;

	virtual void ComputeData(Model* mod, const Matrix& mat) = 0;
	virtual bool Intersect(const CollisionVolume& other) = 0;
	virtual bool Intersect(const CollisionVolumeBSphere& other) = 0;

};

#endif CollisionVolume_
