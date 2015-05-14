#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "engine/game.h"
#include "spritebatch.h"
#include "engine\camera.h"
#include <queue>
class Simulator : public Game  {
private:
	Camera camera;
	SpriteBatch spriteBatch;
	std::queue<std::function<void()>> pendingActions;
	Simulator();
	~Simulator();

	Simulator(Simulator const&) = delete;
	void operator=(Simulator const&) = delete;
public:
	static Simulator& getInstance() {
		static Simulator instance;
		return instance;
	}
	void update(float tpf);
	void draw();
	void initialize();
	Camera& getCamera();
	void doNextFrame(std::function<void() > action);
};


#endif