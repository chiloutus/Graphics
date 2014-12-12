#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "SFML\Graphics.hpp"
#include "RobotPart.h"

using namespace sf;

class Balloon : public Sprite {
private:
	
public:
	Balloon();
	~Balloon();
	
	void Draw(RenderWindow &w);
};
#endif