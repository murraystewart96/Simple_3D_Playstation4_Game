#include "Entities.h"
#include "ptController.h"
#include "ptObjectManager.h"
#include "score.h"


//*****Spaceship*****//

Spaceship::Spaceship()
{
	m_collisionSphere.radius = 0.65;
}

Spaceship::~Spaceship()
{

}

void Spaceship::Update()
{

	//Track LEFT_RIGHT
	Matrix4 Xtranslation = Matrix4::translation(Vector3(m_pController->leftStickX(), 0.0, 0.0));

	//Update psoition of collision sphere
	m_collisionSphere.centre = m_modelWorldMx.getTranslation();



	//Prevent ship from going too far right
	if (m_modelWorldMx.getTranslation().getX().getAsFloat() > 5)
	{
		m_modelWorldMx.setTranslation(Vector3(5, -2.5, -5.0f));
	}

	//Prevent ship from going too far left
	if (m_modelWorldMx.getTranslation().getX().getAsFloat() < -5)
	{
		m_modelWorldMx.setTranslation(Vector3(-5, -2.5, -5.0f));
	}

	//Update ships modelworld matrix
	m_modelWorldMx =  Xtranslation * m_modelWorldMx;

	//If health is below 0 Deactivate 
	if (m_health <= 0)
	{
		m_health = 0;
		Deactivate();
	}

	
	//reduce cooldown
	m_cooldown -= 0.04;

	//Shoot if pressed and cool down <= 0
	if (m_pController->crossPressCheck() && m_cooldown <= 0)
	{
		Shoot();
		m_cooldown = 1.5;  //reset cooldown
	}
	
	//If pressed the ship takes no damage
	if (m_pController->R3PressCheck())
	{
		m_isInvincible = !m_isInvincible;
	}

}//Spaceship::Update()

void Spaceship::Shoot()
{
	//Create Rocket using the object manager
	ptObjectManager* l_OM = ptObjectManager::GetInstance();
	l_OM->AddItem(l_OM->Create(ptObjectEnum::ROCKET), true);
}//Spaceship::Shoot()

void Spaceship::ProcessCollision(ptObject& otherObject)
{
	
	//Apply a certain amount of damage specific to 
	//the other objects type


	if (otherObject.m_objectType == ptObjectEnum::ENEMY_ROCKET)
	{
		otherObject.Deactivate();   
		if (!m_isInvincible)
		{
			m_health -= 15;
		}
	}

	if (otherObject.m_objectType == ptObjectEnum::ENEMY_SHIP)
	{
		otherObject.Deactivate();
		if (!m_isInvincible)
		{
			m_health -= 100;
		}
	}

}//Spaceship::ProcessCollision()



 //*****Enemy*****//

Enemy::Enemy()
{
	m_collisionSphere.radius = 0.35;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

	//Update axial rotation 
	m_axialRot += 0.00005;

	//Updating collision sphere position
	m_collisionSphere.centre = m_modelWorldMx.getTranslation();


	//Swap direction if too far right
	if (m_modelWorldMx.getTranslation().getX().getAsFloat() > 6)
	{
		m_direction = 0;
	}

	//Swap direction if too far left
	if (m_modelWorldMx.getTranslation().getX().getAsFloat() < -6)
	{
		m_direction = 1;
	}

	//If the enemy goes past the player deactivate
	if (m_modelWorldMx.getTranslation().getZ().getAsFloat() > 2)
	{
		Deactivate();
	}

	//Update rotation matrix with new data
	Matrix4 axialRotMx = Matrix4::rotationY(m_axialRot);

	//Matrices for moving right & left
	Matrix4 moveLeft;
	Matrix4 moveRight;



	//Update modelWorld matrix depending on direction
	if (m_direction == 0)
	{
		 moveLeft = Matrix4::translation(Vector3(-m_Xspeed, 0.0, m_Zspeed));
		 m_modelWorldMx = moveLeft * m_modelWorldMx * axialRotMx;
	}
	else if (m_direction == 1)
	{
		moveRight = Matrix4::translation(Vector3(m_Xspeed, 0.0, m_Zspeed));
		m_modelWorldMx = moveRight * m_modelWorldMx * axialRotMx;
	}//else if

	
	//If health < 0 deactivate and increase player score
	if (m_health <= 0)
	{
		Score::GetInstance()->m_score += 50;
		Deactivate();
	}


	//Update timer
	m_timer += 0.02;

	//If enemy is within a certain distance & timer is above 4.3 Shoot
	if (m_timer > 4.3 && m_modelWorldMx.getTranslation().getZ().getAsFloat() > -50)
	{
		m_timer = 0;  //Reset timer
		Shoot();
	}

}//Enemy::Update

void Enemy::Shoot()
{
	//Create enemy rocket using the object manager
	ptObjectManager* l_OM = ptObjectManager::GetInstance();
	l_OM->AddItem(l_OM->CreateEnemyRocket(m_modelWorldMx), true);
}//Enemy::Shoot()

void Enemy::ProcessCollision(ptObject& otherObject)
{
	//If collided with a rocket reduce health and deactivate the rocket
	if (otherObject.m_objectType == ptObjectEnum::ROCKET)
	{
		otherObject.Deactivate();
		m_health -= 34;
	}
}//Enemy::ProcessCollision()


//*****SpaceStation*****//

SpaceStation::SpaceStation()
{

}

SpaceStation::~SpaceStation()
{

}

void SpaceStation::Update()
{

	//Update axial and orbital rotation amount
	m_axialRot += 0.025;
	m_orbitalRot += 0.005;

	//Update axial and orbital rotation matrices with new data
	Matrix4 OrbitalRotMx = Matrix4::rotationZ(m_orbitalRot);
	Matrix4 AxialRotYMx = Matrix4::rotationY(m_axialRot);
	Matrix4 AxialRotZMx = Matrix4::rotationX(m_axialRot);
	
	//Matrix which determines how far the object is from its orbital centre
	m_modelWorldMx.setTranslation((Vector3(0, 9, -2)));


	//Applying matrices to send object into orbit with local rotation 
	m_modelWorldMx = Matrix4::translation(Vector3(0, -3, -5)) * OrbitalRotMx * 
		Matrix4::translation(m_modelWorldMx.getTranslation())*  AxialRotYMx;

}//SpaceStaion::Update()


 //*****Rocket*****//

Rocket::Rocket(Matrix4 modelWorld)
{
	m_modelWorldMx = modelWorld;
	m_collisionSphere.radius = 0.35;
}

Rocket::~Rocket()
{

}

void Rocket::Update()
{
	//Updating collision sphere position
	m_collisionSphere.centre = m_modelWorldMx.getTranslation();

	//Matrix used for updating rocket Z translation
	Matrix4 Ztranslation = Matrix4::translation(Vector3(0.0, 0.0, -m_Zspeed));

	//Updating modelworld matrix 
	m_modelWorldMx = Ztranslation * m_modelWorldMx;

	//Deactivate if rocket has went passed the background
	if (m_modelWorldMx.getTranslation().getZ().getAsFloat() < -51)
	{
		Deactivate();
	}

}//Rocket::Update()

void Rocket::ProcessCollision(ptObject& otherObject)
{
	if (otherObject.m_objectType == ptObjectEnum::ENEMY_SHIP)
	{

	}
}//Rocket::ProcessCollision()



 //*****EnemyRocket*****//

EnemyRocket::EnemyRocket(Matrix4 modelWorld)
{
	m_modelWorldMx = modelWorld;
	m_collisionSphere.radius = 0.35;
}

EnemyRocket::~EnemyRocket()
{

}

void EnemyRocket::Update()
{
	//Matrix used for updating rockets Z translation
	Matrix4 Ztranslation = Matrix4::translation(Vector3(0.0, 0.0, m_Zspeed));

	//Updating collision sphere position
	m_collisionSphere.centre = m_modelWorldMx.getTranslation();

	//Updating modelWorl matrix
	m_modelWorldMx = Ztranslation * m_modelWorldMx;

	//If the rocket goes beyond the player deactivate
	if (m_modelWorldMx.getTranslation().getZ().getAsFloat() > 2)
	{
		Deactivate();
	}

}//EnemyRocket::Update()

void EnemyRocket::ProcessCollision(ptObject& otherObject)
{
	if (otherObject.m_objectType == ptObjectEnum::SPACESHIP)
	{
		
	}
}//EnemyRocket::ProcessCollision()