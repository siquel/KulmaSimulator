#include "component/transform.h"

Transform::Transform() : transform(1.0f), rotation(1.0f), scale(1.0f) {
	
}

Transform::~Transform() {}

void Transform::setPosition(glm::vec3& pos) {
	position = pos;
	transform = glm::translate(pos);
}

void Transform::translate(glm::vec3& pos) {
	position += pos;
	transform = glm::translate(transform, pos);
}

void Transform::rotate(float angle, glm::vec3& axis) {
	rotation = glm::rotate(rotation, angle, axis);
}

const glm::mat4 Transform::getTransform() const {
	return transform * rotation * scale;
}

void Transform::setScale(glm::vec3& s) {
	scale = glm::scale(s);
}

const glm::vec3& Transform::getPosition() const {
	return position;
}