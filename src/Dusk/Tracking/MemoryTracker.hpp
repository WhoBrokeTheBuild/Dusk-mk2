#ifndef DUSK_TRACKING_MEMORY_TRACKER_H
#define DUSK_TRACKING_MEMORY_TRACKER_H

#include <Dusk/Config.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Types.hpp>

namespace dusk
{

class TrackedObject;

class MemoryTracker
{

    friend class TrackedObject;

public:
    static bool AddAllocation(
        TrackedObject* pObject, size_t size, unsigned int lineNumber, string filename);

    static bool RemoveAllocation(TrackedObject* pObject);

    static inline unsigned int GetAllocationCount() { return (unsigned int)s_Allocations.size(); }

    static void PrintAllocations();

private:
    struct AllocationRecord
    {
    public:
        unsigned int Number;
        unsigned int LineNumber;
        size_t Size;
        string Filename;

    }; // struct AllocationRecord

    static Map<TrackedObject*, AllocationRecord> s_Allocations;

    static unsigned int s_AllocationIndex;

}; // class MemoryTracker

} // namespace dusk

#endif // DUSK_TRACKING_MEMORY_TRACKER_H
