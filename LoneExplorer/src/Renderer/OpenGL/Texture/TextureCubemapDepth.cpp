#include "TextureCubemapDepth.hpp"

TextureCubemapDepth::TextureCubemapDepth(const unsigned int resolution)
{
	this->m_Resolution = resolution;
	this->Bind();

	for (unsigned int i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	this->Unbind();
}

void TextureCubemapDepth::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_ID);
}

void TextureCubemapDepth::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
