#pragma once
#include "Box2D\Box2D.h"
#include "GL\glew.h"
#include <vector>
class Effect;
class Box2DDebugDraw : public b2Draw {
private:
	GLuint VAO;
	GLuint VBO;
	std::vector<float> vertices;
	Effect* effect;
public:
	Box2DDebugDraw();
	~Box2DDebugDraw();
	void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& tf);
	void doDraw();
};