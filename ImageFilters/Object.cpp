#include "Object.h"

Object::Object()
{
	objList = NULL;
}

Object::~Object()
{
	// delete keys
}

void Object::HandleInput()
{
    //go through all registered key handlers
	for (int i = 0; i < keys.size(); i++)
	{
		int pressState = glfwGetKey(keys[i]); // returns either GLFW_PRESS or GLFW_RELEASE
		tKey* temp = keyMap[keys[i]];
		if (temp->holdFlag)
		{
			// if holds are allowed
			if (temp->depressedFlag = (pressState == GLFW_PRESS))
				temp->keyFunction(); // just execute the function as long as the key is depressed
		}
		else
		{
			if (pressState == GLFW_PRESS && temp->depressedFlag == false)
			{
				// key must have been previously "undepressed" in order for function to execute
				temp->keyFunction();
				temp->depressedFlag = true;
			}
			else if (pressState == GLFW_RELEASE && temp->depressedFlag == true)
				temp->depressedFlag = false; // as soon as user releases key, set its depressed flag to false
		}
	}
	//go through the linked list
	for (Object* pO = this->objList; pO != NULL; pO = pO->objList)
	    pO->HandleInput();
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

void Object::RegisterKey(int key, pfuncVoid func, bool holdflag)
{
	// create new key
	tKey* pKey = new tKey;
	pKey->depressedFlag = false;
	pKey->holdFlag = holdflag;
	pKey->keyFunction = func;	
	
	// add vector entry
	keys.push_back(key);

	// add map entry
	keyMap[key] = pKey;
}