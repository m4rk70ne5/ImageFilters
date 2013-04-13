#include "App.h"

App::App(vec2 min, vec2 max)
{
	pScreen = new Screen(min.x, min.y, max.x, max.y);
	done = false;
}

App::~App()
{
	delete pScreen;
}