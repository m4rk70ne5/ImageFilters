#version 430

out vec4 color; //color fragment output
in vec2 gTexCoord; //uv texture coordinates (interpolated and clamped to [0.5,.95])
				  // hopefully, since the quad the texture is being mapped to is of the same size as the texture
				  // there will be a one-to-one correspondence between the sample coordinates of the texture and quad
uniform sampler2D tex; //the texture sampler
uniform float kernelAmount;
uniform int filterIndex;

float[9] edgeFilter = float[](0, -1, 0,
							-1, 4, -1,
							0, -1, 0); //in the future, this will be a uniform
							
float[9] blurFilter = float[](1, 2, 1,
							2, 4, 2,
							1, 2, 1); //in the future, this will be a uniform
								 
float texUnit = 1/float(textureSize(tex,0)); //do this only for non-rectangular textures
//if texture is rectangular, texUnit = 1

//give ourselves the 9 texels surrounding/on the given texture
//coordinate
vec4[9] GetTextureMatrix()
{
	vec4[9] mat;
	int k = 0;
	for (int i = -1; i <= 1; i++)
	{
		for(int j = -1; i <= 1; j++, k++)
			mat[k] = texture(tex, gTexCoord.xy + vec2(i * texUnit, j * texUnit)).rgba;
	}
	return mat;
}

void main()
{
	vec4[9] data = GetTextureMatrix();
	vec4 sum = vec4(0.0f);
	float[9] kern;
	if (filterIndex == 1)
		kern = edgeFilter;
	else
		kern = blurFilter;
		
	for (int i = 0; i < 9; i++)
		sum += kern[i] * data[i];
		
	if (filterIndex == 1) // apply sharpening
		color = texture(tex, gTexCoord.xy) + sum * kernelAmount;
	else // apply blur
		color = sum / kernelAmount;
	
	// I don't know if color is clamped automatically, but I'll do it here anyway
	color = clamp(color, vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
}