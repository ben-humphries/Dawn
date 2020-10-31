#include "Dawn/Application.h"
#include "Dawn/Log.h"
#include "Dawn/Window.h"

class Playground : public Dawn::Application
{
    Dawn::Window window = Dawn::Window(800, 600, "Playground");
    Dawn::Window window2 = Dawn::Window(800, 600, "Playground2");

    void Init() override
    {
    }

    void Update() override
    {
        window.clear();
        window.display();

        window2.clear();
        window2.display();
    }
};

int main()
{
    Playground playground;
    playground.Start();

    return 0;
}