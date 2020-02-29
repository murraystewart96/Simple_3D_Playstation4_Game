/* SIE CONFIDENTIAL
PlayStation(R)4 Programmer Tool Runtime Library Release 04.008.061
* Copyright (C) 2015 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/


#include <stdio.h>
#include <stdlib.h>
#include <scebase.h>
#include <kernel.h>
#include <gnmx.h>
#include <video_out.h>
#include "../../toolkit/toolkit.h"
#include "../../common/allocator.h"

#include "../../common/danGraphicsWrapper.h"
#include "ptHardModels.h"
#include "ptModel.h"
#include "DrawManager.h"
#include "ptController.h"
#include "ptCamera.h"
#include "ptObject.h"
#include "ptAssetManager.h"
#include "ptLightEnvironment.h"
#include "ptObjectManager.h"
#include "ptHUDTextItem.h"
#include "score.h"
#include "ScoreBoard.h"
#include "GameState.h"
#include "ptMenuSystem.h"

using namespace sce;
using namespace sce::Gnmx;



int main(int _argc, const char* _argv[])
{
	//define the size of our memory heaps
	static const size_t sc_onionMemorySize = 16 * 1024 * 1024;
	static const size_t sc_garlicMemorySize = 64 * 4 * 1024 * 1024;


	//utility for error messages
	int l_error;

	// there are several types of memory access available, but we need to do our own memory management
	// the three main types are "CPU" (which is used automatically) "Onion" for larger CPU use and "Garlic" for GPU use
	// Initialize the WB_ONION memory allocator
	LinearAllocator myOnionAllocator;
	l_error = myOnionAllocator.initialize(sc_onionMemorySize, SCE_KERNEL_WB_ONION, SCE_KERNEL_PROT_CPU_RW | SCE_KERNEL_PROT_GPU_ALL);
	if (l_error != SCE_OK) { printf("Onion allocator failed to initialise: 0x%08X\n", l_error);  return l_error; }

	// Initialize the WC_GARLIC memory allocator
	// NOTE: CPU reads from GARLIC write-combined memory have a very low
	//       bandwidth so they are disabled for safety in this sample
	LinearAllocator myGarlicAllocator;
	l_error = myGarlicAllocator.initialize(sc_garlicMemorySize, SCE_KERNEL_WC_GARLIC, SCE_KERNEL_PROT_CPU_WRITE | SCE_KERNEL_PROT_GPU_ALL);
	if (l_error != SCE_OK) { printf("Garlic allocator failed to initialise: 0x%08X\n", l_error);  return l_error; }

	// We are using three wrappers to the hardware provided by Sony
	// "Gnm" is their low-level graphics API
	// On top of this they provide "Gnmx" with higher level functionality
	// Both Gnm and Gnmx are accessed through libraries and are part of the standard SCE API
	// There is also "toolkit" which was developed for their sample programs
	// This adds yet more abstraction above Gnm and Gnmx
	// However, it is not part of the standard API and so including it in projects is a little cumbersome
	// Sony advise it is not fit for use in release mode games.

	// Initialize the Toolkit module
	sce::Gnmx::Toolkit::Allocators myToolkitAllocators;
	myOnionAllocator.getIAllocator(myToolkitAllocators.m_onion);
	myGarlicAllocator.getIAllocator(myToolkitAllocators.m_garlic);
	Toolkit::initializeWithAllocators(&myToolkitAllocators);

	// Finally, there is a fourth layer of wrapper, the danGraphicsWrapper
	// this is provided by Dan Hodgson for use for students with his tutor series
	// It abstracts away a whole load of hardware stuff including render contexts, video surfaces and concurrency
	danGraphicsWrapper myGraphicsWrapper;
	l_error = myGraphicsWrapper.init(&myOnionAllocator, &myGarlicAllocator);
	if (l_error != SCE_OK) { printf("Graphics Wrapper failed to init: 0x%08X\n", l_error);  return l_error; }



	//Aspect ratio for screen perspective 
	const float t_aspectRatio = float(myGraphicsWrapper.getBufferWidth()) / float(myGraphicsWrapper.getBufferHeight());

	//Game States within the game loop

	GameStateEnum currentState = SETUP;
	GameStateEnum previousState = SETUP;




	//Creating and initialise asset manager
	ptAssetManager myAssetManager(&myGarlicAllocator, &myToolkitAllocators);   
	myAssetManager.Initialise();

	
	//Create game objects 
	ptController myController;
	ptCamera myCamera;
	ptLightEnvironment myLightEnvironment;
	ptObjectManager* p_OM = ptObjectManager::GetInstance();
	//ScoreBoard myScoreBoard = ScoreBoard(&myGarlicAllocator, &myAssetManager);

	

	//Set camera perspective
	myCamera.setPerspetive(1.57f, t_aspectRatio, 0.001f, 100.0f);
	


	ptMenuSystem myMenuSystem = ptMenuSystem(&myGarlicAllocator, &myAssetManager, &myController);

	//main draw loop
	for (uint32_t t_frameIndex = 0; t_frameIndex < 10000; ++t_frameIndex) //only display for a few seconds
	{

	


		switch (currentState)
		{
		//Sets up the game 
		case SETUP:        
		{
			

			//Initialising controller & object manager
			myController.initialise();
			p_OM->Initialise(&myAssetManager, &myGraphicsWrapper, &myLightEnvironment, &myCamera, &myController);

			//Add players specehsip 
			p_OM->AddItem(p_OM->Create(ptObjectEnum::SPACESHIP), true);

			//Switch state to running
			if (previousState == SETUP)
			{
				currentState = MENU;
			}
			else
			{
				currentState = RUNNING;
			}

		}//case
		break;
		case MENU:
		{

			Gnmx::GnmxGfxContext* myGFXC = myGraphicsWrapper.getRenderContext();
			
			currentState = myMenuSystem.MainMenu();
			previousState = myMenuSystem.m_previousState;


			if (currentState == EXIT)
			{
				return 0;
			}
			else if (currentState == SETUP)
			{
				break;
			}


			myGraphicsWrapper.preDraw();
			myMenuSystem.DrawMainMenu(myGFXC);
			myGraphicsWrapper.postDraw();
		}//case
		break;
		case PAUSED:
		{
			
			Gnmx::GnmxGfxContext* myGFXC = myGraphicsWrapper.getRenderContext();

			currentState = myMenuSystem.PauseMenu();
			previousState = PAUSED;
	
			////Draw HUD Menu Items
			myGraphicsWrapper.preDraw();
			myMenuSystem.DrawPauseMenu(myGFXC);
			myGraphicsWrapper.postDraw();
		}//case
		break;
		case RUNNING:
		{
			
			p_OM->m_pController->update();

			//Update Objects
			p_OM->UpdateAll();
			p_OM->DrawAll();
			p_OM->ProcessCollisions();

			//If pressed enter paused 
			if (p_OM->m_pController->optionsPressCheck())
			{
				currentState = PAUSED;
			}

			//If false add player score and enter GameOver state
			if (!p_OM->m_gameOn)
			{
				myMenuSystem.m_pScoreBoard->AddScore();
				currentState = GAMEOVER;
			}
		}//case
		break;
		case HIGHSCORE:
		{

			Gnmx::GnmxGfxContext* myGFXC = myGraphicsWrapper.getRenderContext();

			currentState = myMenuSystem.HighScoreMenu();

			//Draw Highscore Items
			myGraphicsWrapper.preDraw();
			myMenuSystem.DrawHighScores(myGFXC);
			myGraphicsWrapper.postDraw();

		}//case
		break;
		case GAMEOVER:
		{
			
			Gnmx::GnmxGfxContext* myGFXC = myGraphicsWrapper.getRenderContext();

			currentState = myMenuSystem.MainMenu();
			previousState = myMenuSystem.m_previousState;

			if (currentState == EXIT)
			{
				return 0;
			}
			else if (currentState == SETUP)
			{
				break;
			}

			
			////Draw HUD Menu Items
			myGraphicsWrapper.preDraw();
			myMenuSystem.DrawMainMenu(myGFXC);
			myGraphicsWrapper.postDraw();
			
		}//case
		break;
		}//switch

	}//for (main looop)

	 //tidy up
	myGraphicsWrapper.release();

	// Releasing manually each allocated resource is not necessary as we are
	// terminating the linear allocators for ONION and GARLIC here.
	myOnionAllocator.terminate();
	myGarlicAllocator.terminate();

	return 0;
}//main()
