#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "SFML\Graphics.hpp"
#include "RobotPart.h"

using namespace sf;

class Robot {
private:
	Transform mTransform;
	Sprite m_sprite;
	RobotPart* m_part;
public:
	Robot(Vector2f pos, Texture &tex);
	~Robot();
	
	//assuming e is a key down event
	void Update(Event const &e);

	void Draw(RenderWindow &w);

	void AttachPart(RobotPart* part);

	RobotPart* getNextPart() const { return m_part; }
};
#endif