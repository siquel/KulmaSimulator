#include "simulator.h"
#include <iostream>

Simulator::Simulator() {

}
Simulator::~Simulator() {}

void Simulator::update(float tpf) {
	stateManager.update(tpf);
}
void Simulator::draw() {
	// TODO pass spritebatch maybe?
	stateManager.draw();
	spriteBatch.begin(SpriteSortMode::Deferred);
	glm::vec4 src(0.f, 0.f, 200.f, 100.f);
	spriteBatch.draw(glm::vec2(0.f, 0.f), texture, &src, glm::vec2(1.5f, 1.5f), glm::vec2(0.f, 0.f));
	
	//spriteBatch.draw(glm::vec2(400.f, 100.f), texture, nullptr);
	//spriteBatch.draw(glm::vec2(200.f, 400.f), texture2, nullptr);
	
	//spriteBatch.draw(glm::vec2(500.f, 500.f), texture, nullptr);
	//spriteBatch.draw(glm::vec2(200.f, 200.f), texture2, nullptr);

	//spriteBatch.draw(glm::vec2(200.f, 600.f), texture2, nullptr);
	//spriteBatch.draw(glm::vec2(300.f, 300.f), texture3, nullptr);
	//spriteBatch.draw(glm::vec2(200.f, 700.f), texture2, nullptr);
	//spriteBatch.draw(glm::vec2(700.f, 300.f), texture3, nullptr);
	spriteBatch.end();
}

void Simulator::initialize() {
	getInput().bind("Zaaryus", [](InputArgs args) {
		if (args.state == InputState::PRESSED)
			std::cout << "a pressed" << std::endl;
	}, std::vector < ITrigger* > { new KeyTrigger(SDLK_a) });
	
	spriteBatch.init();
	texture = content.load<Texture>("pidgin");
	texture2 = content.load<Texture>("temp");
	texture3 = content.load<Texture>("dolan");
	effect = content.load<Effect>("shader\\basic");
	getStateManager().push(new GameplayState);
	
}
