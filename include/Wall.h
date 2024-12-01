#pragma once
#include "Location.h"
#include <fstream>
#include <iostream>
#include <string>

class Wall
{
public:

	Wall(Location& location);
private:
	Location m_location;
};