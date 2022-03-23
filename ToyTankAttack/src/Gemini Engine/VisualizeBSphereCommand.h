#ifndef VisualizeBSphereCommand_
#define VisualizeBSphereCommand_

#include "VisualizeCommandBase.h"
#include "Vect.h"

class CollisionVolumeBSphere;

class VisualizeBSphereCommand : public VisualizeCommandBase
{
private:
	Vect Center;
	float Radius;
	Vect Color;

public:
	// ---- BIG FOUR ---- //
	VisualizeBSphereCommand() = default;
	VisualizeBSphereCommand(const VisualizeBSphereCommand&) = delete;
	VisualizeBSphereCommand& operator= (const VisualizeBSphereCommand&) = delete;
	~VisualizeBSphereCommand() = default;

	virtual void Execute() override;
	virtual void Initialize(Vect center, float radius, Vect color);
	virtual void Recycle() override;
};

#endif VisualizeBSphereCommand_