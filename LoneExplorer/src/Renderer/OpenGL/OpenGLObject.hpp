#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP 
#pragma once

#include <GL/glew.h>

#include "../../Settings.hpp"

// Classe abstraite pour les objets OpenGL (shader, buffers, texture...)
class OpenGLObject {
	protected:
		GLuint m_ID = 0;
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

		inline const GLuint getID() { return this->m_ID; }
};

#endif