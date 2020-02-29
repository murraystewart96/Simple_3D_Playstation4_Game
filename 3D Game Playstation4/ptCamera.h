#ifndef __PT_CAMERA__
#define __PT_CAMERA__

#include "../../toolkit/toolkit.h"





using namespace std;

class ptCamera
{
public:
	Matrix4 m_projectionMx;
	Matrix4 m_worldViewMx;

	float m_angle;
	float m_aspectRatio;
	float m_zNear;
	float m_zFar;

	ptCamera();


	void Reset();
	
	
	void setPerspetive(float _angle, float _aspectRatio, float _zNear, float _zFar);


	void increaseAngle(float amount);


	void decreaseAngle(float amount);


	void increaseAspectRatio(float amount);


	void decreaseAspectRatio(float amount);


	void increaseZnear(float amount);


	void decreaseZnear(float amount);
	

	void increaseZfar(float amount);


	void decreaseZfar(float amount);


	void track_UP_DOWN(float _amount);


	void track_IN_OUT(float _amount);


	void track_LEFT_RIGHT(float _amount);



	void pitch(float _amount);


	void roll(float _amount);


	void yaw(float _amount);
	


	//Moves Camera left (world space right) by transforming original world-view
	//by a new matrix with -amount as the x-value.
	void trackLeftRight(float _amount);


	



};


#endif
