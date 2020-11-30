#include "Profile.h"

#include "glfw/glfw3.h"

#include "Core/Log.h"

namespace Dawn
{
    std::vector<ScopeTimePair> ProfileTimer::s_scopeTimes;

    ProfileTimer::ProfileTimer(std::string name)
        : m_name(name)
    {
        m_startTime = glfwGetTime();
    }

    ProfileTimer::~ProfileTimer()
    {
        auto time = glfwGetTime() - m_startTime;
        ProfileTimer::s_scopeTimes.push_back({m_name, time});
    }
}