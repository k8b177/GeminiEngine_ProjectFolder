#ifndef VisualizerAttorney_
#define VisualizerAttorney_

#include "Visualizer.h"

class VisualizeBSphereCommand;

class VisualizerAttorney
{
	// ---- BIG FOUR ---- //
	VisualizerAttorney() = default;
	VisualizerAttorney(const VisualizerAttorney&) = delete;
	VisualizerAttorney& operator= (const VisualizerAttorney&) = delete;
	~VisualizerAttorney() = default;

public:
	class GeminiAccess
	{
		friend class Gemini;
	private:
		static void Delete() { Visualizer::Delete(); }
		static void VisualizeAll() { Visualizer::VisualizeAll(); }
	};

	class CommandAccess
	{
		friend class VisualizeBSphereCommand;

	private:
		static void ShowBSphere(Vect center, float radius, const Vect color) { Visualizer::ShowBSphere(center, radius, color); }
		static void RecycleBSphereCmd(VisualizeBSphereCommand* cmd) { Visualizer::RecycleBSphereCmd(cmd); }
	};

};

#endif VisualizerAttorney_
