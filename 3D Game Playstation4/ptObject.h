#ifndef __PT_OBJECT__
#define __PT_OBJECT__
#include "../../toolkit/toolkit.h"
#include "ptModel.h"
#include "ptMaterials.h"
#include "ptAssetType.h"


class ptLightEnvironment;
class ptCamera;


//Collision sphere for objects
struct CollisionSphere
{
	Vector3 centre = Vector3(0, 0, 0);   
	float radius = 1;     
};

class ptObject
{
public:
	//Attributes
	ptModel* m_myModel;
	Matrix4 m_modelWorldMx;
	ptMaterial* m_myMaterial;
	ptObjectEnum m_objectType;       
	CollisionSphere m_collisionSphere;
	bool m_isActive = true;

	//Methods
	virtual void Update();
	void Initialise(Matrix4 modelWorldMx);
	void Draw(Gnmx::GnmxGfxContext* _gfxc, ptLightEnvironment* myLightEnvironment, ptCamera* myCamera);

	//Sets m_isActive to false
	void Deactivate();

	//Calculates if object has collide with otherObject
	bool HasCollided(ptObject& otherObject);

	//Parameters
	//otherObject - runs specific code depending on the 
	//other object type
	virtual void ProcessCollision(ptObject& otherObject);


};
#endif