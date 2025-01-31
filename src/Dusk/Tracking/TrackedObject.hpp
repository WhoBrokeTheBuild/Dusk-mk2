#ifndef DUSK_TRACKING_TRACKED_OBJECT_HPP
#define DUSK_TRACKING_TRACKED_OBJECT_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Platform.hpp>
#include <Dusk/Types.hpp>

namespace dusk
{

#define DUSK_CLASSNAME(NAME) virtual inline string GetClassName() const override { return NAME; }

class TrackedObject
{
public:
    virtual string GetClassName() const = 0;

    // Normal new operator
    void* operator new(size_t size);
    void* operator new[](size_t size);

    // Operator for placement new, takes in the filename and line number
    void* operator new(size_t size, int lineNumber, const char* filename);
    void* operator new[](size_t size, int lineNumber, const char* filename);

    // Normal delete operator
    void operator delete(void* ptr);
    void operator delete[](void* ptr);

    // Required because of the placement new operator, should not be used
    inline void operator delete(void* ptr, int lineNumber, const char* filename)
    {
        ::operator delete(ptr);
    }
    inline void operator delete[](void* ptr, int lineNumber, const char* filename)
    {
        ::operator delete[](ptr);
    }

}; // class MemoryTrackedObject

#ifdef DUSK_DEBUG_BUILD

#define New new (__LINE__, __FILE__)

#else

#define New new

#endif

} // namespace Tracking

#endif // DUSK_TRACKING_TRACKED_OBJECT_HPP
