#ifndef OBJECT_H
#define OBJECT_H

class Object
{
	virtual void HandleInput(bool*, Object*);
	virtual void Render(Object*);
	virtual void Update(Object*);
};

#endif