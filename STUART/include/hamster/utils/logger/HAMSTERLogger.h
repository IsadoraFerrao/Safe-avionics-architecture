/*
 * Copyright (C) 2017     Critical Embedded System Laboratory (LSEC)
 * 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * See the GNU Lesser General Public License for more details.
 * <http://www.gnu.org/licenses/>
 */

/*! 
 * \if DESIGN_MODEL
 * 
 *    \class hamster::utils::logger::HAMSTERLogger
 *    \brief Provides logging functionality for HAMSTER Architecture.
 *    \details 
 *       \note This class is present only in Design Model, not existing in the
 *             conceptual model.
 * 
 *       \n
 *       This class creates the logs defined by \ref Options and performs all
 *       the required logging actions as configured.
 * 
 *       The class run as a \e singleton design pattern, and implements loggin
 *       at a file and/or terminal according to user configurations.
 * 
 *       \note The logging process is activated by default.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * \endif
 */

#ifndef HAMSTERLOGGER_H
#define HAMSTERLOGGER_H

#include "Logger.h"
#include "HAMSTEROptions.h"

#ifdef ENABLE_LOGGING
#define logDetailedMessage(arg...) hamster::utils::logger::HAMSTERLogger::putInLog(hamster::utils::logger::EventCategory::DETAIL,arg)
#define logVerboseMessage(arg...) hamster::utils::logger::HAMSTERLogger::putInLog(hamster::utils::logger::EventCategory::VERBOSE,arg)
/*! \def logDebugMessage(arg...) \brief Output arguments as a DEBUG level message.*/
#define logDebugMessage(arg...) hamster::utils::logger::HAMSTERLogger::putInLog(hamster::utils::logger::EventCategory::DEBUG,arg)
/*! \def logWarningMessage \brief Output arguments as a WARNING level message.*/
#define logWarningMessage(arg...) hamster::utils::logger::HAMSTERLogger::putInLog(hamster::utils::logger::EventCategory::WARNING,arg)
/*! \def logErrorMessage \brief Output arguments as a ERROR level message.*/
#define logErrorMessage(arg...) hamster::utils::logger::HAMSTERLogger::putInLog(hamster::utils::logger::EventCategory::ERROR,arg)
/*! \def logEventMessage \brief Output arguments as a EVENT level message.*/
#define logEventMessage(arg...) hamster::utils::logger::HAMSTERLogger::putInLog(hamster::utils::logger::EventCategory::EVENT,arg)
#else
#define logDetailedMessage(arg...) for(;false;)
#define logVerboseMessage(arg...) for(;false;)
#define logDebugMessage(arg...) for(;false;)
#define logWarningMessage(arg...) for(;false;)
#define logErrorMessage(arg...) for(;false;)
#define logEventMessage(arg...) for(;false;)
#endif

namespace hamster {
namespace utils {
namespace logger {

class HAMSTERLogger {
public:
    /*! 
     * \fn hamster::utils::logger::HAMSTERLogger::startLogger()
     * \brief Starts the log process if configured.
     */
    static void startLogger();
    /*!
     * \fn hamster::utils::logger::HAMSTERLogger::stopLogger()
     * \brief Stop all logging activitites.
     */
    static void stopLogger();
    
    /*!
     * \fn hamster::utils::logger::HAMSTERLogger::putInLog(EventCategory category,Args...args)
     * \brief Log arguments in all available loggers.
     */    
    template<typename ... Args >
    static void putInLog(EventCategory category,Args...args){
        // Verify if there are any active logs
        if(logger_available == true){
            // If logging in file
            if(file_logger != NULL){
                // Check minimum log level
                if(static_cast<int>(category) >= FILE_LOGGING_LEVEL){
                    file_logger->print(category,args...);
                }
            }
            // If logging in terminal
            if(terminal_logger != NULL){
                // Check minimum log level
                if(static_cast<int>(category) >= TERMINAL_LOGGING_LEVEL){
                    terminal_logger->print(category,args...);
                }
            }
        }        
    }

private:
    HAMSTERLogger();
    virtual ~HAMSTERLogger();
    
    /*!
     * \var logger_available
     * \brief Boolean flag which controls the logging process execution. Set to 
     * true by default.
     */    
    static bool logger_available;
    /*! 
     * \var singleton
     * \brief Single instance of HAMSTERLogger. Not available to user. 
     */
    static HAMSTERLogger * singleton;
    /*!
     * \var file_logger
     * \brief Points to logger in file.
     */
    static Logger<FileLogger> * file_logger;
    /*!
     * \var terminal_logger
     * \brief Points to logger in terminal.
     */
    static Logger<TerminalLogger> * terminal_logger;  
};

    

} /* namespace logger */
} /* namespace utils */
} /* namespace logger */

#endif /* HAMSTERLOGGER_H */

