// Copyright(c) 2011, Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file b64-encode.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 * @brief Example usage of high-level API for Base64 encoding and decoding.
 */

#include "b64.h"
#include <fstream>
#include <iostream>

namespace {

    void accept_owire_data
        ( ::b64_owire * wire, const char * data, size_t size )
    {
        std::ostream& stream = *static_cast<std::ostream*>(wire->object);
        stream.write(data, size);
    }

    void run ( std::istream& stream, ::b64_owire& wire )
    {
        char data[1024];
        std::size_t size = 0;
        std::size_t pass = 0;
        std::size_t used = 0;
        do {
            stream.read(data+size, sizeof(data)-size);
            pass = stream.gcount();
            size += pass;
            used = ::b64_owire_feed(&wire, data, size);
            std::copy(data+used, data+size, data);
            size -= used;
        }
        while (pass > 0);
        ::b64_owire_done(&wire, data, size);
    }

}

int main ( int argc, char ** argv )
try
{
    ::b64_owire wire;
    ::b64_owire_init(&wire, 0);
    wire.object      = &std::cout;
    wire.accept_data = &::accept_owire_data;
    if (argc == 1) {
        ::run(std::cin, wire);
    }
    else {
        std::ifstream file(argv[1]);
        if (!file.is_open())
        {
            std::cerr
                << "Could not open input file."
                << std::endl;
            return (EXIT_FAILURE);
        }
        ::run(file, wire);
    }
    ::b64_owire_done(&wire, 0, 0);
}
catch ( const std::exception& error )
{
    std::cerr
        << error.what()
        << std::endl;
    return (EXIT_FAILURE);
}
