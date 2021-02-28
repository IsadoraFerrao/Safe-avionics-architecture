/*! 
 * \if DESIGN_MODEL
 * 
 *    \class hamster::utils::logger::Logger Logger.h
 *    \brief A logger that implements a logging policy.
 *    \details 
 *       \note This class is taken from Dr.Dobb's 
 *        <a href="http://www.drdobbs.com/cpp/logging-in-c/201804215">"A Lightweight Logger for C++"</a> 
 *        online arcticle.
 *    \n
 *    This template class implements the core logging functionality by building
 *    the log strings and outputing them in the propoer log stream determined by
 *    the logging policy. The log resource access is controlled by a mutex.
 * 
 *  \tparam LoggerPolicy How the log messages will be made available (file, output 
 *  terminal, etc).
 * \endif
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "LoggerPolicy.h"
#include "TerminalLogger.h"
#include "FileLogger.h"
#include "EventCategory.h"

#include <iostream>
#include <sstream>
#include <mutex>
#include <type_traits>

namespace hamster {
namespace utils {
namespace logger{

template< typename Policy >
class Logger {
public:

    Logger(const std::string& name) {
        static_assert(std::is_base_of<hamster::utils::logger::LoggerPolicy, Policy>::value, "Logger Policy not derived from LoggerPolicy class.");
        this->log_line_number = 1;
        this->policy = new Policy();
        if (!this->policy) {
            throw std::runtime_error("LOGGER: Unable to create the logger instance");
        }
        this->policy->openOStream(name);
    }

    virtual ~Logger() {
        if (this->policy) {
            this->policy->closeOStream();
            delete this->policy;
        }
    }

    /*!
     * \fn hamster::utils::logger::Logger::print(Args...args)
     * \brief Output the information in log.
     * \details This method handles the log resource acquiring, log string 
     * construction and output and log resource release.
     */
    template<typename ... Args >
    void print(EventCategory category,Args...args) {
        this->write_mutex.lock();
        this->log_stream << "[" << category << "] ";
        this->printInLog(args...);
        this->write_mutex.unlock();
    }

private:
    // Private 
    unsigned int log_line_number = 0; /*!< \brief Current line number to print. */
    std::stringstream log_stream;     /*!< \brief Output stream for the log.    */
    hamster::utils::logger::LoggerPolicy * policy; /*!< \brief Applied policy.               */
    std::mutex write_mutex; /*!< \brief Mutex for log access.         */

    /*!
     * \fn hamster::utils::logger::Logger::getTime()
     * \brief Return a string with current time to be print in log.
     */
    std::string getTime() {
        std::string time_str;
        time_t raw_time;
        time(& raw_time);
        time_str = ctime(&raw_time);
        //without the newline character
        return time_str.substr(0, time_str.size() - 1);
    }

    /*!
     * \fn std::string hamster::utils::logger::Logger::getLoglineHeader()
     * \brief Construct the header string for each log line.
     */
    std::string getLogLineHeader() {
        std::stringstream header;

        header.str("");
        header.fill('0');
        header.width(7);
        header << this->log_line_number++;// << " < " << this->getTime() << " - ";
        header << " ";
//        header.fill('0');
//        header.width(7);
//        header << clock() << " > ~ ";
        return header.str();
    }

    /*!
     * \fn hamster::utils::logger::Logger::printInLog(First parm1, Rest...params)
     * \brief Prepare string to be print in log.
     * \details This method is called to build the stream to be print at the log.
     * It invokes itself recursively, until all data is stored in the stream.
     * Then, method \c printInLog() is invoked to output the built stream to
     * the log.
     */
    template< typename First, typename...Rest >
    void printInLog(First parm1, Rest...params) {
        // Put first param in stream
        this->log_stream << parm1;
        // Call this method recursively to other parameters
        this->printInLog(params...);
    }

    /*!
     * \fn hamster::utils::logger::Logger::printInLog()
     * \brief Print log line information in log file.
     * \details This method will be called at the end of print recursion. The
     * constructed stream (stored in \c log_stream) is outputed together with a 
     * line header and then emptied.
     */
    void printInLog(void) {
        // Write both line header and the constructed string in log
        this->policy->write(this->getLogLineHeader() + this->log_stream.str());
        // Empty stream
        this->log_stream.str("");
    }

};

} /* namespace logger */
} /* namespace utils */
} /* namespace hamster */

#endif /* LOGGER_H */

