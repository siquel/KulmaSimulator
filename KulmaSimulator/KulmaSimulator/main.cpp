#include "simulator.h"
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	LOG_INFO("Starting app..");
	Simulator::getInstance().run();
	return 0;
}
	