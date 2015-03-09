#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"
#include "GLM.h"

class Transform : public Component {
public:
	Transform();
	~Transform();
	void setPosition(glm::vec3& pos);
	void translate(glm::vec3& pos);
	void rotate(float r, glm::vec3& axis);
	void setScale(glm::vec3& scale);
	const glm::mat4 getTransform() const;
private:
	glm::mat4 transform;
	glm::mat4 rotation;
	glm::mat4 scale;
};

#endif