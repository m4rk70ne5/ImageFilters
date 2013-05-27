#include "Screen.h"

Screen::Screen(float x, float y, float x2, float y2)
{
	//initialize the window
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwOpenWindow((int)(x2 - x), (int)(y2 - y), 8,8,8,8,32,0, GLFW_WINDOW);
     
	//set up glew, now that a context has been created with glfwOpenWindow
	glewExperimental = GL_TRUE;
	GLenum err = glewInit(); //now intialize glew

	//create the vertex array object
	//and bind it to the current context
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	//create the projection matrix
	//use the formulas
	//remember, glsl stores matrix components in column major order
	memset(projectionMatrix, 0, sizeof(float)*16);
	projectionMatrix[0] = 2.0f/(x2 - x);
	projectionMatrix[5] = 2.0f/(y2 - y);
	projectionMatrix[10] = 1.0f; //glOrtho
	projectionMatrix[15] = 1.0f;
	projectionMatrix[12] = -((x2 + x)/(x2 - x));
	projectionMatrix[13] = -((y2 + y)/(y2 - y));
}

Screen::~Screen()
{
	// delete the next object in the list
	if (objList != NULL)
		delete objList;
}

void Screen::SetMatrixUniform()
{
	//now set the uniform once and for all
	ProgramManager* pPM = ProgramManager::GetProgramManager();
	GLint program = pPM->GetProgram("program1");
	glUseProgram(program);
	GLint projectionLoc = glGetUniformLocation(program, "projectionMatrix");
	if (projectionLoc != -1)
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (const GLfloat*)projectionMatrix);
}