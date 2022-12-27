#ifndef MANAGER_HPP
#define MANAGER_HPP
#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <mutex>

template<class T>
class Manager {
    protected:
        std::unordered_map <std::string, std::shared_ptr<T>> m_elementMap;

        // Pour les types specifiques (Textures)
        template<typename U>
	    std::weak_ptr<U> getElementByName(const std::string& name)
	    {
            // On vérifie si l'iterateur trouve bien l'element
            auto it{ this->m_elementMap.find(name) };

            // Si le shader n'est pas trouve dans la map
            if (it == m_elementMap.end())
            {
                return std::weak_ptr<U>();
            }

            // Sinon, on renvoie un observer de celui-ci
            return std::weak_ptr<U>(std::dynamic_pointer_cast<U>(it->second));
	    }

    public:

        // Pour les elements globaux a recuperer (Shader & Model)
        std::weak_ptr<T> getElementByName(const std::string& name)
        {
            // On vérifie si l'iterateur trouve bien l'element
            auto it{ this->m_elementMap.find(name) };

            // Si le shader n'est pas trouve dans la map
            if (it == m_elementMap.end())
            {
                return std::weak_ptr<T>();
            }

            // Sinon, on renvoie un observer de celui-ci
            return std::weak_ptr<T>(it->second);
        }

        void clearManager() 
        {
            this->m_elementMap.clear();
        }
        
        void deleteElement(const std::string& name) 
        {
            this->m_elementMap.erase(name);
        }
};
#endif