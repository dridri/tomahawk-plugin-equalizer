tomahawk-plugin-equalizer
=========================

Equalizer plugin for Tomahawk Player


Depends :
---------

This plugin needs a little patch in Tomahawk because the AudioEngine doesn't
let us to get the Phonon's audio path and add the equalizer in it.

It is currently wotking against commit 91223c4 of AudioEngine.cpp/h sources.

Just apply patch 'AudioEngine.path' into src/libtomahawk/audio of tomahawk's 
project folder then build it the normal way.


Building and running :
----------------------

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ make install / copy .so/.dll file into the same folder of tomahawk binary
