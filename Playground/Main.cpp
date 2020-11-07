#include "Dawn/Application.h"
#include "Dawn/Event.h"
#include "Dawn/Log.h"
#include "Dawn/Window.h"

void test(const Dawn::Event& e)
{
    DAWN_LOG(e.toString());
}

void test_keycodes(const Dawn::Event& e)
{
    auto e_k = (const Dawn::KeyPressedEvent&)e;
    if (e_k.getKeyCode() == Dawn::KeyCode::A) {
        DAWN_LOG("Key A was pressed");
    }
}

class Playground : public Dawn::Application
{
   public:
    Playground()
    {
        Dawn::EventHandler::Listen(Dawn::EventType::WindowClosed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::WindowResized, test);
        Dawn::EventHandler::Listen(Dawn::EventType::WindowMoved, test);
        Dawn::EventHandler::Listen(Dawn::EventType::KeyPressed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::KeyReleased, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseMoved, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MousePressed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseReleased, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseScrolled, test);

        Dawn::EventHandler::Listen(Dawn::EventType::KeyPressed, test_keycodes);
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