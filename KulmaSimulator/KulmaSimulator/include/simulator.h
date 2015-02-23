#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "engine/game.h"
#include "spritebatch.h"
#include "engine\camera.h"

class Simulator : public Game  {
private:
	Camera camera;
	SpriteBatch spriteBatch;
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
};


#endif