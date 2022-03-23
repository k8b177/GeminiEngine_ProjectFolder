///-------------------------------------------------------------------------------------------------
// DoxygenData.h
///-------------------------------------------------------------------------------------------------

// -------------- Getting Started Module ---------------------//
/// \defgroup GETTING_STARTED Getting Started
/// 
/// \brief The very basics - how to get your first scene up and running
/// 
/// \par
/// Follow the Modules above in order to get your first scene running.
/// 
/// \defgroup GAME_INITIALIZATION Game Initialization
/// \ingroup GETTING_STARTED
/// \brief How to initialize the game.
/// 		 
///	\section SEC1 Step 1: Game Initialization
///		First, you must initialize the game by setting up the game window in Gemini::GameInitialize().
///		
///		\code
///		void Gemini::GameInitialize()
///		{
///			// Game Window Device setup
///			Gemini::SetWindowName("My First Scene");
///			Gemini::SetWidthHeight(800, 600);
///			Gemini::SetClear(0.4f, 0.4f, 0.8f, 1.0f);
///
///			// Use this area, for one time non-graphic creation
///			// ...
///		}
///		\endcode
///	
///	\defgroup LOADING_RESOURCES Loading Resources
///	\ingroup GETTING_STARTED
///	\brief How to load external resources.
///			 
///	\section SEC2 Step 2: Loading Resources
///			 Next, you must load all the external resources required for your scene.
///				\note All the code snippets in this step (\ref SEC2) are in Gemini::LoadResources();
///				
///		\subsection SEC2-1 2.1 Models
///				Load models with the ModelManager.
///				\code
///				{
///					ModelManager::Load("Frigate", "space_frigate.azul");
///					ModelManager::Load("Plane", "Plane.azul");
///				}
///				\endcode 
///					\note Models must be in .azul format OR use Models::PreMadeModels for basic geometries.
///		\subsection SEC2-2 2.2 Textures
///				Load textures with the TextureManager.
///				\code 
///				{
///					TextureManager::Load("SpaceFrigateTex", "space_frigate.tga");
///					TextureManager::Load("GridTex", "grid.tga");
///				}
///				\endcode
///					\note Textures must be in .tga format
///		\subsection SEC2-3 2.3 Shaders
///				Load shaders with the ShaderManager.
///				\code
///				{
///					ShaderManager::Load("TextureLight", "textureLightRender");
///					ShaderManager::Load("TextureFlat", "textureFlatRender");
///				}
///				\endcode
///						
///	\defgroup SCENE_SETUP Scene Setup
///	\ingroup GETTING_STARTED
///	\brief How to set up a scene.
///				  
///	\section SEC3 Step 3: Setting Up your Scene
///			 Next, you need to create your scene class and set it to be the starting scene.
///			 
///		\subsection SEC3-1 3.1 Creating your Scene Class
///				Your scene class must derive from the Scene base class.  It should implement two virtual functions
///				(1) Scene::Initialize() and (2) Scene::SceneEnd();
///				
///				\par Example Scene Class, MyFirstScene
///					 
///				\code
///				#include "../Gemini Engine/Scene.h"
///
///				class Frigate;
///				class WorldPlane;
///
///				class MyFirstScene : public Scene
///				{
///				public:
///					virtual void Initialize()
///					{
///						GOFrig = new Frigate();
///						GOPlane = new WorldPlane();
///					}
///					
///					virtual void SceneEnd()
///					{
///						delete GOFrig;
///						delete GOPlane;
///					}
///
///				private:
///					Frigate* GOFrig;
///					WorldPlane* GOPlane;
///				};
///
///				\endcode
///						
///				\note Frigate and WorldPlane are GameObject 's.  See \ref SEC4 .
///		 
///					
///		\subsection SEC3-2 3.2 Set your New Scene Class as the Starting Scene
///				You must tell the engine what your starting scene is.  This should be done in Gemini::LoadResources()
///				using SceneManager::SetNextScene(Scene*).
///				
///				\par Example
///					 
///				\code
///				void Gemini::LoadResources()
///				{
///					// Load resources using ModelManager, TextureManager, etc.
///					
///					// Set the Start Scene
///					Scene* demoScene = new MyFirstScene();
///					SceneManager::SetNextScene(demoScene);
///				}
///				\endcode
///					
///	\defgroup CREATING_GAMEOBJECTS Creating Game Objects
///	\ingroup GETTING_STARTED
///	\brief How to create game objects.
///		   
///	\section SEC4 Step 4: Creating Game Objects
///			 Next, you need to create game objects to act in your scene.
///			 
///		\note What the heck even is a Game Object?? See more information <here>
///			 
///		\subsection SEC4-1 4.1 Writing Your Game Object Classes
///				\par
///				Your game object classes must derive from the GameObject base class.  It should implement virtual functions from the base class based on the properties that this particular game object needs.
///				See \ref GAMEOBJECT_EVENTS for the list of events a GameObject can implement.
///				
///				\par 
///				For this first example, we will only deal with 2 events, Updatable::Update() and Drawable::Draw().
///	
///				\par Example GameObject Class, Frigate
///
///				\code
///				#include "../Gemini Engine/GameObject.h"
///				#include "Matrix.h"
///
///				class GraphicsObject_TextureLight;
///
///				class Frigate : public GameObject
///				{
///				private:
///					// Graphics Object for Frigate
///					GraphicsObject_TextureLight* pGObjLT;
///
///					// Matrices to control Frigate movement
///					Matrix ShipScale;
///					Matrix ShipRotTrans;
///
///					// Constants used for Frigate movement
///					const float ShipTransSpeed = 1;
///					const float ShipRotAng = .05f;
///				
///				
///				public:
///					// implementation of Update and Draw properties of GameObject
///					virtual void Update()
///					{
///						// Ship Rotation movement
///						if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
///						{
///							ShipRotTrans = Matrix(ROT_Y, ShipRotAng) * ShipRotTrans;
///						}
///						else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
///						{
///							ShipRotTrans = Matrix(ROT_Y, -ShipRotAng) * ShipRotTrans;
///						}
///
///						// Ship translation movement
///						if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
///						{
///							ShipRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * ShipRotTrans;
///						}
///						else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
///						{
///							ShipRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * ShipRotTrans;
///						}
///
///						// Spaceship adjust matrix
///						Matrix world = ShipScale * ShipRotTrans;
///						// Update the world information of the graphics object
///						pGObjLT->SetWorld(world);
///					}
///				
///					virtual void Draw()
///					{
///						// render the graphics object to the scene's current camera
///						pGObjLT->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
///					}
///
///				};
///				\endcode
///
///		\subsection SEC4-2 4.2 Submitting GameObject Events for Registration
///			\par
///			The virtual methods implemented in your GameObject classes (such as Updatable::Update()and Drawable::Draw()
///			will never be called unless you submit for registration. We must register the Frigate as an Updatable
///			and a Drawable.  See \ref GAMEOBJECT_EVENTS for more details.
///			
///			\par Example:
///				 
///			\code
///			Frigate::Frigate()
///			{
///				// Set up everything for the Frigate object (creating graphics object and initialzing matrices)
///				// ... 
///				
///				// Submit for Update Registration
///				Updatable::SubmitUpdateRegistration();
///				
///				// Submit for Draw Registration
///				Drawable::SubmitDrawRegistration();
///			}
///			\endcode
///					
///		   
///		\subsection SEC4-3 4.3 Creating instances of your GameObjects in Your Scene
///			\par
///			Finally, you need to actually create instances of your GameObjects.  Any objects that should
///			exist at the start of your scene should be created in Scene::Initialize().
///			
///			\par Example, MyFirstScene class
///				 
///			See \ref SEC3-1 for the full definition of MyFirstScene.
///				 
///			\code
///			void MyFirstScene::Initialize()
///			{
///				// Context:
///				//	- GOFrig is type Frigate*
///				//	- GOPlane is type Plane*
///				
///				GOFrig = new Frigate();
///				GOPlane = new WorldPlane();
///			}
///			\endcode
///					
///					
///		\section SEC5 Congrats! You're done with your first scene!
///					
///		\par
///			At this point, run your game and you should have a basic Scene with GameObject 's that can Update() and Draw().
///			
///		\par 
///			 Explore other Modules to learn how to build more features.
///		
///		
/// \defgroup GAMEOBJECT_INFO Guide to Game Objects
/// \brief Learn about what a GameObject is and what kinds of things you can do with it
/// 	   
/// \defgroup WHAT_IS_A_GAMEOBJECT What is a Game Object?
/// \ingroup GAMEOBJECT_INFO 
/// \brief Explanation for what a GameObject is according to GeminiEngine.
///	 
///	\section GAMEOBJECT_EXPLAINED "GameObject", explained.
///
///	\par 
///		 GameObject 's are the building blocks of your game.  GameObject 's exist inside Scene 's
///		 and interact with each other in different ways to create gameplay.
/// 
///	\par
///		In the GeminiEngine, the GameObject class is derived from different <X>-able classes.
///		(Updatable, Drawable, Inputable, etc.).  These base classes each provide a different events
///		the GameObject can use to do things in the Scene. See \ref GAMEOBJECT_EVENTS .
///
///	\note
///		A GameObject does not need to be a visible character or actor in the scene.  
///		For instance, an \b EnemySpawner or \b InventoryManager would not have graphical representations but may
///		need to implement \b Update or \b KeyPress events to control gameplay.
/// 
///		 
///	\defgroup GAMEOBJECT_EVENTS GameObject Events
///	\ingroup GAMEOBJECT_INFO
///	\brief An overview of the different events a GameObject can implement.
///		   
///	\par
///		Your GameObject 's must implement different events to create gameplay.
///		GameObject 's must \b Register and \b Deregister for these events.
///		
///	\section EVENT_LIST Below is a list of events GameObject 's can implement:
///		- \ref UPDATE_EVENT  
///		- \ref DRAW_EVENT
///		- \ref ALARM_EVENT 
///		- \ref INPUT_EVENT
///		- \ref COLLISION_EVENT  
///	
///	\defgroup UPDATE_EVENT Update
///	\ingroup GAMEOBJECT_EVENTS
///	\brief Update event, explained
///			 
///	\section UPDATE_DESCRIPTION  What is Update?
///	\par 
///		 Code put inside Updatable::Update() will be called every frame of the game. 
///	
///	\n
///	  
///	\section UPDATE_REGISTRATION How to Register/Deregister for Update?
///	\par
///		Code inside Updatable::Update() will only be called if the GameObject has registered for the \b Update event.
///		When a GameObject submits for \b Update registration, it is added to the list of GameObject 's Updated every frame.
///		
///	\par
///		You can also \b Deregister a GameObject for Update if you want to remove it from the list of GameObject 's Updated every frame.
///		
///	\par Registration Example:
///		In the following example, the Frigate GameObject registers for \b Update in the constructor, since the user
///		want the Frigate to Update every frame from the start of the scene.
///		
///		\code
///		Frigate::Frigate()
///		 {
///			// Set up everything for the Frigate object (creating graphics object and initialzing matrices)
///			// ...
///		
///			// Submit for Update Registration
///			Updatable::SubmitUpdateRegistration();
///		 }
///		\endcode
///				
///	\par Deregistration Example:
///		In the following example, when a Bullet leaves the scene, it should deregister from \b Update.
///
///		\code
///		void Bullet::SceneExit()
///		{
///			Updatable::SubmitUpdateDeregistration();
///			
///			// Do the other cleanup for the Bullet
///			// ...
///		}
///		\endcode
///				
///	\n
///			
///	\section UPDATE_EXAMPLE Update Event Implementation Example.
///		In this example, Frigate is a GameObject.  Since the Frigate has called Updatable::SubmitUpdateRegistration(),
///		the code in Update will be run every frame.
///			 
///		\code
///		void Frigate::Update()
///		{
///			// Ship Rotation movement
///			if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
///			{
///			    ShipRotTrans = Matrix(ROT_Y, ShipRotAng) * ShipRotTrans;
///			}
///			else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
///			{
///			    ShipRotTrans = Matrix(ROT_Y, -ShipRotAng) * ShipRotTrans;
///			}
///
///			// Ship translation movement
///			if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
///			{
///			    ShipRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * ShipRotTrans;
///			}
///			else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
///			{
///			    ShipRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * ShipRotTrans;
///			}
///
///			// Spaceship adjust matrix
///			Matrix world = ShipScale * ShipRotTrans;
///			// Update the world information of the graphics object
///			pGObjLT->SetWorld(world);
///		}
///		\endcode
///							
///	\defgroup DRAW_EVENT Draw
///	\ingroup GAMEOBJECT_EVENTS
///	\brief Draw event, explained.
///		   
///	\section DRAW_DESCRIPTION What is Draw?
///	\par 
///		 Code put inside Drawable::Draw() will be called every frame of the game AFTER all GameObject 's have been \b Updated.
///		 Code inside the Draw() method should almost exclusively be for rendering Graphics Objects.  Avoid other computations here.
///		 
///	\note
///		 2D GeminiSprite Objects should NOT be rendered Drawable::Draw().  
///		 To ensure that 2D objects are rendered AFTER all 3D objects, render GeminiSprite's in Drawable::Draw2D().
///	
///	\n
///	
///	\section DRAW_REGISTRATION How to Register/Deregister for Draw?
///	\par
///		Code inside Drawable::Draw() will only be called if the GameObject has registered for the \b Draw event.
///		When a GameObject submits for \b Draw registration, it is added to the list of GameObject 's Drawn every frame.
///		
///	\par
///		You can also \b Deregister a GameObject for Draw if you want to remove it from the list of GameObject 's Drawn every frame.
///		
///	\par Registration Example:
///		In the following example, the Frigate GameObject registers for \b Draw in the constructor, since the user
///		want the Frigate to Draw every frame from the start of the scene.
///		
///		\code
///		Frigate::Frigate()
///		 {
///			// Set up everything for the Frigate object (creating graphics object and initialzing matrices)
///			// ...
///		
///			// Submit for Draw Registration
///			Drawable::SubmitDrawRegistration();
///		 }
///		\endcode
///				
///	\par Deregistration Example:
///		In the following example, when a Bullet leaves the scene, it should deregister from \b Draw.
///
///		\code
///		void Bullet::SceneExit()
///		{
///			Drawable::SubmitDrawDeregistration();
///			
///			// Do the other cleanup for the Bullet
///			// ...
///		}
///		\endcode
///				
///	\n
///			
///	\section DRAW_EXAMPLE Draw Event Implementation Example.
///		In this example, Frigate is a GameObject.  Since the Frigate has called Drawable::SubmitDrawRegistration(),
///		the code in Draw will be run every frame.
///			 
///		\code
///		void Frigate::Draw()
///		{
///			// Context:
///			// - pGObjLT is type GraphicsObject_TextureLight*
///			
///			pGObjLT->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
///		}
///		\endcode
///		
///	\defgroup ALARM_EVENT Alarms
///	\ingroup GAMEOBJECT_EVENTS
///	\brief Alarm events, explained.
///
///	\section ALARM_DESCRIPTION What is an Alarm?
///	\par
///		 Each GameObject can register for up to 3 \b Alarms.  
///		 The code inside Alarmable::Alarm0(), Alarmable::Alarm1(), or Alarmable::Alarm2(),  will be called at the time specified by the user.
///
/// \n
///   
///	\section ALARM_REGISTRATION How to Register/Deregister for an Alarm?
///	\par
///		When a GameObject submits for an \b Alarm \b Registration, the user must specify two things:
///		1. Which Alarm is being registered?  (Use AlarmableManager::ALARM_ID)
///		2. How far in the future should the alarm go off? (in seconds)
///
///	\par
///		You can also \b Deregister an \b Alarm if you want to turn off the Alarm.
///
///	\par Registration Example:
///		In the following example, the Frigate GameObject registers for \b Alarm0 in the constructor.
///		The \b Frigate's Alarm0 method will be called 5 seconds after the Frigate is created.
///
///		\code
///		Frigate::Frigate()
///		 {
///			// Submit for Alarm Registration
///			Alarmable::SubmitAlarmRegistration(5.0f, AlarmableManager::ALARM_ID::ALARM_0);
///		 }
///		\endcode
///
///	\par Deregistration Example:
///		In the following example, the Frigate Deregisters for \b Alarm0 when the T Key is Pressed.
///
///		\code
///		void Frigate::KeyPressed(AZUL_KEY k)
///		{
///			if (k == AZUL_KEY::KEY_T)
///				Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
///		}
///		\endcode
///				
///	\n
///
///	\section ALARM_EXAMPLE Alarm Event Implementation Example.
///		When the time specified by the user in the \b Alarm0 registration passes, the code in \b Alarm0 will be called.
///
///		\code
///		void Frigate::Alarm0()
///		{
///			// When the alarm goes off, the Frigate will "become invisible"
///			Drawable::SubmitDrawDeregistration(); // frigate will not draw anymore
///		}
///		\endcode
///				
///	\note
///		 To repeat an alarm, simply re-register the Alarm inside the Alarm callback.
///		 Example:
///		 
///		\code
///		void Frigate::Alarm0()
///		{
///			// When the alarm goes off, the Frigate's health will decrease by 0.1;
///			this->health -= 0.1f;
///			
///			//THEN, the alarm is reset - it will trigger again after 5 seconds
///			Alarmable::SubmitAlarmRegistration(5.0f, AlarmableManager::ALARM_ID::ALARM_0);
///		}
///		\endcode
///				
///
/// \defgroup INPUT_EVENT KeyPress/KeyRelease
///	\ingroup GAMEOBJECT_EVENTS
///	\brief Keyboard Input events, explained.
///
///	\section INPUT_DESCRIPTION What is a KeyPress/ KeyRelease?
///	\par
///		 Each GameObject can register to watch for Key Events. 
///		 A Key Event is a KeyPress or a KeyRelease for a certain Key on the keyboard.
///		 When that key is pressed or released, the code inside Inputable::KeyPressed(AZUL_KEY k) or Inputable::KeyReleased(AZUL_KEY k) will be called.
///		
///	\n
///	  
///	\section INPUT_REGISTRATION How to Register/Deregister for a KeyPress/ KeyRelease?
///	\par
///		When a GameObject submits for an \b Key \b Registration, the user must specify two things:
///		1. Which Key does the object care about?  (Use AZUL_KEY)
///		2. Does it want to watch for a KeyPress or a KeyRelease? (Use EVENT_TYPE::KEY_PRESS or EVENT_TYPE::KEY_RELEASE)
///
///	\par
///		You can also submit a \b Key \b Deregistration if you no longer wish to watch for a Key Event.
///		Once again, you must specify the Key and the EventType for which you are deregistering.
///
///	\par Registration Example:
///		In the following example, the Frigate GameObject registers for \b T \b KeyPress and \b T \b KeyRelease in the constructor.
///
///		\code
///		Frigate::Frigate()
///		 {
///			// Submit for Key Registration
///			// T, Press
///			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_PRESS);
///			// T, Release
///			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_RELEASE);
///		 }
///		\endcode
///
///	\par Deregistration Example:
///		In the following example, the Frigate Deregisters for \b T \b KeyPress and \b T \b KeyRelease when \b Alarm0 goes off.
///		The Frigate will no longer react when the T key is pressed or released.
///
///		\code
///		void Frigate::Alarm0(AZUL_KEY k)
///		{
///			// Submit for Key Deregistration
///			// T, Press
///			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_PRESS);
///			// T, Release
///			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_RELEASE);
///		}
///		\endcode
///				
///	\n
///
///	\section INPUT_EXAMPLE KeyPress/ KeyRelease Implementation Example.
///		When the T key is pressed, \b KeyPressed(AZUL_KEY k) will be called with AZUL_KEY::KEY_T as the parameter value.
///
///		\code
///		void Frigate::KeyPressed(AZUL_KEY k)
///		{
///			// When the T key is pressed, the message will print
///			if (k == AZUL_KEY::KEY_T)
///				DebugMsg::out("Frigate: T Key Pressed\n");
///		}
///		\endcode
///		
///		When the T key is released, \b KeyReleased(AZUL_KEY k) will be called with AZUL_KEY::KEY_T as the parameter value.
///		
///		\code
///		void Frigate::KeyReleased(AZUL_KEY k)
///		{
///			// When the T key is released, the message will print
///			if (k == AZUL_KEY::KEY_T)
///				DebugMsg::out("Frigate: T Key Released\n");
///		}
///		\endcode
///				
///	\note
///		 When Inputable::KeyPressed(AZUL_KEY k) or Inputable::KeyReleased(AZUL_KEY k) is called,
///		 GeminiEngine passes back the key as a parameter.
///		 So, it is on the user to check which key this is and respond appropriately.
///		 (Suggestion: use \b if/elseif logic or a \b switch statement)
///		 
///				
///	\defgroup COLLISION_EVENT Collision
///	\ingroup GAMEOBJECT_EVENTS
///	\brief Collision events, explained.
///
///	\section COLLISION_DESCRIPTION What is a Collision?
///	\par
///		 Each GameObject can register to watch for \b Collisions with other GameObjects of a certain type.
///		 GameObject 's are assigned \b Collider \b Models and if the model intersects with another GameObject 's \b Collider \b Model, an event callback can be triggered.
///
/// \n 
///    
///	\section COLLISION_REGISTRATION How to Set Up a Collision?
///	\par
///		Collision Events require more setup and maintenance than other GameObject events.  
///		The steps below outline the steps you need to take to detect Collisions between GameObject 's.
///		
///	\n
///	  
///	\subsection COLLISION_REGISTRATION_SETCOLLISIONPAIRSELF Step 1: Tell Scene to Watch for Certain Collisions
///				You must tell your Scene which kinds of Collisions you care about detecting.
///				In the Scene class, there are two templatized methods you can use to do this where you specify which GameObject 's you care about colliding:
///					1. Scene::SetCollisionPair() : specify two kinds of GameObject's - you want to trigger a callback when these two types collide
///					2. Scene::SetCollisionSelf() : specify one kind of GameObject - you want to trigger a callback when an object of this type collides with another object of this type
///				
///	\par SetCollisionPair Example
///		 In the following example, \b MainScene is a Scene that wants to watch for \b Bullet - \b Enemy collisions.
///		 
///		\code
///		void MainScene::Initialize()
///		{
///			// Creating GameObjects in the scene
///			// ...
///
///			// Bullet and Enemy are user-defined GameObject types 
///			SetCollisionPair<Bullet, Enemy>();
///		}
///		\endcode
///				
///	\par SetCollisionSelf Example
///		 In the following example, \b MainScene is a Scene that wants to watch for \b Enemy - \b Enemy collisions.
///
///		\code
///		void MainScene::Initialize()
///		{
///			// Creating GameObjects in the scene
///			// ...
///
///			// Enemy is a user-defined GameObject type
///			SetCollisionSelf<Enemy>();
///		}
///		\endcode
///				
///	\n
///				
///	\subsection COLLISION_REGISTRATION_SETCOLLIDERMODELS Step 2: Setting Collider Models for your Game Objects
///				If a GameObject is watching for a collision, you need to indicate which Model represents the GameObject.
///				A Bounding Geometry will be created for this Model.
///				You will be notified when the Bounding Geometry for this Model intersects with another Bounding Geometry associated with GameObject 's whose collision you care about.
///				
///	\par SetColliderModel Example:
///		 In the following example, Bullet is a GameObject getting ready for collisions.
///		 In its constructor, it creates a GraphicsObject and sets its model as the Collider Model.
///		 
///	\code
///	Bullet::Bullet()
///{
///		// Creating Graphics Object for the Bullet
///		// pGObj_Bullet is type GraphicsObject_TextureLight*
///		Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
///		Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
///		Texture* pBulletTex = TextureManager::Get("BulletTex");
///		pGObj_Bullet = new GraphicsObject_TextureLight(ModelManager::Get("Bullet"), ShaderManager::Get("TextureLight"), pBulletTex, pBulletTex, LightColor, LightPos);
///		
///		// Setting the colllider model 
///		// A Bounding Sphere that best respresents the model will be used for collision tests
///		Collidable::SetColliderModel(pGObj_Bullet->getModel());
/// }
///	\endcode
///				
///	\note
///		1. The current version of GeminiEngine only calculates Bounding Sphere collisions. GeminiEngine will approximate the best fitting Bounding Sphere to match the Model you set. The resulting collision tests are efficient but inaccurate. More Bounding Geometries will be available soon.  
///		2. You must set a \b Collider \b Model for every GameObject that wants to watch for collisions. (In the example for this module, namely setting up \b Bullet - \b Enemy collisions, you would also need to set a \b Collider \b Model for the \b Enemy GameObject.)			
///	
///	\n
///	  
///	\subsection COLLISION_REGISTRATION_SETCOLLIDABLEGROUP Step 3: Putting your Game Objects into Collidable Groups
///				If a GameObject is watching for collision, you also need to indicate which \b CollidableGroup it is associated with.
///				You must manually specify this for each of your GameObject 's.
///				
///	\par SetCollidableGroup Example:
///		 In the following example, the Scene wants to watch for \b Bullet - \b Enemy Collisions.
///		 You must specify that the \b Bullet GameObject is part of the \b Bullet \b CollidableGroup and the \b Enemy GameObject is part of the \b Enemy \b CollidableGroup.
///		 GeminiEngine will create these groups internally, you just need to specify which GameObject type the group is associated with.
///		 
///	\code
///	Bullet::Bullet()
///	{
///		// Other initialization
///		// ...
///		
///		// Set the Bullet to be part of the Bullet CollidableGroup
///		Collidable::SetCollidableGroup<Bullet>();	
///	}
///	
///	Enemy::Enemy()
///	{
///		// Other initialization
///		// ...
///		
///		// Set the Enemy to be part of the Enemy CollidableGroup
///		Collidable::SetCollidableGroup<Enemy>();
///	}
///	\endcode
///			
///	\note 
///		  Usually, the \b CollidableGroup type should match the GameObject 's type (\b Bullet is in the \b Bullet \b CollidableGroup, \b Enemy is in the \b Enemy \b CollidableGroup ).
///		  BUT there is nothing stopping you from putting a GameObject in a \b CollidableGroup that does not match its type.
///		  For instance, if you have more than one type of \b Enemy (a \b Wizard and an \b Elf), you could set their \b CollidableGroup to be the \b Enemy \b CollidableGroup.
///		  If other GameObject 's are watching for collisions with \b Enemies , then the callback will be triggered when they collide with a \b Wizard or an \b Elf .
///		  This kind of grouping could be helpful depending on your game's needs.
///		
///	\n
///	  
///	\subsection COLLISION_REGISTRATION_REGDEREG Step 4: Collision Registration and Deregistration	
///				For a GameObject to actively watch for collisions, it must submit a \b Collision \b Registration.
///				While registered for collision, collision callbacks for the object will be enabled.
///
///		You can also submit a \b Collision \b Deregistration if you no longer wish to watch for Collisions.
///		
///	\par Registration Example:
///		In the following example, the \b Bullet GameObject registers for Collision when it enters the Scene.
///
///		\code
///		void Bullet::SceneEntry()
///		{
///			Collidable::SubmitCollisionRegistration();
///		}
///		\endcode
///
///	\par Deregistration Example:
///		In the following example, the Bullet deregisters for Collision when it leaves the Scene.
///
///		\code
///		void Bullet::SceneExit()
///		{
///			Collidable::SubmitCollisionDeregistration();
///		}
///		\endcode
///				
///	\n
///	  
///	\subsection COLLISION_REGISTRATION_UPDATECOLLISIONDATA Step 5: Updating Collision Data
///				GeminiEngine does collision testing by using a Bounding Geometry for your GameObject.
///				When that Bounding Geometry intersects with another Bounding Geometry that you have specified to watch for, you get a collision callback.
///				You must tell GeminiEngine where the Bounding Geometry is at any given time of the game so that it can check for intersections every frame.
///			
///	\par	
///		This is where Collidable::UpdateCollisionData(const Matrix& mat) comes in.
///		You must call Collidable::UpdateCollisionData(const Matrix& mat) whenever your GameObject moves and pass in the world matrix of the GameObject.
///		This way GeminiEngine can adjust the Bounding Geometry appropriately and check for intersections.
///		
///	\par Example:
///		 In the following example, the \b Bullet is registered for collision.
///		 Whenever the \b Bullet 's transform changes during Update(), its Bounding Geometry transform also needs to be updated.
///		 
///	\code
///	void Bullet::Update()
///	{
///		// Adjusting the Bullet's World Matrix
///		BulletRotTrans = Matrix(TRANS, Vect(0, 0, BulletSpeed)) * BulletRotTrans; // go forward at constant speed
///		Matrix world = BulletScale * BulletRotTrans;
///		
///		// pGObj_Bullet is a Graphics Object representing the bullet (type GraphicsObject_TextureLight*)
///		// Updating the world matrix for the Graphics Object
///		pGObj_Bullet->SetWorld(world);
///		
///		// Updating the Bounding Geometry for the Bullet - passing in the Bullet's updated world matrix
///		// The Bounding Geometry will move in tandem with the Bullet
///		Collidable::UpdateCollisionData(world);
/// }
///	\endcode
///			
///	\note
///		 1. The current version of GeminiEngine uses Bounding Spheres exclusively for collision testing. UpdateCollisionData will adjust the sphere to match the world matrix you provide. More Bounding Geometries will be available soon.  
///		 2. If your GameObject does not move, you do not need to update the collision data every frame.  Call UpdateCollisionData once when you place the object in the world.
///		
///	\n
///	    
///	\subsection COLLISION_REGISTRATION_FINAL_STEP Now you are ready to implement the actual Colllision Callback.  See the Implementation example below.
///		
///	\n
///
///	\section COLLISION_EXAMPLE Collision Implementation Example.
///		In this example, the user has gone through all of the collision setup steps above to set up \b Bullet - \b Enemy Collisions.
///		When a \b Bullet collides with a \b Enemy, both of the following methods are executed.
///		
///		\code
///		// In Enemy.cpp
///		void Enemy::Collision(Bullet* b)
///		{
///			// Destroy the Bullet
///			b->GameObject::SubmitExit();
///			
///			// Lose health
///			health -= 0.5;
///			
///			// If health too low, Destroy
///			if (health <= 0)
///			{
///				GameObject::SubmitExit();
///			}
///		}
///		
///		//In Bullet.cpp
///		void Bullet::Collision(Enemy* e)
///		{
///			// Print Debug message
///			DebugMsg::out("Collision Bullet with Enemy KATE\n");
///		}
///		\endcode
///
/// \defgroup DEBUGGING_TOOLS Debugging Tools
/// \brief Learn about what Debugging Tools are available in GeminiEngine.
/// 	
/// \defgroup VISUALIZER Visualizer
/// \ingroup DEBUGGING_TOOLS
/// \brief How to use the visualizer to display geometries in your scene in real time.
///
/// \section VIS-1 What is the Visualizer?
///		The Visualizer displays different shapes, lines, and bounding volumes associated with
///		your GameObject 's.  GeminiEngine will update the visualizations every frame, which is helpful
///		for live debugging.
///
///		All Visualization requests are gathered during one frame and then executed.
///		You must request visualization every frame you want something to appear.
/// 
///  \n
///   
///	\section VIS-2 Visualization Tools
///		Here is the current list of visualizations available via the Visualizer:
///		- BSphere Visualization (Visualizer::SubmitBSphereVisualization(const CollisionVolumeBSphere& s, const Vect& col))
///		
///	\note More Visualization Tools coming soon.
///		
///	\n
///	  
///	\section VIS-3 Visualization Example
///			 In the following example, Frigate is a GameObject that has been set up for 
///			 Collision.  The user wants to view the Bounding Sphere as the Frigate moves
///			 around to they can easily check for collisions.
///			 
///	\code
///	Frigate::Update()
///	{
///		Visualizer::SubmitBSphereVisualization(GetBSphere(), Colors::Blue);
///		
///		// ...
///	}
///	\endcode
///		   
///	\note 
///		  1. You must include the "Visualizer.h" header to access the Visualizer  
///		  2. Include the "Colors.h" header to access the Colors Enumerator that contains the RBG color vectors for many common colors.
///	
///	
///	\defgroup SCREENLOG Screen Log
/// \ingroup DEBUGGING_TOOLS
/// \brief How to use the screen log to display debugging text in real time.
///
/// \section SCRLG-1 What is the Screen Log?
///		The Screen Log displays strings that you request in the window of your game.
///		While there is a delay when printing to the console, the ScreenLog operates in real time
///		and updates every frame of the game for live debugging messages.
///		
///		You can use standard printf formatting for Screen Log strings.
///
///		All Screen Log requests are gathered during one frame and then executed.
///		You must request visualization every frame you want something to appear.
/// 
///  \n
///	  
///	\section SCRLG-3 Screen Log Example
///			 In the following example, Frigate is a GameObject that has moves around.
///			 The user wants to display the position of the frigate in the debugging log
///			 as the Frigate moves around.
///			 
///	\code
///	Frigate::Update()
///	{
///		// More Update code for movement ...
///		
///		// Data Log
///		ScreenLog::Add("Frigate:");
///		ScreenLog::Add("\tPos: %3.1f, %3.1f, %3.1f", RotTrans.M12(), RotTrans.M13(), RotTrans.M14());
///	}
///	\endcode
///		   
///	\note You must include the "ScreenLog.h" header to access the ScreenLog
///		 
///	\defgroup GODCAM God Cam
/// \ingroup DEBUGGING_TOOLS
/// \brief How to use the god cam to view your scene with independent camera controls.
///
/// \section GC-1 What is the God Cam?
///		The God Cam allows you to look around your scene with a completely independent and input-controlled camera.
///		This tool is useful if you need to dynamically see your game from certain angles that your scene camera does not allow.
/// 
///  \n
///    
/// \section GC-2 How to use the God Cam?
/// 	The GodCam has 2 methods available:
/// 	- GodCamController::SwitchToGodCam()
/// 	- GodCamController::SwitchToLastUserCam()  
/// 	
/// Calling \b SwitchToGodCam() will change the scenes current camera to the God Cam and save your last scene camera internally.
/// When you are done using the God Cam, call \b SwitchToLastUserCam() to switch back to your old scene camera.
/// 	
/// When using the GodCam use the following keyboard controls to navigate:
/// - \b Forward = \b F Key    
/// - \b Backward = \b V Key  
/// - \b Right = \b B Key  
/// - \b Left = \b C Key  
/// 
/// - \b RotateUp = \b UpArrow Key  
/// - \b RotateDown = \b DownArrow Key
/// - \b RotateRight = \b RightArrow Key  
/// - \b RotateLeft = \b LeftArrowKey  
/// 
/// \n
/// 
///	\section GC-3 God Cam Example
///			 In the following example, the user has created a CameraController Game Object to manage their camera.
///			 They have set up key events to switch between the GodCam and their scene camera.
///
///	\code
///	void CameraController::KeyPressed(AZUL_KEY k)
/// {
///		switch (k)
///		{
///		// if "1" key pressed, switch to GodCam
///		case AZUL_KEY::KEY_1:
///			GodCamController::SwitchToGodCam();
///			break;
///		// if "2" key pressed, switch back to last scene camera
///		case AZUL_KEY::KEY_2:
///			GodCamController::SwitchToLastUserCam();
///			break;
///		}
/// }
///	\endcode
///
///	\note You must include the "GodCamController.h" header to access the GodCam
///
 