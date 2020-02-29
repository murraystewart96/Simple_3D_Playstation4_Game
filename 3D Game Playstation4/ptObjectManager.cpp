#pragma once
#include "ptObjectManager.h"
#include "ptAssetManager.h"
#include "ptObject.h"
#include "Entities.h"
#include "ptHUDTextItem.h"
#include "score.h"
#include "ScoreBoard.h"

ptObjectManager* ptObjectManager::pInstance = nullptr;


ptObjectManager::ptObjectManager()
{
	
}

ptObjectManager::~ptObjectManager()
{

}

ptObjectManager* ptObjectManager::GetInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new ptObjectManager;
	}
	return pInstance;
}




void ptObjectManager::Initialise(ptAssetManager* myAssetManager, danGraphicsWrapper* myGraphicsWrapper,
	ptLightEnvironment* myLightEnvironment, ptCamera* myCamera, ptController* myController)
{
	//Assign data for member variables 
	m_pAssetManager = myAssetManager;
	m_pGraphicsWrapper = myGraphicsWrapper;
	m_pLightEnvironment = myLightEnvironment;
	m_pCamera = myCamera;
	m_pController = myController;
	m_pScore = Score::GetInstance();
	m_pScore->m_score = 0;
	m_gameOn = true;


	//Create HUD menu items
	m_pHUDHealthText = new ptHUDTextItem(m_pAssetManager->m_myGarlicAllocator, "HEALTH:", 3, -0.95, 0.95, m_pAssetManager->GetMaterial(ptMaterialEnum::HUD_MAT));
	m_pHUDHealthNumber = new ptHUDTextItem(m_pAssetManager->m_myGarlicAllocator, 100, 2, -0.70, 0.95, m_pAssetManager->GetMaterial(ptMaterialEnum::HUD_MAT));

	m_pHUDScoreText = new ptHUDTextItem(m_pAssetManager->m_myGarlicAllocator, "SCORE:", 3, -0.2, 0.95, m_pAssetManager->GetMaterial(ptMaterialEnum::HUD_MAT));
	m_pHUDScoreNumber = new ptHUDTextItem(m_pAssetManager->m_myGarlicAllocator, 10000, 2, 0, 0.95, m_pAssetManager->GetMaterial(ptMaterialEnum::HUD_MAT));
	
	

	//Creating in game background
	ptObject * pBackground = new ptObject;
	pBackground->m_myModel = m_pAssetManager->getModel(ptModelEnum::FLOOR_PTM);
	pBackground->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::SPACE_MAT);
	pBackground->m_modelWorldMx = Matrix4::translation(Vector3(-3.5, -2, -50)) * Matrix4::rotationX(1.5708f) * Matrix4::scale(Vector3(10, 8, 10));
	m_pBackground = pBackground;
	AddItem(pBackground, false);


	//Initialising Enemies on right
	for (int i = 0; i <= NUM_ENEMIES; i++)
	{
		m_pEnemiesRight[i] = new Enemy;
		m_pEnemiesRight[i]->m_myModel = m_pAssetManager->getModel(ptModelEnum::ENEMY_SHIP_PTM);
		m_pEnemiesRight[i]->m_modelWorldMx = Matrix4::translation((Vector3(2, -2.5, -30.0f * i)))  *  Matrix4::scale(Vector3(0.5, 0.5, 0.5));
		m_pEnemiesRight[i]->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::ENEMY_SHIP_MAT);
		m_pEnemiesRight[i]->m_objectType = ptObjectEnum::ENEMY_SHIP;
		m_pEnemiesRight[i]->m_direction = 0;
		AddItem((ptObject*)m_pEnemiesRight[i], true);
	}

	//Initialising Enemies on left
	for (int i = 0; i <= NUM_ENEMIES; i++)
	{
		m_pEnemiesLeft[i] = new Enemy;
		m_pEnemiesLeft[i]->m_myModel = m_pAssetManager->getModel(ptModelEnum::ENEMY_SHIP_PTM);
		m_pEnemiesLeft[i]->m_modelWorldMx = Matrix4::translation((Vector3(-2, -2.5, -25.0f * i)))  * Matrix4::scale(Vector3(0.5, 0.5, 0.5));
		m_pEnemiesLeft[i]->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::ENEMY_SHIP_MAT);
		m_pEnemiesLeft[i]->m_objectType = ptObjectEnum::ENEMY_SHIP;
		m_pEnemiesLeft[i]->m_direction = 1;
		AddItem((ptObject*)m_pEnemiesLeft[i], true);
	}

	//Creating space station
	AddItem(Create(ptObjectEnum::SPACE_STATION), false);

	
}


ptObject* ptObjectManager::Create(ptObjectEnum object)
{
	switch (object)
	{
	case ptObjectEnum::SPACESHIP:
	{
		Spaceship* pTemp = new Spaceship;
		pTemp->m_myModel = m_pAssetManager->getModel(ptModelEnum::SPACESHIP_PTM);
		pTemp->m_modelWorldMx = Matrix4::translation((Vector3(0, -2.5, -5.0f))) * Matrix4::rotationY(3.1416) * Matrix4::scale(Vector3(1.5, 1.5, 1.5));
		pTemp->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::SPACESHIP_MAT);
		pTemp->m_pController = m_pController;
		pTemp->m_objectType = ptObjectEnum::SPACESHIP;
		m_pShip = pTemp;
		return (ptObject*)pTemp;
	}//case
	break;
	case ptObjectEnum::ENEMY_SHIP:
	{
		Enemy* pTemp = new Enemy;
		pTemp->m_myModel = m_pAssetManager->getModel(ptModelEnum::ENEMY_SHIP_PTM);
		pTemp->m_modelWorldMx = Matrix4::translation(Vector3(1, -2.5, -2))  * Matrix4::scale(Vector3(1,1,1));
		pTemp->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::ENEMY_SHIP_MAT);

		return (ptObject*)pTemp;
	}//case
	break;
	case ptObjectEnum::SPACE_STATION:
	{
		SpaceStation* pTemp = new SpaceStation;
		pTemp->m_myModel = m_pAssetManager->getModel(ptModelEnum::SPACE_STATION_PTM);
		pTemp->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::SPACE_STATION_MAT);
		pTemp->m_modelWorldMx = Matrix4::translation(Vector3(-3, 0, -5)) * Matrix4::rotationX(1.5708f) * Matrix4::scale(Vector3(1, 1, 1));
		return (ptObject*)pTemp;
	}//case
	break;
	case ptObjectEnum::ROCKET:
	{
		Rocket* pTemp = new Rocket(m_pShip->m_modelWorldMx);
		pTemp->m_myModel = m_pAssetManager->getModel(ptModelEnum::SPHERE_PTM);
		pTemp->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::OIL_MAT);
		pTemp->m_objectType = ptObjectEnum::ROCKET;
		pTemp->m_modelWorldMx = pTemp->m_modelWorldMx * Matrix4::scale(Vector3(0.4, 0.4, 0.4));
		return (ptObject*)pTemp;
	}//case
	}//switch


}



ptObject* ptObjectManager::CreateEnemyRocket(Matrix4 modelWorld)
{
	EnemyRocket* pTemp = new EnemyRocket(modelWorld);
	pTemp->m_myModel = m_pAssetManager->getModel(ptModelEnum::SPHERE_PTM);
	pTemp->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::EARTH_MAT);
	pTemp->m_objectType = ptObjectEnum::ENEMY_ROCKET;
	return (ptObject*)pTemp;
}


// Adds a new item to the list of objects.
// Note: 

// Parameters:
//  pNewItem - Pointer to the object to be added
//  collides - If true, this object will also be
//          added to the list of collidable objects
void ptObjectManager::AddItem(ptObject* pNewItem, bool collides)
{

	//Add new item to object list
	m_allObjects.push_back(pNewItem);

	//If collides also add to collider list
	if (collides)
	{
		m_colliders.push_back(pNewItem);
	}

	

}



void ptObjectManager::DeactivateAll()
{
	auto it = m_allObjects.begin();

	for (; it != m_allObjects.end(); ++it)
	{
		(*it)->Deactivate();
	}


	auto it2 = m_colliders.begin();

	for (; it2 != m_colliders.end(); ++it2)
	{
		(*it2)->Deactivate();
	}

	printf("All objects deactivated\n");

}

// Deletes all objects in all scenes that have been set to "disabled".
void ptObjectManager::DeleteInactiveItems()
{



	// Remove all inactive objects from collider list

	auto itc = std::remove_if(m_colliders.begin(), m_colliders.end(), [](ptObject* pGO) { return !pGO->m_isActive; });
	m_colliders.erase(itc, m_colliders.end());


	// Delete all inactive objects
	auto it = m_allObjects.begin();

	for (; it != m_allObjects.end(); ++it)
	{
		if (!(*it)->m_isActive)
		{
			delete *it;
			*it = nullptr;
		}
	}

	// Remove all inactive objects from master list
	auto ita = std::remove(m_allObjects.begin(), m_allObjects.end(), nullptr);
	m_allObjects.erase(ita, m_allObjects.end());

	printf("ydydydydyd\n");
	
}//DeleteInactiveItems





// Updates all objects in the current scene.
void ptObjectManager::UpdateAll()
{


	auto it = m_allObjects.begin();

	for (it; it != m_allObjects.end(); it++)
	{
		if ((*it)->m_isActive)
		{
			(*it)->Update();
		}
	}

	m_pHUDHealthNumber->HUDNumberInput(m_pShip->m_health);
	m_pHUDScoreNumber->HUDNumberInput(m_pScore->m_score);

	m_timer += 0.02;

	if (!m_pShip->m_isActive && m_timer > 5)
	{
		m_gameOn = false;
	}

	if (m_timer > 5)
	{
		m_timer = 0;
	
	}

	m_pHUDScoreNumber->HUDNumberInput(m_pScore->m_score);

	

	EnemyGenerator();

}


void ptObjectManager::RoadGenerator()
{

}

void ptObjectManager::EnemyGenerator()
{
	//Generating Enemies
	for (int i = 0; i <= NUM_ENEMIES; i++)
	{
		//Deleting enemies if they are out of scene
		if (m_pEnemiesRight[i]->m_isActive)
		{
			if (m_pEnemiesRight[i]->m_modelWorldMx.getTranslation().getZ() > 2 || m_pEnemiesRight[i]->m_isActive == false)
			{
				m_pEnemiesRight[i]->m_isActive = false;
				delete m_pEnemiesRight[i];
				m_pEnemiesRight[i] = nullptr;
			}
		}//if

		 //Deleting enemies if they are out of scene
		if (m_pEnemiesLeft[i]->m_isAlive)
		{
			if (m_pEnemiesLeft[i]->m_modelWorldMx.getTranslation().getZ() > 2 || m_pEnemiesLeft[i]->m_isActive == false)
			{
				m_pEnemiesLeft[i]->m_isActive = false;
				delete m_pEnemiesLeft[i];
				m_pEnemiesLeft[i] = nullptr;
			}
		}//if


		//Creating enemies if they are nullptr
		if (m_pEnemiesRight[i] == nullptr)
		{
			m_pEnemiesRight[i] = new Enemy;
			m_pEnemiesRight[i]->m_myModel = m_pAssetManager->getModel(ptModelEnum::ENEMY_SHIP_PTM);
			m_pEnemiesRight[i]->m_modelWorldMx = Matrix4::translation((Vector3(2, -2.5, -100))) * Matrix4::scale(Vector3(0.5, 0.5, 0.5));
			m_pEnemiesRight[i]->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::ENEMY_SHIP_MAT);
			m_pEnemiesRight[i]->m_direction = 0;
		}//if

		 //Creating enemies if they are nullptr
		if (m_pEnemiesLeft[i] == nullptr)
		{
			m_pEnemiesLeft[i] = new Enemy;
			m_pEnemiesLeft[i]->m_myModel = m_pAssetManager->getModel(ptModelEnum::ENEMY_SHIP_PTM);
			m_pEnemiesLeft[i]->m_modelWorldMx = Matrix4::translation((Vector3(-2, -2.5, -89))) * Matrix4::scale(Vector3(0.5, 0.5, 0.5));
			m_pEnemiesLeft[i]->m_myMaterial = m_pAssetManager->GetMaterial(ptMaterialEnum::ENEMY_SHIP_MAT); 
			m_pEnemiesLeft[i]->m_direction = 1;
		}//if

	}//for
}


// Draws all objects in the current scene
void ptObjectManager::DrawAll()
{

	//required to set states ready for draw commands
	m_pGraphicsWrapper->preDraw();

	//Grab a pointer to the current graphics context, to give us direct access
	Gnmx::GnmxGfxContext* myGFXC = m_pGraphicsWrapper->getRenderContext();

	auto it = m_allObjects.begin();

	

	for (it; it != m_allObjects.end(); it++)
	{
		if ((*it)->m_isActive)
		{
			(*it)->Draw(myGFXC, m_pLightEnvironment, m_pCamera);
		}
	}


	m_pHUDHealthText->Draw(myGFXC);
	m_pHUDHealthNumber->Draw(myGFXC);

	m_pHUDScoreText->Draw(myGFXC);
	m_pHUDScoreNumber->Draw(myGFXC);

	//and this neeeds to be done after all draw calls, to end the frame.
	m_pGraphicsWrapper->postDraw();
}

// Checks for collisions between all objects in the current scene.
// If any collide, ProcessCollision will be called for both objects
void ptObjectManager::ProcessCollisions()
{
	//  collisions
	auto it1 = m_colliders.begin();

	for (; it1 != m_colliders.end(); ++it1)
	{
		auto it2 = it1;
		it2++;

		for (; it2 != m_colliders.end(); ++it2)
		{
			if ((*it1)->m_isActive && (*it2)->m_isActive)
			{
				if ((*it1)->HasCollided(**it2))
				{
					(*it1)->ProcessCollision(**it2);
					(*it2)->ProcessCollision(**it1);
				}
			}
		}//for
	}

	
}

// Deletes all objects in all scenes
void ptObjectManager::DeleteAllObjects()
{
	auto it = m_allObjects.begin();

	for (it; it != m_allObjects.end(); it++)
	{
		//delete (*it);
		(*it) = nullptr;
	}

	auto it2 = m_colliders.begin();

	for (it2; it2 != m_colliders.end(); it2++)
	{
		//delete (*it2);
		(*it2) = nullptr;
	}

	m_allObjects.clear();
	m_colliders.clear();

	printf("All objects deleted\n");
}




void ptObjectManager::DeleteRogueObjects()
{
	/*delete m_pBackground;
	delete m_pauseGround;
	delete m_pHUDHealthText;
	delete m_pHUDHealthNumber;
	delete m_pHUDPauseExit;
	delete m_pHUDPauseResume;
	delete m_pHUDHighScore;
	delete m_pHUDStartGame;

	delete m_pHUDScoreText;
	delete m_pHUDScoreNumber;*/
	
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		//delete m_pEnemiesLeft[i];
		m_pEnemiesLeft[i] = nullptr;

		//delete m_pEnemiesRight[i];
		m_pEnemiesRight[i] = nullptr;

	}

	


	 m_pBackground = nullptr;
	 m_pHUDHealthText = nullptr;
	 m_pHUDHealthNumber = nullptr;
	 m_pHUDPauseExit = nullptr;
	 m_pHUDPauseResume = nullptr;
	 m_pHUDHighScore = nullptr;
	 m_pHUDStartGame = nullptr;

	 m_pHUDScoreText = nullptr;
	 m_pHUDScoreNumber = nullptr;

	 printf("rogue objects deleted\n");
}



