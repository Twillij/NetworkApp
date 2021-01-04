#include "Arena.h"
#include "Tank.h"
#include <time.h>

vec3 Arena::GetRandomLocation()
{
	vec3 location;

	srand(time(NULL));
	
	location.x = (borders.x > 0) ? rand() % (int)borders.x : 0;
	location.y = (borders.y > 0) ? rand() % (int)borders.y : 0;
	location.z = (borders.z > 0) ? rand() % (int)borders.z : 0;

	return location;
}