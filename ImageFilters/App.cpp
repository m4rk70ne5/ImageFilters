#include "App.h"

App* pApp;

void CloseApp(Object* o)
{
	pApp->done = true;
}

App::App()
{
	done = false;
	//set up glfw
	glfwInit();
	//register key
	RegisterKey(GLFW_KEY_ESC, CloseApp, false);
}

App::~App()
{
	// delete the next object in the linked list
	if (objList != NULL)
		delete objList;
	glfwTerminate();
}

void App::Render()
{
	// OpenGL rendering code goes here...
	glClear(GL_COLOR_BUFFER_BIT); // clear the back buffer

	// draw all the objects
	Object::Render();

	// swap buffers
	glfwSwapBuffers();
}