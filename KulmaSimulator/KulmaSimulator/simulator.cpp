#include "simulator.h"
#include <iostream>


float points[] = {
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.f, 1.f,
	-0.5f, -0.5f, 0.0f, 0.f, 0.f,
	0.5f, -0.5f, 0.0f, 1.f, 0.f
	
};

GLushort indices[] = {
	0, 1, 2,
	1, 2, 3
};

Simulator::Simulator() {

}
Simulator::~Simulator() {}

void Simulator::update() {}
void Simulator::draw() { 
	effect->bind();

	glBindVertexArray(vao);
	
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->getId());
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
	
	effect->unbind();
}

void Simulator::initialize() {
	getInput().bind("Zaaryus", [](InputArgs* args) {
		std::cout << "a pressed" << std::endl;
	}, std::vector < ITrigger* > { new KeyTrigger(SDLK_a) });
	texture = content.load<Texture>("temp");
	effect = content.load<Effect>("shader\\basic");
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


}
