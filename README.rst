==========================================================
  `cb64` --- Incremental Base64 encoder and decoder in C
==========================================================
:authors:
   André Caron
:contact: andre.l.caron@gmail.com

Description
===========

This library provides an encoder and a decoder for `Base64`_ encoded data.  The
coders are implemented as finite state machine (FSM) for use in streaming
applications (i.e. data arrives at an unpredictable rate and the parser must be
interruptible).  As such, the parser itself does not buffer any received data.
It just forwards it to registered callbacks.  It requires little overhead and is
well suited for being used in an object-oriented wrapper.

.. _`Base64`: http://en.wikipedia.org/wiki/Base64
