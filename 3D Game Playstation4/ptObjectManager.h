#ifndef __OBJECT_MANAGER__
#define __OBJECT_MANAGER__
#include <list>
#include "../../common/danGraphicsWrapper.h"
#include "ptAssetType.h"


using namespace std;


//Predeclarations 
class ptObject;
class ptCamera;
class ptAssetManager;
class ptLightEnvironment;
class ptController;
class Road;
class Enemy;
class Spaceship;
class ptHUDTextItem;
class Score;

//MAX number of road tiles and enemies
const int NUM_ROAD_TILES = 5;
const int NUM_ENEMIES = 5;



//SINGLETON
class ptObjectManager
{

private:
	ptObjectManager();
	~ptObjectManager();
	static ptObjectManager* pInstance;
public:

	//Attributes

	//list of all objects and collidable objects
	list<ptObject*> m_allObjects;
	list<ptObject*> m_colliders;

	ptAssetManager* m_pAssetManager;
	danGraphicsWrapper* m_pGraphicsWrapper;

	//Camera, light and controller
	ptLightEnvironment* m_pLightEnvironment;
	ptCamera* m_pCamera;
	ptController* m_pController;


	//Game object pointers
	Spaceship* m_pShip;
	Enemy* m_pEnemiesRight[NUM_ENEMIES];
	Enemy* m_pEnemiesLeft[NUM_ENEMIES];
	ptObject* m_pBackground = nullptr;

	//HUD menu & UI item pointers
	ptHUDTextItem* m_pHUDHealthText = nullptr;
	ptHUDTextItem* m_pHUDHealthNumber = nullptr;
	ptHUDTextItem* m_pHUDPauseExit = nullptr;
	ptHUDTextItem* m_pHUDPauseResume = nullptr;
	ptHUDTextItem* m_pHUDHighScore = nullptr;
	ptHUDTextItem* m_pHUDStartGame = nullptr;
	ptHUDTextItem* m_pHUDScoreText = nullptr;
	ptHUDTextItem* m_pHUDScoreNumber = nullptr;

	//User Score pointer
	Score* m_pScore = nullptr;

	//timer used for delays 
	float m_timer = 0;

	//used to end game when user ship is destroyed
	bool m_gameOn = true;

	//Methods
	static ptObjectManager* GetInstance();


	//Initialise
	//Parameters:
	//myAssetManager - used when creating new objects
	//myGraphicsWrapper - used when making draw calls
	//myLightEnvironment - used when making draw calls
	//myCamera - used when making draw calls
	//myController - used for updating the player ship
	void Initialise(ptAssetManager* myAssetManager, danGraphicsWrapper* myGraphicsWrapper,
		ptLightEnvironment* myLightEnvironment, ptCamera* myCamera, ptController* myController);


	//Creates objects and return a pointer to the object
	//Parameters:
	//object - enum type that is used to determine what 
	//object gets created
	ptObject* Create(ptObjectEnum object);

	//Creates an enemy rocket
	ptObject* CreateEnemyRocket(Matrix4 modelWorld);



	// Adds a new item to the list of objects.
	// Note: 
	// Parameters:
	//  pNewItem - Pointer to the object to be added
	//  collides - If true, this object will also be
	//          added to the list of collidable objects
	void AddItem(ptObject* pNewItem, bool collides);
	


	// Updates all objects
	void UpdateAll();
		
	// Draws all objects
	void DrawAll();

	// Checks for collisions between all collidable objects
	// If any collide, ProcessCollision will be called for both objects
	void ProcessCollisions();

	// Sets ALL objects to inactive.
	void DeactivateAll();

	// Deletes all objects in all scenes that have been set to "disabled".
	void DeleteInactiveItems();

	// Deletes all objects in all scenes
	void DeleteAllObjects();

	//Generates Road Tiles
	void RoadGenerator();

	//Generates Enemies
	void EnemyGenerator();

	//Delete Objects not in the object list
	void DeleteRogueObjects();
};


#endif