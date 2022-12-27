#include "RenderWindow.hpp"

// Initialisation variable static
RenderWindow* RenderWindow::m_instance{ nullptr };

RenderWindow::RenderWindow(const bool& fullscreen)
{
    // GLFW : Inititalisation
    // ----------------------
    glfwInit();

	// Version
	// -------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// sRGB
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

	// Anticrenelage - Ne fonctionne pas si on utilise un FBO, il faut creer des textureMS pour l'anticrenelage dans ce cas
	// --------------------------------------------------------------------------------------------------------------------
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Fenetre non redimensionnable
	// ----------------------------
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Synchro vertical
	// ----------------
	glfwSwapInterval(1);

	// Creation de la fenetre
	// ----------------------
	auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	m_Width = RESOLUTION_X;
	m_Height = RESOLUTION_Y;
	if (fullscreen == true) 
	{

		this->m_Window = glfwCreateWindow(m_Width, m_Height, "LoneExplorer", glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		this->m_Window = glfwCreateWindow(m_Width, m_Height, "LoneExplorer", NULL, NULL);
	}

	// Si pas de fenetre creee
	// -----------------------
	if (this->m_Window == NULL)
		throw std::runtime_error("Erreur GLFW : Impossible d'initialiser la fenetre");

	// Definition du contexte OpenGL et fonction de callback lors du resize de la fenetre
	// ----------------------------------------------------------------------------------
	glfwMakeContextCurrent(this->m_Window);

	// GLEW : Inititalisation
	// ----------------------
	GLenum err{ glewInit() };
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Erreur GLEW: %s\n", glewGetErrorString(err));
		//throw std::runtime_error(); // A modifier
	}

	// Options OpenGL
	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// N'afficher que les objets en face de la camera
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Antialiasing
	glEnable(GL_MULTISAMPLE);

	// sRGB
	glEnable(GL_FRAMEBUFFER_SRGB);

	// Transparence
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	// Lancer le HDRFBO
	m_HDRFBO = std::make_shared<HDRFBO>(m_Width, m_Height);

	// Recuperer le sceneManager
	m_sceneManagerPtr = SceneManager::getInstance();
}

RenderWindow::~RenderWindow()
{
	glfwTerminate();
}

// Recuperer le singleton de la classe
RenderWindow* RenderWindow::getInstance(const bool& fullscreen)
{
    if (RenderWindow::m_instance == nullptr)
    {
        RenderWindow::m_instance = new RenderWindow(fullscreen);
    }
    return RenderWindow::m_instance;
}

void RenderWindow::Clear()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderWindow::Draw(const float& deltatime, const float& lastframe)
{
	m_HDRFBO->Bind();
		glClearColor(0.01f, 0.01f, 0.01f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_sceneManagerPtr->DrawActiveScene(m_Width, m_Height, deltatime, lastframe);
	m_HDRFBO->Unbind();
	m_HDRFBO->Blur();
	glClearColor(1.00f, 1.00f, 1.00f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_HDRFBO->Draw();
}

bool RenderWindow::Run()
{
	return glfwWindowShouldClose(this->m_Window) == GLFW_FALSE;
}

void RenderWindow::Close()
{
	glfwSetWindowShouldClose(this->m_Window, GLFW_TRUE);
}

void RenderWindow::Update()
{
	glfwSwapBuffers(this->m_Window);
	glfwPollEvents();
}
