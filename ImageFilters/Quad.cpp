#include "Quad.h"

Quad::Quad(vec2* dimensions, int* indices, int numIndices, string textureName, string programName) : programName(programName)
{
	//generate vertices based off of dimension
	//we'll go clockwise, starting from the lower left
	vec4 tempVertices[4] = {{-dimensions->x, -dimensions->y, 0.0f, 1.0f},
	{-dimensions->x, dimensions->y, 0.0f, 1.0f},
	{dimensions->x, dimensions->y, 0.0f, 1.0f},
	{dimensions->x, -dimensions->y, 0.0f, 1.0f}};
	vertices = new vec4[4];
	memcpy(vertices, tempVertices, sizeof(vec4)*4); //copy the vertices over

	//try to load texture
	TextureManager* pTextureManager = TextureManager::GetTextureManager();
	if (pTextureManager->AddTexture(textureName))
		textureID = pTextureManager->GetTexture(textureName);

	//set the texture uniform once and for all
	ProgramManager* pPM = ProgramManager::GetProgramManager();
	GLint prog = pPM->GetProgram(programName);
	GLint texLoc = glGetUniformLocation(prog, "tex");
	glProgramUniform1i(prog, texLoc, 0);

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
}

Quad::~Quad()
{
    delete [] vertices;
    delete [] vertexIndices;
	delete [] texCoords;
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
