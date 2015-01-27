#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "game.h"

class Simulator : public Game  {
public:
	Simulator();
	~Simulator();
	void update();
	void draw();
};


#endif