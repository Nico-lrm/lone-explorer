#include "Application.hpp"

Application* Application::m_instance{ nullptr };
bool Application::m_firstMouse{ true };
float Application::m_lastX{ 0.f };
float Application::m_lastY{ 0.f };
 
void Application::UpdateTime()
{
    m_currentFrame = static_cast<float>(glfwGetTime());
    m_deltaTime = m_currentFrame - m_lastFrame;
    m_countFrame++;
}

void Application::Inputs()
{
    if (glfwGetKey(m_RenderWindow->getWindow(), GLFW_KEY_ESCAPE))
        m_RenderWindow->Close();
    if (glfwGetKey(m_RenderWindow->getWindow(), GLFW_KEY_W))
        m_SceneManager->updateActiveCameraPositionActiveScene(FORWARD, m_deltaTime);
    if (glfwGetKey(m_RenderWindow->getWindow(), GLFW_KEY_S))
        m_SceneManager->updateActiveCameraPositionActiveScene(BACKWARD, m_deltaTime);
    if (glfwGetKey(m_RenderWindow->getWindow(), GLFW_KEY_A))
        m_SceneManager->updateActiveCameraPositionActiveScene(LEFT, m_deltaTime);
    if (glfwGetKey(m_RenderWindow->getWindow(), GLFW_KEY_D))
        m_SceneManager->updateActiveCameraPositionActiveScene(RIGHT, m_deltaTime);
    if (glfwGetKey(m_RenderWindow->getWindow(), GLFW_KEY_R))
        m_SceneManager->updateActiveCameraPositionActiveScene(UP, m_deltaTime);
    if (glfwGetKey(m_RenderWindow->getWindow(), GLFW_KEY_F))
        m_SceneManager->updateActiveCameraPositionActiveScene(BOTTOM, m_deltaTime);
}

// Recuperer le singleton de la classe
Application* Application::getInstance(const bool& fullscreen)
{
    if (Application::m_instance == nullptr)
    {
        Application::m_instance = new Application(fullscreen);
    }
    return Application::m_instance;
}

void Application::mouse_camera_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    auto sceneManager{ SceneManager::getInstance() };

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;

    sceneManager->updateActiveCameraOrientationActiveScene(xoffset, yoffset);
}

void Application::InitSpaceRenderer()
{
    // Chemin des textures skybox
    // --------------------------
    const std::vector<std::string> cubemapFiles
    {
        "../Ressources/skybox/milkyway/right.png",
        "../Ressources/skybox/milkyway/left.png",
        "../Ressources/skybox/milkyway/up.png",
        "../Ressources/skybox/milkyway/down.png",
        "../Ressources/skybox/milkyway/front.png",
        "../Ressources/skybox/milkyway/back.png",
    };

    // Mesurer le temps de chargement de l'ensemble du programme
    // ---------------------------------------------------------
    auto start_time{ std::chrono::high_resolution_clock::now() };

    // Chargement des shaders - Pas besoin de multithread pour l'instant (?)
    // ----------------------
    #ifdef NORMAL_MAP
        this->m_ShaderManager->createShader("planet", "planetnormal.vert.shader", "planetnormal.frag.shader");
        this->m_ShaderManager->createShader("asteroid", "asteroidnormal.vert.shader", "planetnormal.frag.shader");
    #else
        this->m_ShaderManager->createShader("planet", "planet.vert.shader", "planet.frag.shader");
        this->m_ShaderManager->createShader("asteroid", "asteroid.vert.shader", "planet.frag.shader");
    #endif
    this->m_ShaderManager->createShader("star", "star.vert.shader", "star.frag.shader");
    this->m_ShaderManager->createShader("skybox", "skybox.vert.shader", "skybox.frag.shader");

    // Chargements des modeles - Multithread a faire 
    // -----------------------
    this->m_ModelManager->createModel("sun", "sun/sun.gltf", true);
    this->m_ModelManager->createModel("mercury", "mercury/mercury.gltf", true);
    this->m_ModelManager->createModel("venus", "venus/venus.gltf", true);
    this->m_ModelManager->createModel("earth", "earth/earth.gltf", false);
    this->m_ModelManager->createModel("mars", "mars/mars.gltf", true);
    this->m_ModelManager->createModel("jupiter", "jupiter/jupiter.gltf", true);
    this->m_ModelManager->createModel("saturn", "saturn/saturn.gltf", true);
    this->m_ModelManager->createModel("uranus", "uranus/uranus.gltf", true);
    this->m_ModelManager->createModel("neptune", "neptune/neptune.gltf", true);
    this->m_ModelManager->createModel("moon", "moon/moon.gltf", true);
    this->m_ModelManager->createModel("asteroid", "asteroid/asteroid.gltf", true);

    // Creation de la scene - Pas multithread (?)
    // --------------------
    this->m_SceneManager->createScene("mainScene");
    this->m_SceneManager->addCameraActiveScene("mainCamera", glm::vec3(0.f, 0.0f, 4.0f));
    this->m_SceneManager->addSkyboxActiveScene("mainSkybox", cubemapFiles, true);

    // Ajout des elements de la scene - Pas multithread (?)
    // ------------------------------
    this->m_SceneManager->addPointLightActiveScene(glm::vec3(0.0f), glm::vec3(0.1f), glm::vec3(0.5f, 0.5f, 0.45f), glm::vec3(1.0f));
    this->m_SceneManager->addCelestialActiveScene("Sun", m_ModelManager->getElementByName("sun"), m_ShaderManager->getElementByName("star"), 1666666.7f, 545.5f, std::weak_ptr<Celestial>(), glm::vec3(0.f, 0.f, 0.0f), m_SceneManager->getPointLightActiveScene(0));
    this->m_SceneManager->addCelestialActiveScene("Mercury", m_ModelManager->getElementByName("mercury"), m_ShaderManager->getElementByName("planet"), 0.276f, 1.91f, m_SceneManager->getCelestialActiveScene("Sun"), glm::vec3(1.935f, 0.f, 0.0f));
    this->m_SceneManager->addCelestialActiveScene("Venus", m_ModelManager->getElementByName("venus"), m_ShaderManager->getElementByName("planet"), 4.17f, 4.745f, m_SceneManager->getCelestialActiveScene("Sun"), glm::vec3(3.615f, 0.f, 0.0f));
    this->m_SceneManager->addCelestialActiveScene("Earth", m_ModelManager->getElementByName("earth"), m_ShaderManager->getElementByName("planet"), 5.f, 5.f, m_SceneManager->getCelestialActiveScene("Sun"), glm::vec3(5.f, 0.f, 0.0f));
    this->m_SceneManager->addCelestialActiveScene("Moon", m_ModelManager->getElementByName("moon"), m_ShaderManager->getElementByName("planet"), 0.0615f, 0.009f, m_SceneManager->getCelestialActiveScene("Earth"), glm::vec3(0.05f, 0.f, 0.0f));
    this->m_SceneManager->addCelestialActiveScene("Mars", m_ModelManager->getElementByName("mars"), m_ShaderManager->getElementByName("planet"), 0.535f, 2.66f, m_SceneManager->getCelestialActiveScene("Sun"), glm::vec3(7.615f, 0.f, 0.0f));
    this->m_SceneManager->addCelestialActiveScene("Jupiter", m_ModelManager->getElementByName("jupiter"), m_ShaderManager->getElementByName("planet"), 1589.f, 56.05f, m_SceneManager->getCelestialActiveScene("Sun"), glm::vec3(26.015f, 0.f, 0.0f));
    this->m_SceneManager->addCelestialActiveScene("Saturn", m_ModelManager->getElementByName("saturn"), m_ShaderManager->getElementByName("planet"), 476.f, 47.25f, m_SceneManager->getCelestialActiveScene("Sun"), glm::vec3(47.5f, 0.f, 0.0f));
    this->m_SceneManager->addCelestialActiveScene("Uranus", m_ModelManager->getElementByName("uranus"), m_ShaderManager->getElementByName("planet"), 72.5f, 20.035f, m_SceneManager->getCelestialActiveScene("Sun"), glm::vec3(96.15f, 0.f, 0.0f));
    this->m_SceneManager->addCelestialActiveScene("Neptune", m_ModelManager->getElementByName("neptune"), m_ShaderManager->getElementByName("planet"), 86.f, 19.415f, m_SceneManager->getCelestialActiveScene("Sun"), glm::vec3(150.35f, 0.f, 0.0f));
    this->m_SceneManager->addAsteroidActiveScene("KuiperBelt", 200.f, 40.f, 15000, m_SceneManager->getCelestialActiveScene("Sun"), m_ShaderManager->getElementByName("asteroid"), m_ModelManager->getElementByName("asteroid"), 25.0);


    // Mesurer le temps de chargement de l'ensemble du programme
    // ---------------------------------------------------------
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> execution_time = end_time - start_time;

    // Affichage du temps de chargement
    // --------------------------------
    std::cout << "Temps de chargement du programme : " << execution_time.count() / 1000 << "sec" << std::endl;

    // Suivi de l'execution du programme
    //---------------------------------
    std::cout << "Lancement du programme..." << std::endl;
}

void Application::Run()
{
    while (m_RenderWindow->Run())
    {
        UpdateTime();

        // Afficher le nombre de FPS
        if (m_deltaTime > 1.f / 30.f)
        {
            std::string FPS{ std::to_string((1.0 / m_deltaTime) * m_countFrame) };
            std::string title{ "LoneExplorer / " + FPS + " FPS" };
            glfwSetWindowTitle(m_RenderWindow->getWindow(), title.c_str());
            m_lastFrame = m_currentFrame;
            m_countFrame = 0;
        }

        // Traitement des entrees
        Inputs();

        // Dessiner la scene active
        m_RenderWindow->Draw(m_deltaTime, m_lastFrame);

        // Mettre a jour la fenetre (swap buffer / recuperer les touches pressees pour prochaine frame)
        m_RenderWindow->Update();
    }
}

Application::Application(const bool& fullscreen)
{
    this->m_RenderWindow = RenderWindow::getInstance(fullscreen);
    this->m_Width = RESOLUTION_X;
    this->m_Height = RESOLUTION_Y;

    Application::m_lastX = static_cast<float>(m_Width / 2);
    Application::m_lastY = static_cast<float>(m_Height / 2);

    this->m_ModelManager = ModelManager::getInstance();
    this->m_ShaderManager = ShaderManager::getInstance();
    this->m_SceneManager = SceneManager::getInstance();
    this->m_TextureManager = TextureManager::getInstance();

    glfwSetCursorPosCallback(m_RenderWindow->getWindow(), mouse_camera_callback);
    glfwSetInputMode(m_RenderWindow->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    srand(static_cast<unsigned int>(glfwGetTime()));
    InitSpaceRenderer();
}