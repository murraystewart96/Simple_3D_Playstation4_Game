#ifndef __ENTITIES__
#define __ENTITIES__
#include "ptObject.h"

class ptController;

class Spaceship : public ptObject
{
public:
	//Attributes
	ptController* m_pController;   
	float m_health = 100;
	float m_cooldown = 0;  //shoot cooldown
	float m_isInvincible = false;

	//Constructor/Destructor//Methods
	Spaceship();
	~Spaceship();

	//Methods
	void Update();
	void ProcessCollision(ptObject& otherObject);
	void Shoot();
};



class Enemy : public ptObject
{
public :
	//Attributes
	bool m_isAlive = true;
	float m_health = 100;       
	float m_axialRot = 0;
	int m_direction = 0;
	float m_Xspeed = 0.05;
	float m_Zspeed = 0.06;
	float m_timer = 0;     //shoot timer


	//Constructor/Destructor
	Enemy();
	~Enemy();
	void Shoot();

	//Methods
	void Update();
	void ProcessCollision(ptObject& otherObject);
};



class SpaceStation : public ptObject
{
public:
	//Attributes
	bool m_isAlive = true;
	float m_health = 100;
	float m_axialRot = 0;
	float m_orbitalRot = 0;
	int m_id = 0;

	//Constructor/Destructor
	SpaceStation();
	~SpaceStation();

	//Methods
	void Update();
};



class Rocket : public ptObject
{
public:
	//Attributes
	float m_damage = 30;
	float m_Zspeed = 0.5;

	//Constructor/Destructor
	Rocket(Matrix4 modelWorld);
	~Rocket();


	//Methods
	void Update();
	void ProcessCollision(ptObject& otherObject);
};


class EnemyRocket : public ptObject
{
public:
	//Attributes
	float m_damage = 15;
	float m_Zspeed = 0.4;

	//Constructor/Destructor
	EnemyRocket(Matrix4 modelWorld);
	~EnemyRocket();

	//Methods
	void Update();
	void ProcessCollision(ptObject& otherObject);
};


#endif