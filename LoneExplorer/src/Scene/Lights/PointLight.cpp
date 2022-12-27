#include "PointLight.hpp"

// Initialisation du nombre de pointLight
unsigned PointLight::_NumberPointLight{ 0 };

PointLight::PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const float& linear, const float& quadratic) : Light(position, ambient, diffuse, specular)
{
	this->m_IndexPointLight = PointLight::_NumberPointLight++;
	this->m_Linear = linear;
	this->m_Quadratic = quadratic;
	
	// Definir les matrices pour le DFBO des ombres
	#ifdef SHADOW_ENABLE
		setShadowMatrices();
	#endif // SHADOW_ENABLE
}

void PointLight::applyLight(const std::shared_ptr<Shader>& shaderPtr)
{
	shaderPtr->setVec3("pointLight[" + std::to_string(m_IndexPointLight) + "].position", this->m_Position);
	shaderPtr->setVec3("pointLight[" + std::to_string(m_IndexPointLight) + "].ambient", this->m_Ambient);
	shaderPtr->setVec3("pointLight[" + std::to_string(m_IndexPointLight) + "].diffuse", this->m_Diffuse);
	shaderPtr->setVec3("pointLight[" + std::to_string(m_IndexPointLight) + "].specular", this->m_Specular);
	shaderPtr->setFloat("pointLight[" + std::to_string(m_IndexPointLight) + "].constant", this->m_Constant);
	shaderPtr->setFloat("pointLight[" + std::to_string(m_IndexPointLight) + "].linear", this->m_Linear);
	shaderPtr->setFloat("pointLight[" + std::to_string(m_IndexPointLight) + "].quadratic", this->m_Quadratic);
}

void PointLight::Update()
{
	// Nettoyer les matrices pour le DFBO
	m_ShadowTransforms.clear();

	// Maj des matrices pour cubemap
	setShadowMatrices();
}

void PointLight::prepareShadow()
{
	m_DepthFBO->Bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	auto shader = m_DepthShader.lock();
	shader->Bind();

	for (unsigned int i = 0; i < 6; ++i)
		shader->setMat4("shadowMatrices[" + std::to_string(i) + "]", m_ShadowTransforms[i]);

	shader->setFloat("far_plane", FAR);
	shader->setVec3("lightPos", m_Position);
	shader->setInt("texture1", 0);
}

void PointLight::releaseShadow()
{
	auto shader = m_DepthShader.lock();
	shader->Unbind();
	m_DepthFBO->Unbind();
}
