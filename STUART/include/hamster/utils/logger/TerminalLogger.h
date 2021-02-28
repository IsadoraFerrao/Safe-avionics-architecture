/*! 
 * \if DESIGN_MODEL
 * 
 *    \class hamster::utils::logger::TerminalLogger TerminalLogger.h
 *    \brief A file logging policy.
 *    \details 
 *       \note This class is taken from Dr.Dobb's 
 *        <a href="http://www.drdobbs.com/cpp/logging-in-c/201804215">"A Lightweight Logger for C++"</a> 
 *        online arcticle.
 *    \n
 *    This class implements the necessary methods so that the log is built in a
 *    file.
 * 
 * \endif
 */
#ifndef TERMINALLOGGER_H
#define TERMINALLOGGER_H

#include <iostream>
#include <memory>
#include "LoggerPolicy.h"

namespace hamster{
namespace utils{
namespace logger{
    
class TerminalLogger : public LoggerPolicy {
public:
    TerminalLogger();
    virtual ~TerminalLogger();
    
    void openOStream(const std::string& name);
    void closeOStream();
    void write(const std::string& msg);
};

} /* namespace logger */
} /* namespace utils */
} /* namespace hamster */

#endif /* TERMINALLOGGER_H */

