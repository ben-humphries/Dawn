#pragma once

#include <iostream>

//#include "Dawn/Log_Def.h"

#define DAWN_LOG(...) Dawn::Log::print(__VA_ARGS__)

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