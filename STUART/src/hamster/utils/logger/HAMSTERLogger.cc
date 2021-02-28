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

/* 
 * \file   HAMSTERLogger.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "HAMSTERLogger.h"

namespace hamster{
namespace utils{
namespace logger{

HAMSTERLogger * HAMSTERLogger::singleton = new HAMSTERLogger();
Logger<FileLogger> * HAMSTERLogger::file_logger = NULL;
Logger<TerminalLogger> * HAMSTERLogger::terminal_logger = NULL;
bool HAMSTERLogger::logger_available = false;

HAMSTERLogger::HAMSTERLogger(){
#if(ENABLE_FILE_LOGGING == 1)
#ifdef HAMSTER_LOG_FILE_NAME
    HAMSTERLogger::logger_available = true;
    HAMSTERLogger::file_logger = new Logger<FileLogger>(HAMSTER_LOG_FILE_NAME);
#else
    HAMSTERLogger::file_logger = new Logger<FileLogger>("HAMSTERLog.log");
#endif
#endif

#if (ENABLE_TERMINAL_LOGGING == 1)
    HAMSTERLogger::logger_available = true;
    HAMSTERLogger::terminal_logger = new Logger<TerminalLogger>("");
#endif
    
}


HAMSTERLogger::~HAMSTERLogger() {
}

void HAMSTERLogger::stopLogger(){
    HAMSTERLogger::logger_available = false;
}

void HAMSTERLogger::startLogger(){
    if((HAMSTERLogger::file_logger != NULL) || (HAMSTERLogger::terminal_logger != NULL)){
        HAMSTERLogger::logger_available = true;
    }
}


}
}
}
