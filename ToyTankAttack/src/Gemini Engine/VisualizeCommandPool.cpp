#include "VisualizeCommandPool.h"

#include "VisualizeBSphereCommand.h"

VisualizeBSphereCommand* VisualizeCommandPool::GetBSphereCmd()
{
	VisualizeBSphereCommand* cmd;

	if (recycledBSphereCmds.empty())
	{
		cmd = new VisualizeBSphereCommand();
	}
	else
	{
		cmd = recycledBSphereCmds.top();
		recycledBSphereCmds.pop();
	}

	return cmd;
}

void VisualizeCommandPool::ReturnBSphereCmd(VisualizeBSphereCommand* cmd)
{
	recycledBSphereCmds.push(cmd);
}

VisualizeCommandPool::~VisualizeCommandPool()
{
	// forcefully delele all recycled commands
	while (!recycledBSphereCmds.empty())
	{
		delete recycledBSphereCmds.top();
		recycledBSphereCmds.pop();
	}
}