#ifndef RBO_HPP 
#define RBO_HPP

#pragma once

#include "../OpenGLObject.hpp"

class RBO : public OpenGLObject {
	public:
		RBO(const unsigned int& width, const unsigned int& height);
		RBO();

		void Bind() override;
		void Unbind() override;
		void Delete() override;

		void setRenderbufferStorage(const unsigned int& width, const unsigned int& height);
		void setRenderbufferStorageMultisample(const unsigned int& sample, const unsigned int& width, const unsigned int& height);
};
#endif