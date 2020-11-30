#pragma once
#include "DawnPCH.h"

#define PROFILE_FUNC() ProfileTimer timer(__FUNCTION__ + std::string("()::") + std::to_string(__LINE__))
#define DAWN_PROFILE_FUNC() Dawn::ProfileTimer timer(__FUNCTION__ + std::string("()::") + std::to_string(__LINE__))

#define PROFILE_SCOPE(name) ProfileTimer timer(name)
#define DAWN_PROFILE_SCOPE(name) Dawn::ProfileTimer timer(name)

namespace Dawn
{
    struct ScopeTimePair {
        std::string name;
        double time;
    };

    class ProfileTimer
    {
       public:
        ProfileTimer(std::string name);
        ~ProfileTimer();

        //This is never cleared. Must be done by the reader.
        static std::vector<ScopeTimePair> s_scopeTimes;

       private:
        double m_startTime;
        std::string m_name;
    };
};