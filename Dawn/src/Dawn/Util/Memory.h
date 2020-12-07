#pragma once
#include "DawnPCH.h"

namespace Dawn
{
    class Memory
    {
       public:
        static void Allocation(size_t size)
        {
            s_currentlyAllocated += size;
            s_allocations++;
        }

        static void Deallocation(size_t size)
        {
            s_currentlyAllocated -= size;
        }

        static size_t GetCurrentlyAllocated()
        {
            return s_currentlyAllocated;
        }

        static size_t GetAllocations()
        {
            return s_allocations;
        }

       private:
        inline static size_t s_currentlyAllocated = 0;
        inline static size_t s_allocations = 0;
    };
}  // namespace Dawn

#if FALSE  //Disable overloading for now

#ifndef DAWN_MEMORY_MANAGEMENT_OVERLOADED
#define DAWN_MEMORY_MANAGEMENT_OVERLOADED

//TODO: Implement all other variations of new and delete operators

#ifndef __INTELLISENSE__  //Solely to prevent a buggy error from appearing in VSCode. This code is still present.
inline void* operator new(size_t size)
{
    Dawn::Memory::Allocation(size);
    void* p = malloc(size);
    return p;
}

inline void* operator new[](size_t size)
{
    Dawn::Memory::Allocation(size);
    void* p = malloc(size);
    return p;
}

inline void operator delete(void* p, size_t size)
{
    Dawn::Memory::Deallocation(size);
    free(p);
}

inline void operator delete[](void* p, size_t size)
{
    Dawn::Memory::Deallocation(size);
    free(p);
}

#endif

#endif

#endif