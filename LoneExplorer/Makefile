#Variable
CC=g++
CFLAGS= -std=c++20
LDFLAGS= -lGL -lGLEW -lglfw -lassimp -lstb

objects= Main.o Application.o SceneManager.o ShaderManager.o TextureManager.o ModelManager.o RenderWindow.o Model.o Mesh.o DepthFramebuffer.o BloomFramebuffer.o HDRFBO.o EBO.o RBO.o SSBO.o VAO.o VBO.o Shader.o TextureBlank.o TextureFloatBlank.o TextureFile.o TextureCubemap.o TextureCubemapDepth.o Scene.o SpaceScene.o Orbits.o Skybox.o Camera.o Celestial.o Asteroid.o PointLight.o

.PHONY: clean

#Principal
app: $(objects)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	rm -rf *.o *.gch

#Main
Main.o: src/Main.cpp src/Application.hpp src/Settings.hpp
	$(CC) $(CFLAGS) -c $<

#Application
Application.o: src/Application.cpp src/Application.hpp src/Settings.hpp src/Manager/ModelManager.hpp src/Manager/ShaderManager.hpp src/Manager/SceneManager.hpp src/Manager/TextureManager.hpp src/Renderer/RenderWindow.hpp
	$(CC) $(CFLAGS) -c $<

#Managers
SceneManager.o : src/Manager/SceneManager.cpp src/Manager/SceneManager.hpp src/Manager/Manager.hpp src/Scene/SpaceScene.hpp
	$(CC) $(CFLAGS) -c $<

ShaderManager.o : src/Manager/ShaderManager.cpp src/Manager/ShaderManager.hpp src/Manager/Manager.hpp src/Renderer/OpenGL/Shader/Shader.hpp
	$(CC) $(CFLAGS) -c $<

TextureManager.o : src/Manager/TextureManager.cpp src/Manager/TextureManager.hpp src/Manager/Manager.hpp src/Renderer/OpenGL/Texture/TextureBlank.hpp src/Renderer/OpenGL/Texture/TextureFile.hpp src/Renderer/OpenGL/Texture/TextureCubemap.hpp src/Renderer/OpenGL/Texture/TextureCubemapDepth.hpp src/Renderer/OpenGL/Texture/TextureDepth.hpp src/Renderer/OpenGL/Texture/TextureFloatBlank.hpp
	$(CC) $(CFLAGS) -c $<

ModelManager.o : src/Manager/ModelManager.cpp src/Manager/ModelManager.hpp src/Manager/TextureManager.hpp src/Renderer/Model/Model.hpp
	$(CC) $(CFLAGS) -c $<

#Renderer
RenderWindow.o : src/Renderer/RenderWindow.cpp src/Renderer/RenderWindow.hpp src/Settings.hpp src/Scene/Scene.hpp src/Renderer/OpenGL/Buffer/Framebuffer/HDRFBO.hpp src/Manager/SceneManager.hpp
	$(CC) $(CFLAGS) -c $<

Model.o : src/Renderer/Model/Model.cpp src/Renderer/Model/Model.hpp src/Renderer/Model/Mesh.hpp src/Manager/TextureManager.hpp
	$(CC) $(CFLAGS) -c $<

Mesh.o : src/Renderer/Model/Mesh.cpp src/Renderer/Model/Mesh.hpp src/Renderer/OpenGL/Buffer/VAO.hpp src/Renderer/OpenGL/Buffer/VBO.hpp src/Renderer/OpenGL/Buffer/EBO.hpp src/Renderer/OpenGL/Shader/Shader.hpp src/Renderer/OpenGL/Texture/TextureFile.hpp src/Scene/Lights/PointLight.hpp src/Settings.hpp
	$(CC) $(CFLAGS) -c $<

DepthFramebuffer.o : src/Renderer/OpenGL/Buffer/Framebuffer/DepthFramebuffer.cpp src/Renderer/OpenGL/Buffer/Framebuffer/DepthFramebuffer.hpp src/Manager/TextureManager.hpp src/Renderer/OpenGL/Buffer/Framebuffer/FBO.hpp
	$(CC) $(CFLAGS) -c $<

BloomFramebuffer.o : src/Renderer/OpenGL/Buffer/Framebuffer/BloomFramebuffer.cpp src/Settings.hpp src/Renderer/OpenGL/Buffer/Framebuffer/BloomFramebuffer.hpp src/Manager/TextureManager.hpp src/Manager/ShaderManager.hpp src/Renderer/OpenGL/Buffer/Framebuffer/FBO.hpp src/Renderer/OpenGL/Buffer/VAO.hpp
	$(CC) $(CFLAGS) -c $<

HDRFBO.o : src/Renderer/OpenGL/Buffer/Framebuffer/HDRFBO.cpp src/Settings.hpp src/Renderer/OpenGL/Buffer/Framebuffer/HDRFBO.hpp src/Renderer/OpenGL/Buffer/Framebuffer/BloomFramebuffer.hpp src/Manager/SceneManager.hpp src/Renderer/OpenGL/Buffer/VBO.hpp src/Renderer/OpenGL/Buffer/RBO.hpp
	$(CC) $(CFLAGS) -c $<

EBO.o : src/Renderer/OpenGL/Buffer/EBO.cpp src/Renderer/OpenGL/Buffer/EBO.hpp src/Renderer/OpenGL/OpenGLObject.hpp
	$(CC) $(CFLAGS) -c $<

RBO.o : src/Renderer/OpenGL/Buffer/RBO.cpp src/Renderer/OpenGL/Buffer/RBO.hpp src/Renderer/OpenGL/OpenGLObject.hpp
	$(CC) $(CFLAGS) -c $<

SSBO.o :  src/Renderer/OpenGL/Buffer/SSBO.cpp src/Renderer/OpenGL/Buffer/SSBO.hpp src/Renderer/OpenGL/Shader/Shader.hpp
	$(CC) $(CFLAGS) -c $<

VAO.o : src/Renderer/OpenGL/Buffer/VAO.cpp src/Renderer/OpenGL/Buffer/VAO.hpp src/Renderer/OpenGL/OpenGLObject.hpp
	$(CC) $(CFLAGS) -c $<

VBO.o : src/Renderer/OpenGL/Buffer/VBO.cpp src/Renderer/OpenGL/Buffer/VBO.hpp src/Renderer/OpenGL/OpenGLObject.hpp
	$(CC) $(CFLAGS) -c $<

Shader.o : src/Renderer/OpenGL/Shader/Shader.cpp src/Renderer/OpenGL/Shader/Shader.hpp src/Renderer/OpenGL/OpenGLObject.hpp
	$(CC) $(CFLAGS) -c $<

TextureBlank.o : src/Renderer/OpenGL/Texture/TextureBlank.cpp src/Renderer/OpenGL/Texture/TextureBlank.hpp src/Renderer/OpenGL/Texture/Texture.hpp 
	$(CC) $(CFLAGS) -c $<

TextureFloatBlank.o : src/Renderer/OpenGL/Texture/TextureFloatBlank.cpp src/Renderer/OpenGL/Texture/TextureFloatBlank.hpp src/Renderer/OpenGL/Texture/Texture.hpp 
	$(CC) $(CFLAGS) -c $<

TextureFile.o : src/Renderer/OpenGL/Texture/TextureFile.cpp src/Renderer/OpenGL/Texture/TextureFile.hpp src/Renderer/OpenGL/Texture/Texture.hpp 
	$(CC) $(CFLAGS) -c $<

TextureCubemap.o : src/Renderer/OpenGL/Texture/TextureCubemap.cpp src/Renderer/OpenGL/Texture/TextureCubemap.hpp src/Renderer/OpenGL/Texture/Texture.hpp
	$(CC) $(CFLAGS) -c $<

TextureCubemapDepth.o : src/Renderer/OpenGL/Texture/TextureCubemapDepth.cpp src/Renderer/OpenGL/Texture/TextureCubemapDepth.hpp src/Renderer/OpenGL/Texture/Texture.hpp
	$(CC) $(CFLAGS) -c $<

#Scene
Scene.o : src/Scene/Scene.cpp src/Scene/Scene.hpp src/Scene/Camera/Camera.hpp src/Scene/Skybox/Skybox.hpp src/Scene/Lights/PointLight.hpp
	$(CC) $(CFLAGS) -c $<

SpaceScene.o : src/Scene/SpaceScene.cpp src/Scene/SpaceScene.hpp src/Settings.hpp src/Scene/Scene.hpp src/Scene/Orbits.hpp src/Scene/Entity/Celestial.hpp src/Scene/Entity/Asteroid.hpp
	$(CC) $(CFLAGS) -c $<

Orbits.o : src/Scene/Orbits.cpp src/Scene/Orbits.hpp src/Manager/ShaderManager.hpp src/Scene/Entity/Celestial.hpp
	$(CC) $(CFLAGS) -c $<

Skybox.o : src/Scene/Skybox/Skybox.cpp src/Scene/Skybox/Skybox.hpp src/Renderer/OpenGL/Buffer/VAO.hpp src/Renderer/OpenGL/Buffer/VBO.hpp src/Manager/ShaderManager.hpp src/Manager/TextureManager.hpp
	$(CC) $(CFLAGS) -c $<

Camera.o : src/Scene/Camera/Camera.cpp src/Scene/Camera/Camera.hpp src/Settings.hpp
	$(CC) $(CFLAGS) -c $<

Celestial.o : src/Scene/Entity/Celestial.cpp src/Scene/Entity/Celestial.hpp src/Scene/Entity/Entity.hpp
	$(CC) $(CFLAGS) -c $<

Asteroid.o : src/Scene/Entity/Asteroid.cpp src/Scene/Entity/Asteroid.hpp src/Scene/Entity/Entity.hpp src/Renderer/OpenGL/Buffer/SSBO.hpp
	$(CC) $(CFLAGS) -c $<

PointLight.o : src/Scene/Lights/PointLight.cpp src/Scene/Lights/PointLight.hpp src/Scene/Lights/Light.hpp src/Settings.hpp
	$(CC) $(CFLAGS) -c $<


move:
	mv *.o $(OBJDIR)

link:
	$(CC) -o $(EXEC) $(OBJDIR)/*.o $(LDFLAGS)

clean: 
	rm -rf $(OBJDIR)/*.o
	rm $(EXEC)
