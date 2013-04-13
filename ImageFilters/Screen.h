#ifndef SCREEN_H
#define SCREEN_H

#include "Quad.h"

class Screen : public Object
{
	protected:
		GLuint vao;
	public:
		Screen(float, float, float, float); //min x and y, max x and y
		~Screen();
};

#endif