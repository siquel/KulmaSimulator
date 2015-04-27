#include "component/transform.h"

Transform::Transform() : transform(1.0f), rotation(1.0f), scale(1.0f) {
	
}

Transform::~Transform() {}

void Transform::setPosition(const glm::vec3& pos) {
	position = pos;
	transform = glm::translate(pos);
}

void Transform::translate(const glm::vec3& pos) {
	position += pos;
	transform = glm::translate(transform, pos);
}

void Transform::rotate(float angle, const glm::vec3& axis) {
	rotation = glm::rotate(rotation, angle, axis);
}

const glm::mat4 Transform::getTransform() const {
	return transform * rotation * scale;
}

void Transform::setScale(const glm::vec3& s) {
	scale = glm::scale(s);
}

const glm::vec3& Transform::getPosition() const {
	return position;
}

void Transform::setRotation(const glm::mat4& rot) {
	rotation = rot;
}