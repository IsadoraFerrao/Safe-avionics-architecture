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
 * \file   EventCategory.h
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 * 
 * \endif
 */

#include <thread>

/*! \namespace hamster::utils::logger */
#ifndef EVENTCATEGORY_H
#define EVENTCATEGORY_H

namespace hamster {
namespace utils {
namespace logger {

    /*! 
     * \enum hamster::utils::logger::EventCategory
     * \brief Describes the category of the logged event.
     * \details 
     * \note The ostream operator \b \<\< is overloaded so the category 
     * string is print transparently.
     */
    enum class EventCategory : int {
        VERBOSE = 1,
        DETAIL = 2,
        DEBUG = 3,
        WARNING = 4,
        ERROR = 5,
        EVENT = 6
    };

    // Operator overload to print the event severity
    inline std::ostream& operator<<(std::ostream& stream, const EventCategory& category) {
        switch (category) {
            case EventCategory::DETAIL:
#ifdef LOG_THREAD
                stream << "THREAD ID = " << std::this_thread::get_id() << " DETAILS";
#else
                stream << "DETAILS";
#endif
                break;
            case EventCategory::VERBOSE:
#ifdef LOG_THREAD
                stream << "THREAD ID = " << std::this_thread::get_id() << " VERBOSE";
#else
                stream << "VERBOSE";
#endif
                break;
            case EventCategory::DEBUG:
#ifdef LOG_THREAD
                stream << "THREAD ID = " << std::this_thread::get_id() << " DEBUG";
#else
                stream << "DEBUG";
#endif
                break;
            case EventCategory::WARNING:
#ifdef LOG_THREAD
                stream << "THREAD ID = " << std::this_thread::get_id() << " WARNING";
#else
                stream << "WARNING";
#endif
                break;
            case EventCategory::ERROR:
#ifdef LOG_THREAD
                stream << "THREAD ID = " << std::this_thread::get_id() << " ERROR";
#else
                stream << "ERROR";
#endif
                break;
            case EventCategory::EVENT:
#ifdef LOG_THREAD
                stream << "THREAD ID = " << std::this_thread::get_id() << " EVENT";
#else
                stream << "EVENT";
#endif
                break;
        }
        return stream;
    }
    
} /* namespace logger */
} /* namespace utils */
} /* namespace hamster */

#endif /* EVENTCATEGORY_H */

