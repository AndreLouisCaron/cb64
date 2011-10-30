#ifndef _b64_h__
#define _b64_h__

// Copyright(c) 2011, Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file b64.h
 * @author Andre Caron (andre.l.caron@gmail.com)
 * @brief Low-level incremental encoder and decoder for Base64.
 */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct b64_iwire_t
{
    void * object;
    void(*accept_data)(struct b64_iwire_t*,const char*,size_t);

    char codebook[256];

} b64_iwire;

void b64_iwire_init ( b64_iwire * stream, const char * codebook );
size_t b64_iwire_feed ( b64_iwire * stream, const char * data, size_t size );
size_t b64_iwire_done ( b64_iwire * stream, const char * data, size_t size );

typedef struct b64_owire_t
{
    void * object;
    void(*accept_data)(struct b64_owire_t*,const char*,size_t);

    char codebook[64];

} b64_owire;

void b64_owire_init ( b64_owire * stream, const char * codebook );
size_t b64_owire_feed ( b64_owire * stream, const char * data, size_t size );
size_t b64_owire_done ( b64_owire * stream, const char * data, size_t size );

#ifdef __cplusplus
}
#endif

#endif /* _b64_h__ */
