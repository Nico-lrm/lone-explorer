#include "TextureFile.hpp"

TextureFile::TextureFile(const std::string& filepath, const TextureType& type, const bool& flipUV, const bool& srgb)
{
	glBindTexture(GL_TEXTURE_2D, m_ID);

	stbi_set_flip_vertically_on_load(flipUV);

	//On defini les parametres comme la repetition de la texture et la methode de filtrage sur la texture actuellement attachee
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Definir le type de la texture
	this->m_Type = type;

	//On recupere les informations concernant le fichier en le chargeant grace a stb_image
	int widthImg, heightImg, nbChannel;

	unsigned char* data{ stbi_load(filepath.c_str(), &widthImg, &heightImg, &nbChannel, 0) };
	if (data)
	{
		if (srgb) 
		{
			//S'il y a bien eu recuperation de donnees, on verifie le nombre de canaux disponibles sur l'image
			if (nbChannel == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else if (nbChannel == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else if (nbChannel == 1)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			else
				throw std::invalid_argument("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image\n");
		}
		else
		{
			if (nbChannel == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else if (nbChannel == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else if (nbChannel == 1)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			else
				throw std::invalid_argument("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image\n");
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		throw std::runtime_error("Erreur : Impossible de lire le fichier utilise comme texture");

	//On libere l'image une fois la texture chargee
	stbi_image_free(data);

	//On unbind la texture pour eviter toute modification incongrue
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureFile::Bind()
{
	glBindTexture(GL_TEXTURE_2D, this->m_ID);
}

void TextureFile::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}