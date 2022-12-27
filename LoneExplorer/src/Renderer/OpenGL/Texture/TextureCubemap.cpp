#include "TextureCubemap.hpp"

TextureCubemap::TextureCubemap(const std::vector<std::string>& filepaths, const bool& srgb) : m_Filepaths(filepaths)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_ID);

	stbi_set_flip_vertically_on_load(false);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < filepaths.size(); i++)
	{
		std::string filepath{ filepaths[i] };

		unsigned char* data{ stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0) };
		if (data)
		{
			if (srgb)
			{
				if (nrChannels == 4)
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				else if (nrChannels == 3)
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				else if (nrChannels == 1)
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
				else
					throw std::runtime_error("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image\n");
			}
			else
			{
				if (nrChannels == 4)
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				else if (nrChannels == 3)
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				else if (nrChannels == 1)
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
				else
					throw std::runtime_error("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image\n");
			}
		}
		else
		{
			throw std::invalid_argument(std::string("Impossible de lire la texture cubemap : " + filepaths[i]).c_str());
		}
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubemap::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_ID);
}

void TextureCubemap::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
