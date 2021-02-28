/*! 
 * \if DESIGN_MODEL
 * 
 *    \class hamster::utils::logger::FileLogger FileLogger.h
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
#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <fstream>
#include <memory>
#include "LoggerPolicy.h"


namespace hamster{
namespace utils{
namespace logger{
    
class FileLogger : public LoggerPolicy {
public:
    
    FileLogger();
    virtual ~FileLogger();
    
    void openOStream(const std::string& name);
    void closeOStream();
    void write(const std::string& msg);
    
private:
    
    std::unique_ptr< std::ofstream > file_stream; /*!< Pointer to file stream 
                                                   * managed by \c unique_ptr class.
                                                   */

};

} /* namespace logger */
} /* namespace utils */
} /* namespace hamster */

#endif /* FILELOGGER_H */

