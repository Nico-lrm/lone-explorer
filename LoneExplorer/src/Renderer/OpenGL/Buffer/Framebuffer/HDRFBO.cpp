#include "HDRFBO.hpp"

HDRFBO::HDRFBO(const unsigned int& width, const unsigned int& height)
{
	// Generer la texture
	auto texMan{ TextureManager::getInstance() };
	m_mainTexturePtr = texMan->createTextureFloatBlank("mainHdrTexture", width, height);
	m_brightTexturePtr = texMan->createTextureFloatBlank("brightHdrTexture", width, height);

	// Recuperer le shader liee aux FBO
	auto shadMan{ ShaderManager::getInstance() };
	m_shaderPtr = shadMan->createShader("fbo", "fbo.vert.shader", "fbo.frag.shader");

	// Preparer le VAO & le VBO pour le dessin du buffer
	std::vector<float> quadVertices = {
		// positions        // texCoords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	m_VAO.Bind();
	m_VBO.BindData(quadVertices);

	m_VAO.linkAttribute(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	m_VAO.linkAttribute(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	m_VAO.Unbind();
	m_VBO.Unbind();

	// Gerer le FBO & le RBO
	m_depthRBO = std::make_unique<RBO>(width, height);
	auto mainTexture{ m_mainTexturePtr.lock() };
	auto brightTexture{ m_brightTexturePtr.lock() };

	this->Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mainTexture->getID(), 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, brightTexture->getID(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRBO->getID());

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("Framebuffer incomplet !");

	// Preciser dans quel buffer on ecrit
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);

	this->Unbind();

	// Initialiser un BloomFramebuffer
	m_BloomFramebuffer = std::make_unique<BloomFramebuffer>(width, height);
}

void HDRFBO::Draw()
{
	auto texture = m_mainTexturePtr.lock();
	auto shader = m_shaderPtr.lock();

	// Bind du shader et des uniforms
	shader->Bind();
	shader->setInt("hdrBuffer", 0);
	shader->setInt("bloom", 1);
	shader->setFloat("exposure", m_exposure);

	// Bind des textures
	glActiveTexture(GL_TEXTURE0);
	texture->Bind();
	glActiveTexture(GL_TEXTURE1);
	m_BloomFramebuffer->getDrawingTexture().lock()->Bind();

	// Dessiner le framebuffer
	m_VAO.Bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Unbind de securite
	m_VAO.Unbind();
	texture->Unbind();
	shader->Unbind();
	m_BloomFramebuffer->getDrawingTexture().lock()->Unbind();
}

void HDRFBO::Blur()
{
	m_BloomFramebuffer->Blur(m_VAO, m_brightTexturePtr);
}
