#include "RobotPart.h"

RobotPart::RobotPart(Vector2f offset, Vector2f originOfRotation, Texture &tex, Keyboard::Key key1, Keyboard::Key key2, float rotationLimit, float startingRotation) :
	m_translation(Transform::Identity),
	m_rotation(Transform::Identity),
	m_origin(Transform::Identity),
	m_sprite(tex),
	cake(key1),
	lie(key2),
	rotationLimit(rotationLimit),
	startingRotation(startingRotation),
	deltaRotation(0)
{
	m_translation.translate(offset);
	m_origin.translate(originOfRotation);
}

RobotPart::~RobotPart() {
}

void RobotPart::Update(Event const &e) {

	Keyboard::Key pressed = e.key.code;

	if(pressed == cake) {
		deltaRotation -= 1;

		if(deltaRotation < -rotationLimit){
			deltaRotation += 1;
		}
	}
	else if(pressed == lie) {
		deltaRotation += 1;

		if(deltaRotation > rotationLimit) {
			deltaRotation -= 1;
		}
	}

	m_rotation = Transform::Identity;
	m_rotation.rotate(startingRotation + deltaRotation);

	//m_transform = m_origin * m_rotation * m_translation * *parent;
	m_transform = *parent * m_translation * m_rotation * m_origin;

	if(nextPart != NULL)
			nextPart->Update(e);
}

void RobotPart::Draw(RenderWindow &w) {
	w.draw( m_sprite, m_transform );
	if(nextPart != NULL)
			nextPart->Draw(w);
}

Transform RobotPart::getTransformation() const {
	return m_transform;
}

const Transform &RobotPart::getTranslation() const {
	return m_translation;
}

const Transform &RobotPart::getRotation() const {
	return m_rotation;
}

void RobotPart::AttachPart(RobotPart* part) {
	if(nextPart == NULL){
		nextPart = part;
		nextPart->setParent(&m_transform);
	}

	else
		nextPart->AttachPart(part);
}