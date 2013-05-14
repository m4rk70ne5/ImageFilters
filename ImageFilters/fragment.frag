#version 430

out vec4 color; //color fragment output
in vec2 texCoord;
uniform sampler2D texture; //the texture sampler

float[9] blurFilter = float[](0, 1/8, 0,
							1/8, 1/2, 1/8,
							0, 1/8, 0); //in the future, this will be a uniform
								 
float texUnit = 1/float(textureSize(texture,0)); //do this only for non-rectangular textures
//if texture is rectangular, texUnit = 1

//give ourselves the 9 texels surrounding/on the given texture
//coordinate
vec4[9] GetTextureMatrix()
{
	float[9] mat;
	int k = 0;
	for (int i = -1; i <= 1; i++)
	{
		for(int j = -1; i <= 1; j++, k++)
			mat[k] = texture(texture, textureCoord.xy + vec2(i * texUnit, j * texUnit));
	}
	return mat;
}

void main()
{
	float[9] data = GetTextureMatrix();
	float sum = 0;
	for (int i = 0; i < 9; i++)
		sum += blurFilter[i] * data[i];
	color = sum;
}