#pragma once


#define _USE_MATH_DEFINES
#include <math.h>

namespace gaijin
{
	namespace maths
	{
		inline float toRadians(float degrees)
		{
			return (float)((double)degrees * (M_PI / (double)180.0f));
		}
	}
}