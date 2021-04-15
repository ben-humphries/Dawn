#pragma once
#include "DawnPCH.h"

#ifndef _MSC_VER

#define LOG(args...) Log::print("DAWN ENGINE: ", args)
#define DAWN_LOG(args...) Dawn::Log::print("DAWN APP: ", args)

#else

#define LOG(...) Log::print("DAWN ENGINE: ", __VA_ARGS__)
#define DAWN_LOG(...) Dawn::Log::print("DAWN APP: ", __VA_ARGS__)

#endif

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