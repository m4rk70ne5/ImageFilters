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
	// SOIL can't work directly with modern OpenGL, so we can only 
	// low the raw image 
	int width, height, channels;
    unsigned char* data = SOIL_load_image(texture_string.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

	//generate the texture
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data); // free the memory

	//store texture if successful
    if (texture_ID == 0)
        return false;
	textureHash[texture_string] = texture_ID;

	//set the default border color
	//float defaultColor[4] = {0.0f, 0.0f, 0.0f, 1.0f}; //black
    // Typical Texture Generation Using Data From The Bitmap
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