#pragma once 
#include "ptObject.h"
#include "DrawManager.h"



void ptObject::Initialise(Matrix4 modelWorldMx)
{
	m_modelWorldMx = modelWorldMx;
}

void ptObject::Update()
{

}

void ptObject::Draw(Gnmx::GnmxGfxContext* _gfxc, ptLightEnvironment* myLightEnvironment, ptCamera* myCamera)
{

	DrawManager::GetInstance()->DrawObject(_gfxc, this, myLightEnvironment, myCamera);
}//Draw()

bool ptObject::HasCollided(ptObject& otherObject)
{
	//Calculate the squared distance between the centres of both spheres 
	Vector3 vecDistance = otherObject.m_collisionSphere.centre - m_collisionSphere.centre;
	float fdistSq = sce::Vectormath::Scalar::Aos::dot(vecDistance, vecDistance);
	
	//Calculate the squared sum of both radii
	float fRadiiSumSquared = m_collisionSphere.radius + otherObject.m_collisionSphere.radius;
	fRadiiSumSquared *= fRadiiSumSquared;

	//Check for collision
	//If the distance squared is less than or equal to the square sum
	//of the radii, then we have a collision
	if (fdistSq <= fRadiiSumSquared)
	{
		return true;
	}

	return false;
}//HasCollided()

void ptObject::Deactivate()
{
	m_isActive = false;
}//Deactivate()

void ptObject::ProcessCollision(ptObject& otherObject)
{

}//ProcessCollision()