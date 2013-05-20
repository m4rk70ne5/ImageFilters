#include "TextureManager.h"

TextureManager* TextureManager::instance = NULL; //definition of static member

TextureManager::TextureManager()
{
}

TextureManager* TextureManager::GetTextureManager()
{
	if (instance == NULL)
		instance = new TextureManager;
	return instance;
}

bool TextureManager::AddTexture(string texture_string)
{
	GLuint texture_ID;
    //now load the texture with SOIL
    texture_ID = SOIL_load_OGL_texture(texture_string.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    
	//store texture if successful
    if (texture_ID == 0)
        return false;
	textureHash[texture_string] = texture_ID;

	//set the default border color
	//float defaultColor[4] = {0.0f, 0.0f, 0.0f, 1.0f}; //black
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture_ID);
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, defaultColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //makes all texels fall within the range [0.5, .95]
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // no unintentional filtering desired
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0); //unbind the texture
    return true;
}

int TextureManager::GetTexture(string textureName)
{
	return textureHash[textureName];
}