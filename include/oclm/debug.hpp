
//  Copyright (c) 2012 Julian Hornich
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_DEBUG_HPP
#define OCLM_DEBUG_HPP

#include <oclm/config.hpp>

#include <iostream>
#include <iomanip>

#define OCLM_DEBUG_LENGTH       80
#define OCLM_DEBUG_MSG_OFFSET   10
#define OCLM_DEBUG_MSG_LENGTH   ( OCLM_DEBUG_LENGTH - OCLM_DEBUG_MSG_OFFSET )

// produces nice debug messages with a specified lenght
#define OCLM_DEBUG( MSG )                                                     \
    {                                                                         \
        std::string message( MSG );                                           \
        if ( !message.empty() )                                               \
        {                                                                     \
            /* save old ios_flags */                                          \
            std::ios_base::fmtflags cerrFlags( std::cerr.flags() );           \
                                                                              \
            size_t l(message.substr(0,OCLM_DEBUG_MSG_LENGTH).rfind(' '));     \
            l  = (l == std::string::npos) ? OCLM_DEBUG_MSG_LENGTH : l;        \
            std::string subMessage(message.substr(0,l));                      \
            std::string spaces( OCLM_DEBUG_MSG_OFFSET, ' ' );                 \
                                                                              \
            std::cerr << std::left;                                           \
            std::cerr << std::setw( OCLM_DEBUG_MSG_OFFSET ) << "[DEBUG]";     \
            std::cerr << subMessage << "\n";                                  \
                                                                              \
            message.erase(0,l+1);                                             \
                                                                              \
            while( message.size() > OCLM_DEBUG_MSG_LENGTH )                   \
            {                                                                 \
                l = message.substr(0,OCLM_DEBUG_MSG_LENGTH).rfind(' ');       \
                l  = (l == std::string::npos) ? OCLM_DEBUG_MSG_LENGTH : l;    \
                std::string subMessage(message.substr(0,l));                  \
                std::cerr << spaces << subMessage << "\n";                    \
                message.erase(0,l+1);                                         \
            }                                                                 \
                                                                              \
            std::cerr << spaces << message << std::endl;                      \
            /* reset ios_flags */                                             \
            std::cerr.setf( cerrFlags );                                      \
        }                                                                     \
    }                                                                         \

#endif
