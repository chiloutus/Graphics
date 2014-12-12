#ifndef _ROBOT_PART_H
#define _ROBOT_PART_H

#include "SFML\Graphics.hpp"

using namespace sf;

class RobotPart {
private:
	Transform m_translation, m_rotation, m_origin;
	Transform m_transform;
	Transform* parent;
	Sprite m_sprite;
	RobotPart* nextPart;
	const Keyboard::Key cake;
	const Keyboard::Key lie;

	const float rotationLimit;
	const float startingRotation;
	float deltaRotation;

public:
	RobotPart(Vector2f offset, Vector2f originOfRotation, Texture &tex, Keyboard::Key key1, Keyboard::Key key2, float rotationLimit, float startingRotation);
	~RobotPart();

	void Update(Event const &e);

	void Draw(RenderWindow &w);

	Transform getTransformation() const;
	const Transform &getTranslation() const;
	const Transform &getRotation() const;

	void AttachPart(RobotPart* part);

	void setParent(Transform* newParent) { parent = newParent; }

	RobotPart* getNextPart() const { return nextPart; }
};
#endif