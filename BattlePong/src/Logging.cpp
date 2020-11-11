#include "Logging.h"
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

void init()
{
    #ifdef LOG_DESTINATION
        std::string logPath = LOG_DESTINATION;
    #else
        std::string logPath = "log_%N.log";
    #endif

    auto consoleSink    = logging::add_console_log(std::cout);
    auto fileSink       = logging::add_file_log(keywords::file_name = logPath,
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%]: [%LineID%]: [%ProcessID%]: [%ThreadID%]: %Message%"
        );

    logging::core::get()->set_filter
    (
        boost::log::trivial::severity >= logging::trivial::info
    );
    logging::add_common_attributes();
    //boost::shared_ptr< logging::core > core = logging::core::get();

}
