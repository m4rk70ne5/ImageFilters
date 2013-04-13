#include "Screen.h"

Screen::Screen(float x, float y, float x2, float y2)
{
	//set up glfw
	glfwInit();
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwOpenWindow(x2 - x, y2 - y, 8,8,8,8,32,0, GLFW_WINDOW);
     
	//set up glew, now that a context has been created with glfwOpenWindow
	glewExperimental = GL_TRUE;
	GLenum err = glewInit(); //now intialize glew

	//create the vertex array object
	//and bind it to the current context
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
}