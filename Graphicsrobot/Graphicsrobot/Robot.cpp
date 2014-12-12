#include "Robot.h"

Robot::Robot(Vector2f pos, Texture &tex) : mTransform(Transform::Identity), m_sprite(tex){
	mTransform.translate(pos);
}

Robot::~Robot() {
}

//assuming e is a key down event
void Robot::Update(Event const & e) {
	switch (e.key.code)
	{
	case Keyboard::Right:
		mTransform.translate(Vector2f(1,0));
		break;

	case Keyboard::Left:
		mTransform.translate(Vector2f(-1,0));
		break;
	default:
		break;
	}
	m_part->Update(e);
}

void Robot::Draw(RenderWindow &w) {
	w.draw(m_sprite, mTransform);
	m_part->Draw( w );
}

void Robot::AttachPart(RobotPart* part) {
	if(m_part == NULL){
		m_part = part;
		m_part->setParent(&mTransform);
	}
	else
		m_part->AttachPart(part);
}