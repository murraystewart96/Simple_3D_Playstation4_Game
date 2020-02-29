#include "ptCamera.h"

ptCamera::ptCamera()
{
	m_worldViewMx = Matrix4::identity();
}

void ptCamera::Reset()
{
	m_worldViewMx = Matrix4::identity();
}

void ptCamera::setPerspetive(float _angle, float _aspectRatio, float _zNear, float _zFar)
{
	m_angle = _angle;
	m_aspectRatio = _aspectRatio;
	m_zNear = _zNear;
	m_zFar = _zFar;

	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
}

void ptCamera::increaseAngle(float amount)
{
	m_angle += amount;
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
	printf("working\n");
}

void ptCamera::decreaseAngle(float amount)
{
	m_angle -= amount;
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
}

void ptCamera::increaseAspectRatio(float amount)
{
	m_aspectRatio += amount;
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
	printf("working\n");
}

void ptCamera::decreaseAspectRatio(float amount)
{
	m_aspectRatio -= amount;
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
	printf("working\n");
}

void ptCamera::increaseZnear(float amount)
{
	m_zNear += amount;
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
}

void ptCamera::decreaseZnear(float amount)
{
	m_zNear = amount;
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
}

void ptCamera::increaseZfar(float amount)
{
	m_zFar += amount;
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
}

void ptCamera::decreaseZfar(float amount)
{
	m_zFar -= amount;
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
}

void ptCamera::track_UP_DOWN(float _amount)
{
	m_worldViewMx = Matrix4::translation(Vector3(0.0, _amount, 0.0)) * m_worldViewMx;
}

void ptCamera::track_IN_OUT(float _amount)
{
	m_worldViewMx = Matrix4::translation(Vector3(0.0, 0.0, -_amount)) * m_worldViewMx;
}

void ptCamera::track_LEFT_RIGHT(float _amount)
{
	m_worldViewMx = Matrix4::translation(Vector3(-_amount, 0.0, 0.0)) * m_worldViewMx;
}


void ptCamera::pitch(float _amount)
{
	m_worldViewMx = m_worldViewMx * Matrix4::rotationX(-_amount);
}

void ptCamera::roll(float _amount)
{
	m_worldViewMx = m_worldViewMx * Matrix4::rotationZ(-_amount);
}

void ptCamera::yaw(float _amount)
{
	m_worldViewMx = m_worldViewMx * Matrix4::rotationZ(-_amount);
}


//Moves Camera left (world space right) by transforming original world-view
//by a new matrix with -amount as the x-value.
void ptCamera::trackLeftRight(float _amount)
{
	m_worldViewMx = Matrix4::translation(Vector3(-_amount, 0.0, 0.0)) * m_worldViewMx;
}//trackLeftRight()
