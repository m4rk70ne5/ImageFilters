#include "Quad.h"

Quad::Quad(vec4* vertices, int numVertices, int* indices, int numIndices, string textureName, string programName) : programName(programName)
{
	//try to load texture
	TextureManager* pTextureManager = TextureManager::GetTextureManager();
	if (pTextureManager->AddTexture(textureName))
		textureID = pTextureManager->GetTexture(textureName);

	//now try to create buffers
	CreateBuffers();

	//and set the attribute pointers of the vao
	InitAttributePointers();
}

Quad::~Quad()
{
    delete [] vertices;
    delete [] vertexIndices;
}

void Quad::CreateBuffers()
{
	//generate the vertex buffer
      glGenBuffers(1, &vertexBufferID);
      glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * numVertices, vertices, GL_STATIC_DRAW); //"upload" data
      glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
      //generate the index buffer
      glGenBuffers(1, &indexBufferID);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID); //the binding to GL_ELEMENT_ARRAY_BUFFER will stay in the vao state
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, vertexIndices, GL_STATIC_DRAW);
}

void Quad::InitAttributePointers()
{
	//create vertex attribute pointers for current vao
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
