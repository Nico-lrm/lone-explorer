#include "BloomFramebuffer.hpp"

BloomFramebuffer::BloomFramebuffer(const unsigned int& width, const unsigned int& height)
{
	// Recuperer le shader liee aux BloomFBO
	auto shadMan{ ShaderManager::getInstance() };
	m_blurShaderPtr = shadMan->createShader("blur", "blur.vert.shader", "blur.frag.shader");

	// Creer les deux textures pour le bloom
	auto texMan{ TextureManager::getInstance() };
	for (unsigned i = 0; i < 2; i++)
	{
		m_arrayTexturePtr[i] = texMan->createTextureFloatBlank("bloomTex" + std::to_string(i), width, height);
	}

	// Appliquer les textures aux FBOs
	for (unsigned i = 0; i < 2; i++)
	{
		auto texture = m_arrayTexturePtr[i].lock();
		m_Framebuffers[i].Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getID(), 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw std::runtime_error("Framebuffer incomplet !");
		m_Framebuffers[i].Unbind();
	}

}

void BloomFramebuffer::Blur(VAO& refVAO, std::weak_ptr<TextureFloatBlank>& brightTex)
{
	auto blurShader{ m_blurShaderPtr.lock() };
	auto brightTexture{ brightTex.lock() };
	blurShader->Bind();

	m_horizontal = true;

	for (unsigned i = 0; i < m_amount; i++)
	{
		// Bind le framebuffer et preciser au shader si c'est un blur horizontal ou vertical
		m_Framebuffers[m_horizontal].Bind();
		blurShader->setInt("horizontal", m_horizontal);

		// Si c'est le premier tour de boucle, alors on bind la texture non floutee
		if (i == 0)
			brightTexture->Bind();
		else
			m_arrayTexturePtr[!m_horizontal].lock()->Bind();

		// Dessin de la forme floutee
		refVAO.Bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		refVAO.Unbind();

		// On inverse la valeur pour soit flouter en horizontal, soit en vertical
		m_horizontal = !m_horizontal;

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}