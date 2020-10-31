#include "Dawn/Application.h"
#include "Dawn/Log.h"

class Playground : public Dawn::Application
{
    void Init() override
    {
        DAWN_LOG("Starting Dawn Application...");
    }

    void Update() override
    {
        DAWN_LOG("Logging from Playground update function");
    }
};

int main()
{
    Playground playground;
    playground.Start();

    return 0;
}