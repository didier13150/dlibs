dlibs
=====

C++ Framework to have a simple way of programming life.

Introduction
------------

Some of the functionality provide includes :

* Writing logs with the log libraries : An already build-in factory ( DLogger )
* Settings file operation (XML format) with the DSettings library.
* Sockets functions with The DSock library : client part with DClientSock and server part with DServerSock.
* String operations with the DString library.
* Manage points and rectangle with DPoint and rectangle with DRect libraries.
* Database operations with the DDatabase factory library DSQLite and optionnaly DMySQL, DPgSQL.
* Manage URL with the DURL library
* Send email by the DSMTP library
* Use exception with DException
* A class to manage events : DBasicEvent
* A template factory engine : DFactory
* A template singleton : DSingleton
* A class to manage thread process : DThread
* A template observer-observable pair : DObserver and DObservable
* A timer : DTimer
* Parse command line arguments with the DAppCmdLine ( DAppOption and DAppArg )

Build library
-------------

    mkdir build

    cd build

    cmake -i ..

    make install

After the install process, you can rediscover the prefix by the 'dlibspath --prefix' command line ( in a terminal or directly in cmake )

Documentation (doxygen) can be built as well

    make doc
    
Run Unit-tests for library elements

    make test

Howto to use it
---------------

You just need to include the all in one header file.

    &#35;include &lt;dlibs/dlibs.h&gt;

or add the header files directory to the cpp flags and include file in your code like this :

    -I/usr/local/dlibs

In this example, the prefix path ( /usr/local ) can be found with the 'dlibspath --prefix' command line

    &#35;include &lt;dlibs.h&gt;

And for linking your application against the dlibss library, just add this option into your Makefile :

    -L/usr/local/libs -ldlibs

Supported Platforms
-------------------

The application has been successfully built on the following platforms:
* Linux (x86, x86_64) : on debian, fedora and gentoo.

Dependencies
------------

This library depends on several other open source packages.These must be installed before libraries can be installed ( Don't forget the devel packages) :
* pthread (The lib use threads)
* libxml2 (XML API)
* librt (real time)
* libmysql (DB operations) : optionnal
* libpq (DB operations) : optionnal

Note

* SQLite is not necessary to build DLibs because a embedded version is present in package source.

Licensing
---------

The libraries are licensed under GNU/GPL v3 license. See the COPYING file.
