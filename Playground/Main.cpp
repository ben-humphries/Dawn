#include "Dawn/Application.h"
#include "Dawn/Event.h"
#include "Dawn/Log.h"
#include "Dawn/Window.h"

void test(const Dawn::MouseMovedEvent& e)
{
    DAWN_LOG("testing!", e.getX());
    e.getX();
}

class Playground : public Dawn::Application
{
    Dawn::Window win = Dawn::Window(200, 200, "this is a window");

   public:
    Playground()
    {
        Dawn::EventHandler::Listen(Dawn::EventType::MouseMoved, test);

        Dawn::EventHandler::Submit(Dawn::MouseMovedEvent(100, 100));
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