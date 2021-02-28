

#ifndef HAMSTEROPTIONS_H
#define HAMSTEROPTIONS_H

/*! @page Options HAMSTER Options
 *  Since its conception, the HAMSTER Architecture was designed taking into 
 *  account its modularity and the possibility of enabling/disabling features.
 *  the file \ref HAMSTEROptions.h lists the available options for building the
 *  architecture. In this file, options are made available through \#define
 *  directives.
 *  \if DESIGN_MODEL
 *  Options listed in this file are tested by \#ifdef directives around the code
 *  so proper modularization and portability is reached.
 *  \endif
 *  An alphabetically sorted list of available options follows:
 *  \secreflist
 *  \refitem config_ENABLE_LOGGING config_ENABLE_LOGGING
 */

namespace hamster{
    
/*!
 * \section ENABLE_FILE_LOGGING Enable HAMSTER File Logging
 * If set to 1, this option enables HAMSTER Architecture to log events in a file
 * defined by macro HAMSTER_LOG_FILE_NAME. If set to 0, file logging is disabled.
 */

#define ENABLE_FILE_LOGGING         1

#define ENABLE_TERMINAL_LOGGING     1

#define FILE_LOGGING_LEVEL          1

#define TERMINAL_LOGGING_LEVEL      1

#define HAMSTER_LOG_FILE_NAME       "UAV.log"
    
//#define LOG_THREAD


/*! \endsecreflist */

#if (ENABLE_FILE_LOGGING == 1) || (ENABLE_TERMINAL_LOGGING == 1)
#define ENABLE_LOGGING
#endif
    
#define KOWN_FORMATION
//#define UNKOWN_FORMATION
    
#define CENTRALIZED
//#define DECENTRALIZED
    

#define KEPP_ALIVE_TIMEOUT_MS 2000
    
//------------------------------------------------------------------------------
// Communication options
//------------------------------------------------------------------------------
#define HAMSTER_DEFAULT_PORT 38833
    
    
//------------------------------------------------------------------------------
// Cryptography options
//------------------------------------------------------------------------------
    
#define CRYPTOGRAPHY_AVAILABLE 0
    
#define DEFAULT_BUFFER_SIZE 1000
}
#endif /* HAMSTEROPTIONS_H */

