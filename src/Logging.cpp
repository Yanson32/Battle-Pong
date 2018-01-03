#include "Logging.h"
#include <boost/log/utility/setup/console.hpp>

void init()
{
    #ifdef LOG_DESTINATION
        std::string logPath = LOG_DESTINATION;
    #else
        std::string logPath = "log_%N.log";
    #endif

    auto consoleSink = logging::add_console_log(std::cout);
    auto fileSink = logging::add_file_log(keywords::file_name = logPath,
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%]: [%LineID%]: [%ProcessID%]: [%ThreadID%]: %Message%"
        );

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
    logging::add_common_attributes();
    //boost::shared_ptr< logging::core > core = logging::core::get();

}
