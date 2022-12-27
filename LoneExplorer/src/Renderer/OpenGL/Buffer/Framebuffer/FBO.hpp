#ifndef FBO_HPP 
#define FBO_HPP

#pragma once
#include "../../OpenGLObject.hpp"

class FBO : public OpenGLObject {
	public:
		FBO() { glGenFramebuffers(1, &(this->m_ID)); };
		~FBO() { glDeleteFramebuffers(1, &this->m_ID); }

		void Bind() override {
			glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);
		};
		void Unbind() override {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		};
		void Delete() override {
			glDeleteFramebuffers(1, &this->m_ID);
		};
};
#endif