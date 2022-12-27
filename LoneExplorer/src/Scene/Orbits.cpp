#include "Orbits.hpp"

Orbits::Orbits()
{
	GLfloat xx;
	GLfloat zz;
	float angl;

	for (int i = 0; i < 2000; i++)
	{
		angl = (float)(std::numbers::pi_v<float> / 2 - i * (std::numbers::pi_v<float> / 1000));
		xx = sin(angl) * 100.0f;
		zz = cos(angl) * 100.0f;
		m_OrbitVertex.push_back(xx);
		m_OrbitVertex.push_back(0.0f);
		m_OrbitVertex.push_back(zz);

	}

	// Ligne pour les orbites
	m_VAO.Bind();
	m_VBO.BindData(m_OrbitVertex);
	m_VAO.linkAttribute(0, 3, GL_FLOAT, sizeof(float) * 3, 0);
	m_VBO.Unbind();
	m_VAO.Unbind();

	// Recuperer un shader basique pour les lignes
	auto shadMan{ ShaderManager::getInstance() };
	m_LineShader = shadMan->createShader("simpleShader", "simple.vert.shader", "simple.frag.shader");
}

void Orbits::Draw(glm::mat4 viewProjMatrix)
{
	// Lock le shader pour l'utilisation
	auto shaderPtr = m_LineShader.lock();

	// Uniform
	shaderPtr->Bind();
	shaderPtr->setMat4("viewProj", viewProjMatrix);

	//Definir la taille d'une ligne
	m_VAO.Bind();
	glLineWidth(0.25f);


	// Parcourir l'ensemble des donnees pour dessiner chaque ligne
	for (auto& pair : m_Data)
	{
		glm::mat4 modelorb;
		modelorb = glm::mat4(1.0);

		if (!pair.first.expired()) 
		{
			modelorb = glm::translate(modelorb, pair.first.lock()->getPosition());
		}
		else 
		{
			modelorb = glm::translate(modelorb, glm::vec3(0.f));
		}


		modelorb = glm::scale(modelorb, glm::vec3(pair.second / 100));
		shaderPtr->setMat4("model", modelorb);
		glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)m_OrbitVertex.size() / 3);
	}

	// Unbind le tout
	shaderPtr->Unbind();
}

void Orbits::addNewOrbit(const std::weak_ptr<Celestial>& celestialRef, const float& xCoord)
{
	m_Data.push_back(std::make_pair(celestialRef, xCoord));
}

void Orbits::removeOrbit(int id)
{
}

void Orbits::clearOrbits()
{
	m_Data.clear();
}
