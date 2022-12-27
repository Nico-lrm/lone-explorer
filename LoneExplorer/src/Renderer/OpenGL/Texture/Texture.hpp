#ifndef	TEXTURE_HPP
#define TEXTURE_HPP
#pragma once

#include "../OpenGLObject.hpp"

#include <stb/stb_image.h>

#include <vector>
#include <string>
#include <iostream>

class Texture : public OpenGLObject {
	protected:
		Texture() { glGenTextures(1, &(this->m_ID)); }
		~Texture() { glDeleteTextures(1, &(this->m_ID)); }
	public:
		void Delete() override { glDeleteTextures(1, &(this->m_ID)); }
};

#endif