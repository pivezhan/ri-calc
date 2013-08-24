Computes the dispersion of a material given material properties. For example, given an absorbance spectrum, this software can estimate the complex refractive index and Chi values.

A Windows 32 executable is provided in the Win32 directory.  All of the necessary runtime libraries are included.  Start by running 'ricalc -h' for command-line options.

This software is designed to be used with CMake, so we recommend using it to build the application.

This software requires the following libraries for compiling:

FFTW - Fast Fourier Transform library -- http://www.fftw.org
    or
CUDA - NVidia's GPU programming toolkit -- https://developer.nvidia.com/

RTS - Real-Time Scraps C++ library (my codebase) -- https://github.com/dmayerich/RTS






