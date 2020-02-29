#ifndef __PT_CONTROLLER__
#define __PT_CONTROLLER__
#include <pad.h>
#include <scebase.h>
#include <user_service.h>


//************ Holds status of controller **************
//typedef struct ScePadData {
//	uint32_t buttons;
// ScePadAnalogStick leftStick;
//	ScePadAnalogStick rightStick;
//	ScePadAnalogButtons analogButtons;
//	SceFQuaternion orientation;
//	SceFVector3 acceleration;
//	SceFVector3 angularVelocity;
//	ScePadTouchData touchData;
//	bool connected;
//	uint64_t timestamp;
//	ScePadExtensionUnitData extensionUnitData;
//	uint8_t connectedCount;
//	uint8_t reserve[2];
//	uint8_t deviceUniqueDataLen;
//	uint8_t deviceUniqueData[SCE_PAD_MAX_DEVICE_UNIQUE_DATA_SIZE];
//} ScePadData;

/////////////////////////////////////////////////////////////////////////////

//typedef enum ScePadButtonDataOffset {
//	SCE_PAD_BUTTON_L3 = 0x00000002,
//	SCE_PAD_BUTTON_R3 = 0x00000004,
//	SCE_PAD_BUTTON_OPTIONS = 0x00000008,
//	SCE_PAD_BUTTON_UP = 0x00000010,
//	SCE_PAD_BUTTON_RIGHT = 0x00000020,
//	SCE_PAD_BUTTON_DOWN = 0x00000040,
//	SCE_PAD_BUTTON_LEFT = 0x00000080,
//	SCE_PAD_BUTTON_L2 = 0x00000100,
//	SCE_PAD_BUTTON_R2 = 0x00000200,
//	SCE_PAD_BUTTON_L1 = 0x00000400,
//	SCE_PAD_BUTTON_R1 = 0x00000800,
//	SCE_PAD_BUTTON_TRIANGLE = 0x00001000,
//	SCE_PAD_BUTTON_CIRCLE = 0x00002000,
//	SCE_PAD_BUTTON_CROSS = 0x00004000,
//	SCE_PAD_BUTTON_SQUARE = 0x00008000,
//	SCE_PAD_BUTTON_TOUCH_PAD = 0x00100000,
//	SCE_PAD_BUTTON_INTERCEPTED = 0x80000000,
//} ScePadButtonDataOffset;


class ptController
{
public:
	SceUserServiceUserId  m_userId; //id of the user the controller is assigned to
	int32_t m_handle;				//the controller handle, used for all subsequent data collection
	ScePadData m_padState;			//holds the state of the controller when polled 
	uint8_t m_stickOffset = 128;    //
	bool m_initialised = false;		//flag to show when initialised
	bool m_isCrossPressed = false;
	bool m_isR1Pressed = false;
	bool m_isL1Pressed = false;
	bool m_isSquarePressed = false;
	bool m_isCirclePressed = false;
	bool m_isTrianglePressed = false;
	bool m_isR2Pressed = false;
	bool m_isL2Pressed = false;
	bool m_isR3Pressed = false;
	bool m_isL3Pressed = false;
	bool m_isUpPressed = false;
	bool m_isDownPressed = false;
	bool m_isLeftPressed = false;
	bool m_isRightPressed = false;
	bool m_isOptionsPressed = false;
	bool m_crossToggle = false;
	bool m_squareToggle = false;
	bool m_circleToggle = false;
	bool m_triangleToggle = false;
	bool m_R1Toggle = false;
	bool m_L1Toggle = false;
	bool m_R2Toggle = false;
	bool m_L2Toggle = false;
	bool m_R3Toggle = false;
	bool m_L3Toggle = false;
	bool m_upToggle = false;
	bool m_downToggle = false;
	bool m_leftToggle = false;
	bool m_rightToggle = false;
	float m_stickDeadZone = 15.0f;






	float leftStickX()
	{
		float xValue = (m_padState.leftStick.x - m_stickOffset);

		if ((xValue <= m_stickDeadZone) && (xValue >= -m_stickDeadZone))
		{
			xValue = 0;
		}



		return xValue / 1500.0f;
	}


	float leftStickY()
	{
		int yValue = (m_padState.leftStick.y - m_stickOffset);          //yValue = float that represents how far stick has been pushed (y-axis)

		if (yValue <= m_stickDeadZone && yValue >= -m_stickDeadZone)    //If value is in deadzone set to 0
		{
			yValue = 0;
		}



		return (yValue / 1000.0f) * -1;      //return yValue 
	}


	float rightStickX()
	{
		int xValue = (m_padState.rightStick.x - m_stickOffset);

		if ((xValue <= m_stickDeadZone) && (xValue >= -m_stickDeadZone))
		{
			xValue = 0;
		}

		return xValue / 2000.0f;
	}


	float rightStickY()
	{
		int yValue = (m_padState.rightStick.y - m_stickOffset);          //yValue = float that represents how far stick has been pushed (x-axis)

		if (yValue <= m_stickDeadZone && yValue >= -m_stickDeadZone)    //If value is in deadzone set to 0
		{
			yValue = 0;
		}

		return (yValue / 500.0f) * -1;      //return yValue 
	}



	//first set - check if the button is currently pressed
	bool crossPressed() { return m_padState.buttons & SCE_PAD_BUTTON_CROSS; }

	//first set - check if the button is currently pressed
	bool squarePressed() { return m_padState.buttons & SCE_PAD_BUTTON_SQUARE; }

	//first set - check if the button is currently pressed
	bool trianglePressed() { return m_padState.buttons & SCE_PAD_BUTTON_TRIANGLE; }

	//first set - check if the button is currently pressed
	bool circlePressed() { return m_padState.buttons & SCE_PAD_BUTTON_CIRCLE; }

	//first set - check if the button is currently pressed
	bool L1Pressed() { return m_padState.buttons & SCE_PAD_BUTTON_L1; }

	//first set - check if the button is currently pressed
	bool L2Pressed() { return m_padState.buttons & SCE_PAD_BUTTON_L2; }

	//first set - check if the button is currently pressed
	bool L3Pressed() { return m_padState.buttons & SCE_PAD_BUTTON_L3; }

	//first set - check if the button is currently pressed
	bool R1Pressed() { return m_padState.buttons & SCE_PAD_BUTTON_R1; }

	//first set - check if the button is currently pressed
	bool R2Pressed() { return m_padState.buttons & SCE_PAD_BUTTON_R2; }

	//first set - check if the button is currently pressed
	bool R3Pressed() { return m_padState.buttons & SCE_PAD_BUTTON_R3; }

	//first set - check if the button is currently pressed
	bool upPressed() { return m_padState.buttons & SCE_PAD_BUTTON_UP; }

	//first set - check if the button is currently pressed
	bool downPressed() { return m_padState.buttons & SCE_PAD_BUTTON_DOWN; }

	//first set - check if the button is currently pressed
	bool leftPressed() { return m_padState.buttons & SCE_PAD_BUTTON_LEFT; }

	//first set - check if the button is currently pressed
	bool rightPressed() { return m_padState.buttons & SCE_PAD_BUTTON_RIGHT; }

	//first set - check if the button is currently pressed
	bool optionsPressed() { return m_padState.buttons & SCE_PAD_BUTTON_OPTIONS; }


	//Checks to see if the button has already been pressed


	bool optionsPressCheck()
	{
		if (optionsPressed())
		{
			if (m_isOptionsPressed == false)
			{
				m_isOptionsPressed = true;
				return true;
			}
			else if (m_isOptionsPressed == true)
			{
				return false;
			}
		}
		else
		{
			m_isOptionsPressed = false;

			return false;
		}
	}

	bool crossPressCheck()
	{
		if (crossPressed())
		{
			if (m_isCrossPressed == false)
			{
				m_isCrossPressed = true;
				return true;
			}
			else if (m_isCrossPressed == true)
			{
				return false;
			}
		}
		else
		{
			m_isCrossPressed = false;

			return false;
		}
	}

	bool R1PressCheck()
	{
		if (R1Pressed())
		{
			if (m_isR1Pressed == false)
			{
				m_isR1Pressed = true;
				return true;
			}
			else if (m_isR1Pressed == true)
			{
				return false;
			}
		}
		else
		{
			m_isR1Pressed = false;

			return false;
		}
		
	}

	//Checking to see if L1 needs to be registered 
	bool L1PressCheck()
	{
		if (L1Pressed())                  //is L1 Pressed
		{
			if (m_isL1Pressed == false)    //has it been registered 
			{
				m_isL1Pressed = true;      //set to true (register hit)
				return true;
			}
			else if (m_isL1Pressed == true)   //has it been registered 
			{
				return false;              //return false;
			}
		}
		else
		{
			m_isL1Pressed = false;

			return false;
		}
	}
	


	bool squarePressCheck()
	{
		if (squarePressed())
		{
			if (m_isSquarePressed == false)
			{
				m_isSquarePressed = true;
				return true;
			}
			else if (m_isSquarePressed == true)
			{
				return false;
			}
		}
		else
		{
			m_isSquarePressed = false;

			return false;
		}
	}


	bool circlePressCheck()
	{
		if (circlePressed())
		{
			if (m_isCirclePressed == false)
			{
				m_isCirclePressed = true;
				return true;
			}
			else if (m_isCirclePressed == true)
			{
				return false;
			}
		}
		else
		{
			m_isCirclePressed = false;

			return false;
		}
	}



	//Checking to see if L1 is still being pressed 
	bool trianglePressCheck()
	{
		if (trianglePressed())                  //is L1 Pressed
		{
			if (m_isTrianglePressed == false)    //was it being held
			{
				m_isTrianglePressed = true;      //set to true
				return true;
			}
			else if (m_isTrianglePressed == true)   //was it being held
			{
				return false;              //return false;
			}
		}
		else                             //If not pressed
		{
			m_isTrianglePressed = false;       //Set to false 

			return false;                
		}
	}



	bool L2PressCheck()
	{
		if (L2Pressed())                  //is L2 Pressed
		{
			if (m_isL2Pressed == false)    //was it being held
			{
				m_isL2Pressed = true;      //set to true
				return true;
			}
			else if (m_isL2Pressed == true)   //was it being held
			{
				return false;              //return false;
			}
		}
		else                             //If not pressed
		{
			m_isL2Pressed = false;       //Set to false 

			return false;              
		}
	}



	bool L3PressCheck()
	{
		if (L3Pressed())                  //is L3 Pressed
		{
			if (m_isL3Pressed == false)    //was it being held
			{
				m_isL3Pressed = true;      //set to true
				return true;
			}
			else if (m_isL3Pressed == true)   //was it being held
			{
				return false;              //return false;
			}
		}
		else                             //If not pressed
		{
			m_isL3Pressed = false;       //Set to false 

			return false;             
		}
	}


	bool R3PressCheck()
	{
		if (R3Pressed())
		{
			if (m_isR3Pressed == false)
			{
				m_isR3Pressed = true;
				return true;
			}
			else if (m_isR3Pressed == true)
			{
				return false;
			}
		}
		else
		{
			m_isR3Pressed = false;

			return false;
		}
	}


	bool R2PressCheck()
	{
		if (R2Pressed())
		{
			if (m_isR2Pressed == false)
			{
				m_isR2Pressed = true;
				return true;
			}
			else if (m_isR2Pressed == true)
			{
				return false;
			}
		}
		else
		{
			m_isR2Pressed = false;

			return false;
		}
	}



	bool upPressCheck()
	{
		if (upPressed())                  //is L1 Pressed
		{
			if (m_isUpPressed == false)    //was it being held
			{
				m_isUpPressed = true;      //set to true
				return true;
			}
			else if (m_isUpPressed == true)   //was it being held
			{
				return false;              //return false;
			}
		}
		else                             //If not pressed
		{
			m_isUpPressed = false;       //Set to false 

			return false;               
		}
	}


	bool downPressCheck()
	{
		if (downPressed())                  //is L1 Pressed
		{
			if (m_isDownPressed == false)    //was it being held
			{
				m_isDownPressed = true;      //set to true
				return true;
			}
			else if (m_isDownPressed == true)   //was it being held
			{
				return false;              //return false;
			}
		}
		else                             //If not pressed
		{
			m_isDownPressed = false;       //Set to false 

			return false;             
		}
	}


	bool leftPressCheck()
	{
		if (leftPressed())                  //is L1 Pressed
		{
			if (m_isLeftPressed == false)    //was it being held
			{
				m_isLeftPressed = true;      //set to true
				return true;
			}
			else if (m_isLeftPressed == true)   //was it being held
			{
				return false;              //return false;
			}
		}
		else                             //If not pressed
		{
			m_isLeftPressed = false;       //Set to false 

			return false;              
		}
	}



	bool rightPressCheck()
	{
		if (rightPressed())                    //Has right been pressed 
		{
			if (m_isRightPressed == false)     //has the hit been registered 
			{
				m_isRightPressed = true;       //If not set to true
				return true;                   
			}
			else if (m_isRightPressed == true)  //If it has been registered return false
			{
				return false;
			}
		}
		else                              //If right hasn't been pressed return false;
		{
			m_isRightPressed = false;

			return false;
		}
	}

	//*&**************************************************************************

	bool R1Toggle() 
	{
		if (R1PressCheck() == true)                //does hit need to be registered 
		{
			m_R1Toggle = !m_R1Toggle;              //toggle to opposite of exisiting value
			return m_R1Toggle;
		}
		else if(R1PressCheck() == false)          //does hit need to be registered 
		{           
			return m_R1Toggle;
		}
	}

	bool R2Toggle()
	{
		if (R2PressCheck() == true)                //does hit need to be registered 
		{
			m_R2Toggle = !m_R2Toggle;              //toggle to opposite of exisiting value
			return m_R2Toggle;
		}
		else if (R2PressCheck() == false)          //does hit need to be registered 
		{
			return m_R2Toggle;
		}
	}

	bool R3Toggle()
	{
		if (R3PressCheck() == true)                //does hit need to be registered 
		{
			m_R3Toggle = !m_R3Toggle;              //toggle to opposite of exisiting value
			return m_R3Toggle;
		}
		else if (R3PressCheck() == false)          //does hit need to be registered 
		{
			return m_R3Toggle;
		}
	}

	bool L1Toggle()
	{
		if (L1PressCheck() == true)                //does hit need to be registered 
		{
			m_L1Toggle = !m_L1Toggle;              //toggle to opposite of exisiting value
			return m_L1Toggle;
		}
		else if (L1PressCheck() == false)          //does hit need to be registered 
		{
			return m_L1Toggle;
		}
	}

	bool L2Toggle()
	{
		if (L2PressCheck() == true)                //does hit need to be registered 
		{
			m_L2Toggle = !m_L2Toggle;              //toggle to opposite of exisiting value
			return m_L2Toggle;
		}
		else if (L2PressCheck() == false)          //does hit need to be registered 
		{
			return m_L2Toggle;
		}
	}

	bool L3Toggle()
	{
		if (L3PressCheck() == true)                //does hit need to be registered 
		{
			m_L3Toggle = !m_L3Toggle;              //toggle to opposite of exisiting value
			return m_L3Toggle;
		}
		else if (L3PressCheck() == false)          //does hit need to be registered 
		{
			return m_L3Toggle;
		}
	}

	bool crossToggle()
	{
		if (crossPressCheck() == true)                //does hit need to be registered 
		{
			m_crossToggle = !m_crossToggle;              //toggle to opposite of exisiting value
			return m_crossToggle;
		}
		else if (crossPressCheck() == false)          //does hit need to be registered 
		{
			return m_crossToggle;
		}
	}

	bool squareToggle()
	{
		if (squarePressCheck() == true)                //does hit need to be registered 
		{
			m_squareToggle = !m_squareToggle;              //toggle to opposite of exisiting value
			return m_squareToggle;
		}
		else if (squarePressCheck() == false)          //does hit need to be registered 
		{
			return m_squareToggle;
		}
	}


	bool circleToggle()
	{
		if (circlePressCheck() == true)                //does hit need to be registered 
		{
			m_circleToggle = !m_circleToggle;              //toggle to opposite of exisiting value
			return m_circleToggle;
		}
		else if (circlePressCheck() == false)          //does hit need to be registered 
		{
			return m_circleToggle;
		}
	}


	bool triangleToggle()
	{
		if (trianglePressCheck() == true)                //does hit need to be registered 
		{
			m_triangleToggle = !m_triangleToggle;              //toggle to opposite of exisiting value
			return m_triangleToggle;
		}
		else if (trianglePressCheck() == false)          //does hit need to be registered 
		{
			return m_triangleToggle;
		}
	}



	bool upToggle()
	{
		if (upPressCheck() == true)                //does hit need to be registered 
		{
			m_upToggle = !m_upToggle;              //toggle to opposite of exisiting value
			return m_upToggle;
		}
		else if (upPressCheck() == false)          //does hit need to be registered 
		{
			return m_upToggle;
		}
	}


	bool downToggle()
	{
		if (downPressCheck() == true)                //does hit need to be registered 
		{
			m_downToggle = !m_downToggle;              //toggle to opposite of exisiting value
			return m_downToggle;
		}
		else if (downPressCheck() == false)          //does hit need to be registered 
		{
			return m_downToggle;
		}
	}

	bool leftToggle()
	{
		if (leftPressCheck() == true)                //does hit need to be registered 
		{
			m_leftToggle = !m_leftToggle;              //toggle to opposite of exisiting value
			return m_leftToggle;
		}
		else if (leftPressCheck() == false)          //does hit need to be registered 
		{
			return m_leftToggle;
		}
	}

	bool rightToggle()
	{
		if (rightPressCheck() == true)                //does hit need to be registered 
		{
			m_rightToggle = !m_rightToggle;              //toggle to opposite of exisiting value
			return m_rightToggle;
		}
		else if (rightPressCheck() == false)          //does hit need to be registered 
		{
			return m_rightToggle;
		}
	}


	//Initialise controller 
	int initialise()
	{
		int l_error = SCE_OK;

		l_error = sceUserServiceInitialize(NULL);
		if (l_error != SCE_OK) { printf("Unable to initialise user service (from ptController::initialise())\n");  return SCE_ERROR_ERROR_FLAG; }

		//initialise pad library
		l_error = scePadInit();
		if (l_error != SCE_OK) { printf("Unable to initialise controller library\n");  return SCE_ERROR_ERROR_FLAG; }

		//get id for logged in user
		l_error = sceUserServiceGetInitialUser(&m_userId);
		if (l_error != SCE_OK) { printf("Unable to get initial user id (ptController::initialise())\n");  return SCE_ERROR_ERROR_FLAG; }

		m_handle = scePadOpen(m_userId, SCE_PAD_PORT_TYPE_STANDARD, 0, NULL);
		if (m_handle < 0) { printf("Unable to get controller handle\n");  return SCE_ERROR_ERROR_FLAG; }

		//get first lot of data
		l_error = scePadReadState(m_handle, &m_padState);
		if (l_error != SCE_OK) { printf("Unable to read intial data for controller\n");  return SCE_ERROR_ERROR_FLAG; }

		m_initialised = true;

		return l_error;
	}//initialize


	 //populates m_padState with the current state of the pad
	int update()
	{
		int l_error = SCE_ERROR_ERROR_FLAG;
		if (m_initialised) l_error = scePadReadState(m_handle, &m_padState);
		else printf("Warning: attempting to read controller data for an un-initialised controller\n");
		return l_error;
	}//update

};

#endif