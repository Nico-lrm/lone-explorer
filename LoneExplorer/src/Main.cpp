#include "Application.hpp"

int main(int argc, char** argv)
{
    auto app{ Application::getInstance(FULLSCREEN) };
    app->Run();
    return EXIT_SUCCESS;
} 