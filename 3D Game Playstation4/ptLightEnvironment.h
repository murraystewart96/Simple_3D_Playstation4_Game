#ifndef __PT_LIGHT_ENVIRONMENT__
#define __PT_LIGHT_ENVIRONMENT__
#include "ptLightCount.h"
#include "ptLight.h"
class ptLightEnvironment
{
public:
	ptLight m_lights[PT_LIGHT_COUNT];
};

#endif