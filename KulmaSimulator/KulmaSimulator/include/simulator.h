#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "game.h"
#include "spritebatch.h"

class Simulator : public Game  {
private:
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
};


#endif