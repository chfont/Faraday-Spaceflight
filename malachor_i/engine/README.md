# Engine Code

This folder holds code for calculations relating to the engine (primarily thrust) used in the Malachor I project, namely the E12-6 engine.

The data used as the basis for the thrust calculations can be found [here](https://www.nar.org/SandT/pdf/Estes/E12.pdf)

## Structure
engine.hpp, engine.cpp - C++ code to be used by the flight computer for calculations.

engine.m - Matlab file used to take data from the data sheet and create more usable functions for the C++ component.
