#include "Dawn/Application.h"
#include "Dawn/Log.h"
#include "Dawn/Window.h"

class Playground : public Dawn::Application
{
    Dawn::Window win = Dawn::Window(200, 200, "this is a window");

   public:
    Playground()
    {
    }

    void OnUpdate() override
    {
        win.clear();
        win.display();
    }

    void OnClose() override
    {
    }
};

int main()
{
    Playground playground = Playground();
    playground.Start();

    return 0;
}