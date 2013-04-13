#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <algorithm>
#include <string>

#include "SOIL.h"
#include "base.h"

using namespace std;

class TextureManager
{
	protected:
		map<string, int> textureHash; //the int is the texture ID, the string is the name
		static TextureManager* instance; //singleton
	public:
		TextureManager();
		static TextureManager* GetTextureManager();
		bool AddTexture(string); //string will usually be external texture file name
		int GetTexture(string); //return the ID of the texture name
};

#endif