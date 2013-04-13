#ifndef QUAD_H
#define	QUAD_H

#include "TextureManager.h"
#include "ProgramManager.h"
#include "Object.h"

struct vec4
{
	float x;
	float y;
	float z;
	float w;
};

struct vec2
{
	float x;
	float y;
};

class Quad : public Object
{
	protected:
		int textureID;
		string programName;
		int numVertices, numIndices;
		vec4* vertices;
		int* vertexIndices;
		int vertexBufferID, indexBufferID;
		void CreateBuffers();
		void InitAttributePointers();
	public:
		Quad(vec4*, int*, string);
		~Quad();
}

#endif