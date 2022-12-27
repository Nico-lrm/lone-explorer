#ifndef	MODELMANAGER_HPP
#define MODELMANAGER_HPP
#pragma once

#include "../Renderer/Model/Model.hpp"
#include "TextureManager.hpp"

class ModelManager : public Manager<Model> {
	private:
		// Singleton
		static ModelManager* m_instance;
		static std::mutex m_mutex;
		ModelManager() {};

		// Instance d'un Importer pour charger les modeles
		Assimp::Importer m_Importer;
	public:
		static ModelManager* getInstance();
		std::weak_ptr<Model> createModel(const std::string& name, const std::string& path, const bool& flipTexture);
};
#endif