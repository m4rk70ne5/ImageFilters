#ifndef OBJECT_H
#define OBJECT_H

#include "base.h"

class Object
{
	protected:
		Object* objList;
	public:
		Object();
		virtual void HandleInput(bool*);
		virtual void Render();
		virtual void Update();
		void AddObject(Object*);
};

#endif