#ifndef DUSK_TIMING_TIME_INFO_HPP
#define DUSK_TIMING_TIME_INFO_HPP

#include <Dusk/Config.hpp>

namespace dusk
{

////////////////////////////////////////////////////////////
/// \brief Timing and Frame Speed Information
///
////////////////////////////////////////////////////////////
class FrameTimeInfo
{
public:
    FrameTimeInfo() = default;
    FrameTimeInfo(const FrameTimeInfo&) = default;
    FrameTimeInfo& operator=(const FrameTimeInfo&) = default;
    ~FrameTimeInfo() = default;

    ////////////////////////////////////////////////////////////
    /// \brief The Frames Per Second rate that is being targeted
    ///
    ////////////////////////////////////////////////////////////
    double TargetFPS = 0.0;

    ////////////////////////////////////////////////////////////
    /// \brief The Current Frames Per Second rate
    ///
    ////////////////////////////////////////////////////////////
    double CurrentFPS = 0.0;

    ////////////////////////////////////////////////////////////
    /// \brief The total seconds that have elapsed since the program started
    ///
    ////////////////////////////////////////////////////////////
    double TotalSeconds = 0.0;

    ////////////////////////////////////////////////////////////
    /// \brief The total milliseconds that have elapsed since the program started
    ///
    ////////////////////////////////////////////////////////////
    double TotalMilliseconds = 0.0;

    ////////////////////////////////////////////////////////////
    /// \brief The seconds that have elapsed since the last update
    ///
    ////////////////////////////////////////////////////////////
    double ElapsedSeconds = 0.0;

    ////////////////////////////////////////////////////////////
    /// \brief The milliseconds that have elapsed since the last update
    ///
    ////////////////////////////////////////////////////////////
    double ElapsedMilliseconds = 0.0;

    ////////////////////////////////////////////////////////////
    /// \brief The measurement of time relative to the desired frame rate.
    ///
    /// The value will be at 1.0 when the program is running normally, > 1.0
    /// when the program is running slowly, and < 1.0 when the program is
    /// running fast.
    ///
    ////////////////////////////////////////////////////////////
    double Delta = 0.0;

}; // class TimeInfo

} // namespace dusk

#endif // DUSK_TIMING_TIME_INFO_HPP
