#include "App.h"
#include <iostream>
#define WINDOW_Y 600
#define WINDOW_X 800
using namespace std;

App* pApp;

void InitApp(float width, float height)
{
	vec2 min, max;
	//fill in the blank
	min.x = -width/2;
	min.y = -height/2;
	max.x = width/2;
	max.y = height/2;

	pApp = new App();
	//now add textures and programs to the App
	TextureManager* pTextureManager = TextureManager::GetTextureManager();
	pTextureManager->AddTexture("images/picture.bmp");
	//programs
	ProgramManager* pProgramManager = ProgramManager::GetProgramManager();
	int programID = pProgramManager->CreateProgram("vertex.vert", "fragment.frag");
	pProgramManager->AddProgram("program1", programID);
	//add objects
	vec2 quadDimensions = {512.0f, 512.0f};
	int indices[6] = {0, 1, 3, 1, 2, 3};
	Quad* pQuad = new Quad(&quadDimensions, indices, 6, "images/picture.bmp", "program1");
	Screen* pScreen = new Screen(min.x, min.y, max.x, max.y);
	pScreen->AddObject(pQuad);
	pApp->AddObject(pScreen);
}

int main(int nArgs, char* args[])
{
	InitApp(WINDOW_X, WINDOW_Y); //creat the App and initialize it
	
	while(!pApp->done)
	{
		//"game" loop
	}
	delete pApp;
}