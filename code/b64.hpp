#ifndef _b64_hpp__
#define _b64_hpp__

// Copyright(c) 2011, Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file b64.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 * @brief High-level API for Base64 encoding and decoding.
 */

#include <string>

namespace b64 {

    std::string encode ( const std::string& message );
    std::string decode ( const std::string& message );

}

#endif /* _b64_hpp__ */
