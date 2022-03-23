#ifndef GeminiMathTools_
#define GeminiMathTools_

class CollisionVolumeBSphere;

class GeminiMathTools // stateless class, only math functions
{
public:
	// ---- BIG FOUR ---- //
	GeminiMathTools() = default;
	GeminiMathTools(const GeminiMathTools&) = delete;
	GeminiMathTools& operator= (const GeminiMathTools&) = delete;
	~GeminiMathTools() = default;

	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);

};

#endif GeminiMathTools_
