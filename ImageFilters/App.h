#ifndef APP_H
#define APP_H

#include "Screen.h"

void CloseApp();

class App : public Object
{
	friend void CloseApp(); // callback function
	public:
		bool done;
		App();
		~App();
		virtual void Render();
};

extern App* pApp; // I guess I could have made the App class a singleton.  :/

#endif