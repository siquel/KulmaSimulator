#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include "DrawableComponent.h"
#include "engine/resources.h"
#include "spritebatch.h"
#include "GL\glew.h"
class MeshRenderer : public DrawableComponent {
private:
	Mesh* mesh;
	GLuint VBO;
	GLuint VAO;
	GLuint IBO;
	Effect* effect;
public:
	MeshRenderer(Mesh* mesh);
	~MeshRenderer();
protected:
	void onDraw(SpriteBatch& spriteBatch);
	void onInitialize();
};

#endif