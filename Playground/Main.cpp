#include "Dawn/Application.h"
#include "Dawn/Log.h"

int main()
{
    DAWN_LOG("Starting Dawn Application...");

    Dawn::Application::Init();

    Dawn::Application::Start();

    Dawn::Application::Close();

    return 0;
}