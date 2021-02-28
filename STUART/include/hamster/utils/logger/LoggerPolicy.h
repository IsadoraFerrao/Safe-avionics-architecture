/*! 
 * \if DESIGN_MODEL
 * 
 *   \class hamster::utils::logger::LoggerPolicy LoggerPolicy.h
 *   \brief Provides an interface for different policies of logging.
 *   \details 
 *       \note This class is taken from Dr.Dobb's 
 *        <a href="http://www.drdobbs.com/cpp/logging-in-c/201804215">"A Lightweight Logger for C++"</a> 
 *        online arcticle.
 *   \n
 *   This class implements the interface for different log streams, such as 
 *   files or the output screen. This interface has three pure virtual methods 
 *   for dealing with the chosen stream: \c openOStream(), closeOStream() and
 *   \c write().
 * 
 * \endif
 */
#ifndef LOGGERPOLICY_H
#define LOGGERPOLICY_H

#include <string>

namespace hamster {
namespace utils{
namespace logger{

class LoggerPolicy {
public:
    LoggerPolicy(){};
    virtual ~LoggerPolicy(){};

    /*! 
     * \fn hamster::utils::LoggerPolicy::openOStream(const std::string& name)
     * \brief Opens the output stream.
     */
    virtual void openOStream(const std::string& name) = 0;
    /*! 
     * \fn hamster::utils::LoggerPolicy::closeOStream()
     * \brief Closes the output stream.
     */
    virtual void closeOStream() = 0;
    /*! 
     * \fn hamster::utils::LoggerPolicy::write(const std::string& msg)
     * \brief Writes \c msg in output stream
     */
    virtual void write(const std::string& msg) = 0;

};

} /* namespace logger */
} /* namespace utils */
} /* namespace hamster */

#endif /* LOGGERPOLICY_H */

