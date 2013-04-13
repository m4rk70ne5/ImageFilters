#ifndef APP_H
#define APP_H

#include "Screen.h"

class App : public Object
{
	protected:
		Screen* pScreen;
	public:
		bool done;
		App(vec2, vec2);
		~App();
};

#endif