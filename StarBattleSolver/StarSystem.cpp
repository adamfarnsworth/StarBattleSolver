#include "StarSystem.h"

void StarSystem::insertRow(){
	row* solarSystem = new row();

}

StarSystem::StarSystem(int size, int stars)
{
	// all collumns are 0
	collumns.reserve(size);

	this->size = size;
	this->stars = stars;
}


StarSystem::~StarSystem()
{
}
