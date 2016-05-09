#ifndef DUSK_LOGGING_FILE_LOGGER_HPP
#define DUSK_LOGGING_FILE_LOGGER_HPP

#include <Dusk/Logging/Logger.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Collections/ArrayList.hpp>
#include <Dusk/Types.hpp>

#include <fstream>
using std::ofstream;

namespace dusk
{

class FileLogger :
    public Logger
{
public:
    DUSK_CLASSNAME("File Logger")

    FileLogger() = delete;
    FileLogger(const string& filename);
    FileLogger(const FileLogger&) = delete;
    FileLogger& operator=(const FileLogger&) = delete;
    virtual ~FileLogger();

    virtual void Log(const string& line, const LogForegroundColor& fgColor,
                     const LogBackgroundColor& bgColor) override;

private:

    static Map<string, ofstream*> s_Streams;

    static Map<string, int> s_StreamOwners;

    string m_Filename;

    ofstream* m_Stream;

}; // class FileLogger

} // namespace dusk

#endif // DUSK_LOGGING_FILE_LOGGER_HPP
