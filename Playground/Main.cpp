#include "Dawn/Application.h"
#include "Dawn/Event.h"
#include "Dawn/Log.h"
#include "Dawn/Window.h"

void test(const Dawn::Event& e)
{
    DAWN_LOG(e.toString());
}

class Playground : public Dawn::Application
{
   public:
    Playground()
    {
        // TODO: change reference to Event to pointer, so that dynamic casting
        // works!
        Dawn::EventHandler::Listen(Dawn::EventType::WindowClosed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseMoved, [](const Dawn::Event& e) { DAWN_LOG("testing!"); });

        //Dawn::EventHandler::Submit(Dawn::WindowClosedEvent());
    }

    void onUpdate() override
    {
    }

    void onClose() override
    {
    }
};

int main()
{
    Playground playground = Playground();
    playground.start();

    return 0;
}