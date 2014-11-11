tinyrcpp
========

A tiny RCP library for C++ based on Boost.Asio.

Prerequisists
=============

Debian packages: libasio-dev, libboost-thread-dev, libboost-serialization-dev

Build and run demo client and server
====================================

    $ cd demo1
    $ make DEMO1_DIR=$(pwd)
   
    $ ./server1 &
    $ ./client1 127.0.0.1 1313
