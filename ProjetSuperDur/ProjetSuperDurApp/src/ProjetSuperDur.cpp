// ProjetSuperDur.cpp : définit le point d'entrée de l'application.
//

#include "ProjetSuperDur.h"
#include "BoostPython.h"
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/make_shared.hpp>

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

void init_logging()
{
    logging::add_common_attributes();

    // Sink pour moduleA
    auto sinkA = boost::make_shared<sinks::synchronous_sink<sinks::text_file_backend>>(
        keywords::file_name = "moduleA.log", keywords::target_file_name = "moduleA%Y%m%d_%H%M%S_%5N.log");
    sinkA->set_filter(expr::attr<std::string>("Channel") == "A");
    sinkA->set_formatter(expr::stream << "[" << expr::attr<boost::posix_time::ptime>("TimeStamp") << "] "
                                      << expr::smessage);

    sinkA->locked_backend()->set_time_based_rotation(
        sinks::file::rotation_at_time_interval(boost::posix_time::minutes(1)));

    sinkA->locked_backend()->auto_flush(true);

    logging::core::get()->add_sink(sinkA);

    // Sink pour moduleB
    auto sinkB = boost::make_shared<sinks::synchronous_sink<sinks::text_file_backend>>(
        keywords::file_name = "moduleB.log", keywords::target_file_name = "moduleB%Y%m%d_%H%M%S_%5N.log");
    sinkB->set_filter(expr::attr<std::string>("Channel") == "B");
    sinkB->set_formatter(expr::stream << "[" << expr::attr<boost::posix_time::ptime>("TimeStamp") << "] "
                                      << expr::smessage);
    logging::core::get()->add_sink(sinkB);
}

using namespace std;

enum class Com : std::uint8_t
{
    A,
    B
};

inline const char *to_channel(Com Communication)
{
    switch (Communication)
    {
    case Com::A:
        return "A";
    case Com::B:
        return "B";
    default:
        return "Unknown";
    }
}

int main()
{
    try
    {
        cout << "Hello CMake." << std::endl;

        test();
        // create_log();

        python_run();
        return 0;
    }
    catch (...)
    {
        return 1;
    }
    // init_logging();

    // Création de loggers avec un channel
    /*src::channel_logger<> loggerA(keywords::channel = to_channel(Com::A));
    src::channel_logger<> loggerB(keywords::channel = to_channel(Com::B));*/

    // while(true)
    //{
    //     BOOST_LOG(loggerA) << "Log dans A";
    //     BOOST_LOG(loggerB) << "Log dans B";
    //     Sleep(1000); // Pause de 1 seconde
    // }
}
