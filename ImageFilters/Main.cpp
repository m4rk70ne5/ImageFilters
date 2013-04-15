#include "App.h"
#include <iostream>
using namespace std;

App* pApp;

void InitApp()
{
	vec2 min, max;
	//fill in the blank
	min.x = 0;
	min.y = 0;
	max.x = 0;
	max.y = 0;

	pApp = new App(min, max);
	//now add textures and programs to the App
	TextureManager* pTextureManager = TextureManager::GetTextureManager();
	pTextureManager->AddTexture("picture.bmp");
	//programs
	ProgramManager* pProgramManager = ProgramManager::GetProgramManager();
	int programID = pProgramManager->CreateProgram("vertexShader.vert", "fragmentShader.vert");
	pProgramManager->AddProgram("program1", programID);
}

int main(int nArgs, char* args[])
{
	InitApp(); //creat the App and initialize it
	
	while(!pApp->done)
	{
		//"game" loop
	}
	delete pApp;
}