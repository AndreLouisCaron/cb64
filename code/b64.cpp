// Copyright(c) 2011, Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file b64.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 * @brief High-level API for Base64 encoding and decoding.
 */

#include "b64.hpp"
#include "b64.h"

namespace {

    void accept_owire_data
        ( ::b64_owire * stream, const char * data, size_t size )
    {
        static_cast<std::string*>(stream->object)->append(data, size);
    }

    void accept_iwire_data
        ( ::b64_iwire * stream, const char * data, size_t size )
    {
        static_cast<std::string*>(stream->object)->append(data, size);
    }

}

namespace b64 {

    std::string encode ( const std::string& message )
    {
        std::string result;
          // prepare wire handler.
        ::b64_owire wire;
        ::b64_owire_init(&wire, 0);
        wire.object      = &result;
        wire.accept_data = &::accept_owire_data;
          // encode away!
        ::b64_owire_done(&wire, message.data(), message.size());
        return (result);
    }

    std::string decode ( const std::string& message )
    {
        std::string result;
          // prepare wire handler.
        ::b64_iwire wire;
        ::b64_iwire_init(&wire, 0);
        wire.object      = &result;
        wire.accept_data = &::accept_iwire_data;
          // decode away!
        ::b64_iwire_done(&wire, message.data(), message.size());
        return (result);
    }

}
