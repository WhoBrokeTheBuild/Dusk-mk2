#ifndef DUSK_LOGGING_CONSOLE_LOGGER_HPP
#define DUSK_LOGGING_CONSOLE_LOGGER_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Logging/Logger.hpp>
#include <Dusk/Types.hpp>

namespace dusk
{

class ConsoleLogger :
    public Logger
{
public:
    DUSK_CLASSNAME("Console Logger")

    ConsoleLogger() = default;
    ConsoleLogger(const ConsoleLogger&) = delete;
    ConsoleLogger& operator=(const ConsoleLogger&) = delete;
    virtual ~ConsoleLogger() = default;

    virtual void Log(const string& line, const LogForegroundColor& fgColor,
                     const LogBackgroundColor& bgColor) override;

}; // class ConsoleLogger

} // namespace dusk

#endif // DUSK_LOGGING_CONSOLE_LOGGER_HPP
