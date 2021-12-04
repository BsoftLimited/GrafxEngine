#ifndef UTILS_H
	#define UTILS_H

#include <stdio.h>
#include <cmath>

namespace grafx{
	double toRadians(double degrees){
		return degrees * (3.142 /180.0);
	}
	
	double toDegrees(float radians){
		return radians * (180.0 / 3.142);
	}
}

#endif
