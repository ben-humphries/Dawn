#pragma once

#include <iostream>

//#include "Dawn/Log_Def.h"

#define LOG(args...) Log::print("DAWN ENGINE: ", args)
#define DAWN_LOG(args...) Dawn::Log::print("DAWN APP: ", args)

namespace Dawn
{
    class Log
    {
       public:
        static void print()
        {
            std::cout << std::endl;
        }

        template <typename T, typename... Types>
        static void print(T var, Types... var2)
        {
            std::cout << var;
            print(var2...);
        }
    };

}  // namespace Dawn