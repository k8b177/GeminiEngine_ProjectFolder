#ifndef VisualizeCommandPool_
#define VisualizeCommandPool_

#include <stack>

class VisualizeBSphereCommand;

class VisualizeCommandPool
{
private:
	std::stack<VisualizeBSphereCommand*> recycledBSphereCmds;

public:
	VisualizeCommandPool() = default;
	VisualizeCommandPool(const VisualizeCommandPool&) = delete;
	VisualizeCommandPool& operator=(const VisualizeCommandPool&) = delete;
	~VisualizeCommandPool();

	VisualizeBSphereCommand* GetBSphereCmd();

	void ReturnBSphereCmd(VisualizeBSphereCommand* cmd);
};


#endif VisualizeCommandPool_
