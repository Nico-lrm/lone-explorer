#ifndef VAO_HPP
#define VAO_HPP
#pragma once

#include "../OpenGLObject.hpp"

class VAO : public OpenGLObject
{
	public:
		// Constructeur - genere le buffer
		// -------------------------------
		VAO();
		~VAO();

		// Ajouter un element de layout pour le shader
		// -------------------------------------------
		void linkAttribute(const GLuint layout, const GLint size, const GLenum type, const GLsizei stride, const void* pointer) ;

		// Attacher le buffer
		// ------------------
		void Bind() override;

		// Detacher le buffer
		// ------------------
		void Unbind() override;

		// Supprimer le buffer
		// -------------------
		void Delete() override;
};
#endif