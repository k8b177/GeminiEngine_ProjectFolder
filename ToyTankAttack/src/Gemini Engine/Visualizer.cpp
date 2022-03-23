#include "Visualizer.h"

#include "GraphicsObject_WireframeConstantColor.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Colors.h"
#include "VisualizeBSphereCommand.h"
#include "CollisionVolumeBSphere.h"

#include "SceneManager.h"
#include "Scene.h"

Visualizer* Visualizer::ptrInstance = nullptr;

// initialize default color
Vect Visualizer::DEFAULT_COLOR = Colors::Blue;

Visualizer& Visualizer::Instance()
{
	if (!ptrInstance)
		ptrInstance = new Visualizer();
	return *ptrInstance;
}

Visualizer::Visualizer()
{
	// create Wireframe Sphere Model
	WUnitSphere = new GraphicsObject_WireframeConstantColor(
					ModelManager::Get("Sphere"), ShaderManager::Get("ColorConstant"), DEFAULT_COLOR);
}

void Visualizer::SubmitBSphereVisualization(const CollisionVolumeBSphere& s, const Vect& col)
{
	// Get a VisBSphereCommand from the object pool
	VisualizeBSphereCommand* cmd = Instance().myCmdPool.GetBSphereCmd();

	// Initialize the VisCommand with the right info: center, radius, and color
	cmd->Initialize(s.GetCenter(), s.GetRadius(), col);

	// Add the VisCommand of to the list of commands for this frame
	Instance().lstCommands.push_back(cmd);
}

void Visualizer::ShowBSphere(Vect center, float radius, const Vect& col = DEFAULT_COLOR)
{
	// create Transform matrix for Wireframe Sphere based on BSphere's center and radius
	Matrix worldBS = Matrix(SCALE, radius, radius, radius) * Matrix(TRANS, center);

	// call private method to place the one Wireframe Sphere
	Instance().privRenderBSphere(worldBS, col);
}

void Visualizer::privRenderBSphere(Matrix& S, const Vect& col)
{
	// set color of Wireframe Sphere
	this->WUnitSphere->SetColor(col);
	// set world matrix of Wireframe Sphere
	this->WUnitSphere->SetWorld(S);
	// render sphere
	this->WUnitSphere->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Visualizer::Delete()
{
	delete Instance().WUnitSphere;

	delete ptrInstance;
}

void Visualizer::RecycleBSphereCmd(VisualizeBSphereCommand* cmd)
{
	Instance().myCmdPool.ReturnBSphereCmd(cmd);
}


void Visualizer::privVisualizeAll()
{
	// loop through all of the visualize commands accumulated within the last frame and execute them
	for (VisualizeCommandBase* cmd : lstCommands)
	{
		cmd->Execute();
		cmd->Recycle();
	}

	lstCommands.clear();
}
