// Copyright(c) 2011, Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file b64.c
 * @author Andre Caron (andre.l.caron@gmail.com)
 * @brief Low-level incremental encoder and decoder for Base64.
 */

#include "b64.h"
#include <string.h>

#ifndef SIZE
#   define SIZE 1024
#endif

static const char STANDARD[] =
{
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/"
};

static size_t _b64_max ( size_t lhs, size_t rhs )
{
    return ((lhs < rhs)? lhs : rhs);
}

static void _b64_compute_codebook ( const char * forward, char * reverse )
{
    size_t i = 0;
    memset(reverse, 0, 256);
    for ( ; (i < 64); ++i ) {
        reverse[forward[i]] = i;
    }
}

static size_t _b64_encode
    ( b64_owire * stream, char * buffer, const char * data, size_t size, size_t * used )
{
    size_t pass = 0;
    char symbol[4];
    while ( size >= 3 )
    {
         /* inflate. */
        symbol[0] = ((data[0]&0xfc)>>2);
        symbol[1] = ((data[0]&0x03)<<4) | ((data[1]&0xf0)>>4);
        symbol[2] = ((data[1]&0x0f)<<2) | ((data[2]&0xc0)>>6);
        symbol[3] = ((data[2]&0x3f)<<0);
          /* translate symbols. */
        buffer[0] = stream->codebook[symbol[0]];
        buffer[1] = stream->codebook[symbol[1]];
        buffer[2] = stream->codebook[symbol[2]];
        buffer[3] = stream->codebook[symbol[3]];
          /* update cursors. */
        buffer += 4, pass += 4, data += 3, size -= 3, (*used) += 3;
    }
    return (pass);
}

static size_t _b64_decode
    ( b64_iwire * stream, char * buffer, const char * data, size_t size, size_t * used )
{
    size_t pass = 0;
    char symbol[4];
    while ( size >= 4 )
    {
          /* translate symbols. */
        symbol[0] = stream->codebook[data[0]];
        symbol[1] = stream->codebook[data[1]];
        symbol[2] = stream->codebook[data[2]];
        symbol[3] = stream->codebook[data[3]];
          /* deflate. */
        buffer[0] = ((symbol[0]&0x3f)<<2) | ((symbol[1]&0x30)>>4);
        buffer[1] = ((symbol[1]&0x0f)<<4) | ((symbol[2]&0x3c)>>2);
        buffer[2] = ((symbol[2]&0x03)<<6) | ((symbol[3]&0x3f)<<0);
          /* update cursors. */
        buffer += 3, pass += 3, data += 4, size -= 4, (*used) += 4;
    }
    return (pass);
}

void b64_iwire_init ( b64_iwire * stream, const char * codebook )
{
    stream->object = 0;
    stream->accept_data = 0;
      /* reverse codebook for accelerated decoding. */
    if ( codebook ) {
        _b64_compute_codebook(codebook, stream->codebook);
    } else {
        _b64_compute_codebook(STANDARD, stream->codebook);
    }
}

size_t b64_iwire_feed ( b64_iwire * stream, const char * data, size_t size )
{
    char buffer[SIZE];
    size_t used = 0;
    size_t pass = 0;
    while ( size-used >= 4 )
    {
        pass = _b64_decode(stream, buffer,
            data+used, _b64_max(size-used, SIZE), &used);
          /* traling '=' suffix procudes null bytes, don't forward them. */
        while ( buffer[pass-1] == 0 ) {
            --pass;
        }
        stream->accept_data(stream, buffer, pass);
    }
    return (used);
}

size_t b64_iwire_done ( b64_iwire * stream, const char * data, size_t size )
{
    char symbol[4];
    char buffer[4];
    size_t used = b64_iwire_feed(stream, data, size);
    data += used, size -= used;
    if ( size == 3 )
    {
          /* translate symbols. */
        symbol[0] = stream->codebook[data[0]];
        symbol[1] = stream->codebook[data[1]];
        symbol[2] = stream->codebook[data[2]];
          /* deflate. */
        buffer[0] = ((symbol[0]&0x3f)<<2) | ((symbol[1]&0x30)>>4);
        buffer[1] = ((symbol[1]&0x0f)<<4) | ((symbol[2]&0x3c)>>2);
        buffer[2] = ((symbol[2]&0x03)<<6);
    }
    if ( size == 2 )
    {
          /* translate symbols. */
        symbol[0] = stream->codebook[data[0]];
        symbol[1] = stream->codebook[data[1]];
          /* deflate. */
        buffer[0] = ((symbol[0]&0x3f)<<2) | ((symbol[1]&0x30)>>4);
        buffer[1] = ((symbol[1]&0x0f)<<4);
    }
    if ( size == 1 )
    {
          /* translate symbols. */
        symbol[0] = stream->codebook[data[0]];
          /* deflate. */
        buffer[0] = ((symbol[0]&0x3f)<<2);
    }
    stream->accept_data(stream, buffer, size);
    return (size);
}

void b64_owire_init ( b64_owire * stream, const char * codebook )
{
    stream->object = 0;
    stream->accept_data = 0;
    if ( codebook ) {
        memcpy(stream->codebook, codebook, 64);
    } else {
        memcpy(stream->codebook, STANDARD, 64);
    }
}

size_t b64_owire_feed ( b64_owire * stream, const char * data, size_t size )
{
    char buffer[SIZE];
    size_t used = 0;
    size_t pass = 0;
    while ( size-used >= 3 )
    {
        pass = _b64_encode(stream, buffer,
            data+used, _b64_max(size-used, SIZE), &used);
        stream->accept_data(stream, buffer, pass);
    }
    return (used);
}

size_t b64_owire_done ( b64_owire * stream, const char * data, size_t size )
{
    char code[4];
    char buffer[4];
    size_t used = b64_owire_feed(stream, data, size);
    data += used, size -= used;
    if ( size == 2 )
    {
          /* inflate. */
        code[0] = ((data[0]&0xfc)>>2);
        code[1] = ((data[0]&0x03)<<4) | ((data[1]&0xf0)>>4);
        code[2] = ((data[1]&0x0f)<<2);
          /* translate codes. */
        buffer[0] = stream->codebook[code[0]];
        buffer[1] = stream->codebook[code[1]];
        buffer[2] = stream->codebook[code[2]];
        buffer[3] = '=';
          /* update cursors. */
        stream->accept_data(stream, buffer, 4);
    }
    if ( size == 1 )
    {
          /* inflate. */
        code[0] = ((data[0]&0xfc)>>2);
        code[1] = ((data[0]&0x03)<<4);
          /* translate codes. */
        buffer[0] = stream->codebook[code[0]];
        buffer[1] = stream->codebook[code[1]];
        buffer[2] = '=';
        buffer[3] = '=';
          /* update cursors. */
        stream->accept_data(stream, buffer, 4);
    }
    return (size);
}
