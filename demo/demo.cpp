// Copyright(c) 2011, Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file demo.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 * @brief Example usage of high-level API for Base64 encoding and decoding.
 */

#include "b64.hpp"
#include <iostream>

int main ( int, char ** )
{
      // Examples from Wikipedia article on Base64.
    std::cout << "'" << b64::encode("pleasure.") << "'" << std::endl;
    std::cout << "'" << b64::encode( "leasure.") << "'" << std::endl;
    std::cout << "'" << b64::encode(  "easure.") << "'" << std::endl;
    std::cout << "'" << b64::encode(   "asure.") << "'" << std::endl;
    std::cout << "'" << b64::encode(    "sure.") << "'" << std::endl;
    std::cout << "'" << b64::decode("cGxlYXN1cmUu") << "'" << std::endl;
    std::cout << "'" << b64::decode("bGVhc3VyZS4=") << "'" << std::endl;
    std::cout << "'" << b64::decode("ZWFzdXJlLg==") << "'" << std::endl;
    std::cout << "'" << b64::decode(    "YXN1cmUu") << "'" << std::endl;
    std::cout << "'" << b64::decode(    "c3VyZS4=") << "'" << std::endl;
    
      // Examples from Wikipedia article on HTTP basic authentication.
    std::cout
        << "'" << b64::encode("Aladdin:open sesame") << "'"
        << std::endl;
    std::cout
        << "'" << b64::decode("QWxhZGRpbjpvcGVuIHNlc2FtZQ==") << "'"
        << std::endl;
}
