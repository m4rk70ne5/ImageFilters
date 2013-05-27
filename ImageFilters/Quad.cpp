#include "Quad.h"

void AdjustScale(float amount, int prog)
{
	GLint scaleLoc = glGetUniformLocation(prog, "kernelAmount");
	glProgramUniform1f(prog, scaleLoc, amount);
}

void IncreaseScale(Object* o)
{
	Quad* pQ = static_cast<Quad*>(o);
	// program uniform
	ProgramManager* pPM = ProgramManager::GetProgramManager();
	GLint prog = pPM->GetProgram(pQ->programName);

	if (pQ->filterIndex == 1) // unsharp mask
	{
		if (pQ->kernelScale < 1.0f)
			AdjustScale(pQ->kernelScale + 0.1f, prog);
	}
	else // blur filter
	{
		if (pQ->kernelScale < 64.0f)
			AdjustScale(pQ->kernelScale * 2.0f, prog);
	}
}

void DecreaseScale(Object* o)
{
	Quad* pQ = static_cast<Quad*>(o);
	// program uniform
	ProgramManager* pPM = ProgramManager::GetProgramManager();
	GLint prog = pPM->GetProgram(pQ->programName);

	if (pQ->filterIndex == 1) // unsharp mask
	{
		if (pQ->kernelScale > 0.0f)
			AdjustScale(pQ->kernelScale-0.1f, prog);
	}
	else // blur filter
	{
		if (pQ->kernelScale > 1.0f)
			AdjustScale(pQ->kernelScale / 2.0f, prog);
	}
}

void ResetScale(Object* o)
{
	Quad* pQ = static_cast<Quad*>(o);

	// program uniform
	ProgramManager* pPM = ProgramManager::GetProgramManager();
	GLint prog = pPM->GetProgram(pQ->programName);
	GLint scaleLoc = glGetUniformLocation(prog, "kernelAmount");
	if (pQ->filterIndex == 1) // if it's the unsharp masking filter
		pQ->kernelScale = 0.0f; // set the scale to 0
	else // if it's the blur filter
		pQ->kernelScale = 1.0f; // set the scale to 1
	glProgramUniform1f(prog, scaleLoc, pQ->kernelScale); 
}

void ChangeKernels(Object* o)
{
	Quad* pQ = static_cast<Quad*>(o);
	pQ->filterIndex = (pQ->filterIndex + 1) % 2;

	// program uniform
	ProgramManager* pPM = ProgramManager::GetProgramManager();
	GLint prog = pPM->GetProgram(pQ->programName);
	GLint fiLoc = glGetUniformLocation(prog, "filterIndex");

	glProgramUniform1i(prog, fiLoc, pQ->filterIndex); 
}

Quad::Quad(vec2* dimensions, GLuint* indices, int nIndices, string textureName, string programName) : programName(programName)
{
	//generate vertices based off of dimension
	//we'll go clockwise, starting from the lower left
	numVertices = 4;
	dimensions->x /= 2;
	dimensions->y /= 2;
	vec4 tempVertices[4] = {{-dimensions->x, -dimensions->y, 0.0f, 1.0f},
	{-dimensions->x, dimensions->y, 0.0f, 1.0f},
	{dimensions->x, dimensions->y, 0.0f, 1.0f},
	{dimensions->x, -dimensions->y, 0.0f, 1.0f}};
	vertices = new vec4[4];
	memcpy(vertices, tempVertices, sizeof(vec4)*4); //copy the vertices over

	// now for indices
	numIndices = nIndices;
	vertexIndices = new GLuint[numIndices];
	memcpy(vertexIndices, indices, sizeof(GLuint)*numIndices); // copy the indices over
	

	//try to load texture
	TextureManager* pTextureManager = TextureManager::GetTextureManager();
	textureID = pTextureManager->GetTexture(textureName);
	glActiveTexture(GL_TEXTURE0);

	//set the texture uniform once and for all
	ProgramManager* pPM = ProgramManager::GetProgramManager();
	GLint prog = pPM->GetProgram(programName);
	GLint texLoc = glGetUniformLocation(prog, "tex");
	glProgramUniform1i(prog, texLoc, 0);

	// set the filter uniforms
	kernelScale = 0.0f;
	filterIndex = 1;
	GLint scaleLoc = glGetUniformLocation(prog, "kernelAmount");
	GLint fiLoc = glGetUniformLocation(prog, "filterIndex");
	glProgramUniform1f(prog, scaleLoc, kernelScale);
	glProgramUniform1i(prog, fiLoc, filterIndex);

	//texture coordinate time!
	//very simple and straightforward:  standard coordinate winding
	vec2 tempTexcoords[4] = {{0.0f, 0.0f}, 
	{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};
	texCoords = new vec2[4];
	memcpy(texCoords, tempTexcoords, sizeof(vec2)*4);

	//now try to create buffers
	CreateBuffers();

	//and set the attribute pointers of the vao
	InitAttributePointers();

	// now, register the keys that this object will be using
	RegisterKey('+', IncreaseScale, false);
	RegisterKey('-', DecreaseScale, false);
	RegisterKey('r', ResetScale, false);
	RegisterKey(GLFW_KEY_SPACE, ChangeKernels, false);
}

Quad::~Quad()
{
    delete [] vertices;
    delete [] vertexIndices;
	delete [] texCoords;

	if (objList != NULL)
		delete objList;
}

void Quad::CreateBuffers()
{
	//generate the vertex buffer
      glGenBuffers(1, &vertexBufferID);
      glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * numVertices, vertices, GL_STATIC_DRAW); //"upload" data
	  //generate texture coordinate buffer
	  glGenBuffers(1, &texCoordBufferID);
	  glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferID);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * numVertices, texCoords, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
      //generate the index buffer
      glGenBuffers(1, &indexBufferID);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID); //the binding to GL_ELEMENT_ARRAY_BUFFER will stay in the vao state
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, vertexIndices, GL_STATIC_DRAW);
}

void Quad::InitAttributePointers()
{
	//create vertex attribute pointers for current vao
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID); //make sure it references vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//and also the texture coordinate attribute pointers
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferID); //now for texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Quad::Render()
{
	// use its own program
	ProgramManager* pProgramManager = ProgramManager::GetProgramManager();
	glUseProgram(pProgramManager->GetProgram(programName));
	// texture mapping
	glBindTexture(GL_TEXTURE_2D, textureID);
	//draw triangles
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0); // unbind texture
	// call base class function
	Object::Render();
}