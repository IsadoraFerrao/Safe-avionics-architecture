#include "TerminalLogger.h"
#include "Logger.h"

namespace hamster {
namespace utils {
namespace logger{

TerminalLogger::TerminalLogger(){
}

TerminalLogger::~TerminalLogger() {
}

void TerminalLogger::openOStream(const std::string& name) {
    
}

void TerminalLogger::closeOStream() {

}

void TerminalLogger::write(const std::string& msg) {
    std::cout << msg << std::endl;
}


} /* namespace logger */
} /* namespace utils */
} /* namespace hamster */

