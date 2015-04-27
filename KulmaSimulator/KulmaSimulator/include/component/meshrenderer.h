#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include "DrawableComponent.h"
#include "spritebatch.h"
#include "GL\glew.h"
class Texture;
class MeshRenderer : public DrawableComponent {
private:
	Mesh* mesh;
	GLuint VBO;
	GLuint VAO;
	Effect* effect;
	Texture* texture;
public:
	MeshRenderer(Mesh* mesh);
	~MeshRenderer();
	Mesh* getMesh();
	void setTexture(Texture* tex);
protected:
	void onDraw(SpriteBatch& spriteBatch);
	void onInitialize();
};

#endif