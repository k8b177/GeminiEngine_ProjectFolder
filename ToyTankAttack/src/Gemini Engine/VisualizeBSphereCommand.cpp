#include "VisualizeBSphereCommand.h"

#include "VisualizerAttorney.h"


void VisualizeBSphereCommand::Execute()
{
	VisualizerAttorney::CommandAccess::ShowBSphere(Center, Radius, Color);
}

void VisualizeBSphereCommand::Initialize(Vect center, float radius, Vect color)
{
	this->Center = center;
	this->Radius = radius;
	this->Color = color;
}

void VisualizeBSphereCommand::Recycle()
{
	VisualizerAttorney::CommandAccess::RecycleBSphereCmd(this);
}

