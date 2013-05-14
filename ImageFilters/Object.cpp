#include "Object.h"

Object::Object()
{
	objList = NULL;
}

void Object::HandleInput(bool* bKeys)
{
    //glfwGetKey(int key); <- returns either GLFW_PRESS or GLFW_RELEASE
	//go through the linked list
	for (Object* pO = this; pO != NULL; pO = pO->objList)
	    pO->HandleInput(bKeys);
}

void Object::Render()
{
     //go through the linked list
	 for (Object* pO = this; pO != NULL; pO = pO->objList)
       pO->Render();
}

void Object::Update()
{
     //go through the linked list
	 for (Object* pO = this; pO != NULL; pO = pO->objList)
       pO->Update();
}

void Object::AddObject(Object* obj)
{
	Object* pO = this;
	while (pO->objList != NULL)
		pO = pO->objList;
	//once an empty spot is found (NULL)
	//put it there
	pO->objList = obj;
}