#ifndef DUSK_AUDIO_AUDIO_SYSTEM_HPP
#define DUSK_AUDIO_AUDIO_SYSTEM_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>

namespace dusk
{

class Program;

class AudioSystem : public TrackedObject, public EventDispatcher
{

    friend class Program;

public:
    DUSK_CLASSNAME("Audio System")

    AudioSystem(const AudioSystem&) = delete;
    AudioSystem& operator=(const AudioSystem&) = delete;
    ~AudioSystem() = default;

private:
    AudioSystem();
};

} // namespace dusk

#endif // DUSK_AUDIO_AUDIO_SYSTEM_HPP
