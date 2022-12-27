#ifndef EBO_HPP
#define EBO_HPP
#pragma once
#include "../OpenGLObject.hpp"
#include <vector>

class EBO : public OpenGLObject
{
	public:
		// Constructeur - Genere le buffer
		// -------------------------------
		EBO();

		// Attacher le buffer et lui passer les indices
		// --------------------------------------------
		void BindData(std::vector<GLuint>& indices);

		// Attacher le buffer (il faut que les données soit saisies au moins une fois)
		// ---------------------------------------------------------------------------
		void Bind() override;

		// Detacher le buffer
		// ------------------
		void Unbind() override;

		// Supprimer le buffer
		// -------------------
		void Delete() override;
};
#endif