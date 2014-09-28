tomahawk-plugin-equalizer
=========================

Equalizer plugin for Tomahawk Player


Dependancies :
--------------

* Tomahawk version 0.8 or higher
* libFFTW version 3.x (http://www.fftw.org/)

VLC-phonon-backend does not provide equalizer capability, for now you will have
to use a modded version alongside an audio filter available here :

https://github.com/dridri/phonon-vlc

https://github.com/dridri/vlc-dsp-plugin


Building and running :
----------------------

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ make install   -- copy .so/.dll file into the same folder as tomahawk binary
