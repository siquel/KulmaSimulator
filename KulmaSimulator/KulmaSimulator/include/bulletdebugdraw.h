#ifndef BULLETDEBUGDRAW_H
#define BULLETDEBUGDRAW_H
#include <bullet/LinearMath/btIDebugDraw.h>
#include <gl/glew.h>
#include <vector>
#include "engine\resources.h"
class GLDebugDraw : public btIDebugDraw  {
private:
	GLuint VBO;
	GLuint VAO;
	std::vector<float> vertices;
	int debugMode;
	Effect* effect;
public:
	GLDebugDraw();
	~GLDebugDraw();
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	//void drawSphere(const btVector3& p, btScalar radius, const btVector3& color);

	//void drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);

	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	void reportErrorWarning(const char* warningString);

	void draw3dText(const btVector3& location, const char* textString);
	
	void draw();

	virtual void   setDebugMode(int debugMode) {
		this->debugMode = debugMode;
	}

	virtual int      getDebugMode() const { return debugMode; }
};

#endif