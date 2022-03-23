
#ifndef Visualizer_
#define Visualizer_

#include "Vect.h"
#include <list>
#include "VisualizeCommandPool.h"

class GraphicsObject_WireframeConstantColor;
class CollisionVolumeBSphere;
class VisualizeCommandBase;

class Visualizer
{
	/// \cond
	friend class VisualizerAttorney;
private:
	static Visualizer* ptrInstance;

	static Visualizer& Instance();
	static void Delete();
	static void VisualizeAll() { Instance().privVisualizeAll(); }

	static Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor* WUnitSphere;

	void privRenderBSphere(Matrix& S, const Vect& col);
	void privVisualizeAll();

	// list of visualize commands (gathered during one frame)
	using CommandList = std::list<VisualizeCommandBase*>;
	CommandList lstCommands;

	// visualize command pool
	VisualizeCommandPool myCmdPool;

	// ---- BIG FOUR ---- //
	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator= (const Visualizer&) = delete;
	~Visualizer() = default;

	static void ShowBSphere(Vect center, float radius, const Vect& col);
	static void RecycleBSphereCmd(VisualizeBSphereCommand* cmd);
	/// \endcond

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void Visualizer::SubmitBSphereVisualization(const CollisionVolumeBSphere& s, const Vect& col);
	/// 
	/// \brief	Requests a Bounding Sphere tp be visualized.
	///
	/// \param 	s  	The CollisionVolumeBSphere you want to show.
	/// \param 	col	The desired color of the BSphere, as a RBGA Vect.
	/// 			
	/// \par Example
	/// 	In the following example, Frigate is a GameObject that has been set up for
	/// 	Collision. The user wants to view the Bounding Sphere as the Frigate moves
	///		around to they can easily check for collisions.
	/// 
	/// \code
	/// Frigate::Update()
	/// {
	/// 	Visualizer::SubmitBSphereVisualization(GetBSphere(), Colors::Blue);
	/// 
	/// 	// More Update code for movement...
	/// }
	/// \endcode
	/// 
	/// \note
	/// 	  1. You must include the "Visualizer.h" header to access the Visualizer  
	/// 	  2. Include the "Colors.h" header to access the Colors Enumerator that contains the RBG color vectors for many common colors.
	/// 	
	///-------------------------------------------------------------------------------------------------
	static void SubmitBSphereVisualization(const CollisionVolumeBSphere& s, const Vect& col);

};

#endif Visualizer_
