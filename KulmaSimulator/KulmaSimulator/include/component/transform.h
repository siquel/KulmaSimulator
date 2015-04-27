#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"
#include "GLM.h"

class Transform : public Component {
public:
	Transform();
	~Transform();
	void setPosition(const glm::vec3& pos);
	void translate(const glm::vec3& pos);
	void rotate(float r, const glm::vec3& axis);
	void setScale(const glm::vec3& scale);
	void setRotation(const glm::mat4& rot);
	const glm::mat4 getTransform() const;
	const glm::vec3& getPosition() const;
private:
	glm::vec3 position;
	glm::mat4 transform;
	glm::mat4 rotation;
	glm::mat4 scale;
};

#endif