#include "App.h"
#include <iostream>
#define WINDOW_Y 768
#define WINDOW_X 1024
using namespace std;

void InitApp(float width, float height)
{
	vec2 min, max;
	//fill in the blank
	min.x = -width/2;
	min.y = -height/2;
	max.x = width/2;
	max.y = height/2;

	pApp = new App();
	Screen* pScreen = new Screen(min.x, min.y, max.x, max.y); // create the screen so you can start using gl functions!
	//programs
	ProgramManager* pProgramManager = ProgramManager::GetProgramManager();
	int programID = pProgramManager->CreateProgram("vertex2.vert", "fragment2.frag");
	pProgramManager->AddProgram("program1", programID);
	//now add textures and programs to the App
	TextureManager* pTextureManager = TextureManager::GetTextureManager();
	pTextureManager->AddTexture("images/picture.png");
	
	//add objects
	vec2 quadDimensions = {512.0f, 512.0f};
	GLuint indices[6] = {0, 1, 3, 3, 1, 2};
	pScreen->SetMatrixUniform(); // set the projection matrix
	Quad* pQuad = new Quad(&quadDimensions, indices, 6, "images/picture.png", "program1");
	pScreen->AddObject(pQuad);
	pApp->AddObject(pScreen);
}

int main(int nArgs, char* args[])
{
	InitApp(WINDOW_X, WINDOW_Y); //creat the App and initialize it
	
	while(!pApp->done && glfwGetWindowParam(GLFW_OPENED))
	{
		//"game" loop
		pApp->HandleInput(); //input
		//graphics
		pApp->Render();
	}
	delete pApp;
}